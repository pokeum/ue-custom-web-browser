#include "Widget/CustomWebBrowser.h"
#include "SWebBrowser.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"

#if WITH_EDITOR
#endif

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include <android/log.h>
#endif

#define LOCTEXT_NAMESPACE "CustomWebBrowser"

#define DEBUGGING	1

/////////////////////////////////////////////////////
/// UCustomWebBrowser

UCustomWebBrowser::UCustomWebBrowser(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsVariable = true;
}

void UCustomWebBrowser::LoadURL(FString NewURL)
{
	if (WebBrowserWidget.IsValid())
	{
		return WebBrowserWidget->LoadURL(NewURL);
	}
}

void UCustomWebBrowser::LoadString(FString Contents, FString DummyURL)
{
	if (WebBrowserWidget.IsValid())
	{
		return WebBrowserWidget->LoadString(Contents, DummyURL);
	}
}

void UCustomWebBrowser::ExecuteJavascript(const FString& ScriptText)
{
	if (WebBrowserWidget.IsValid())
	{
		Logging(FString::Printf(TEXT("ExecuteJavascript: Script={%s}"), *ScriptText));
		
		return WebBrowserWidget->ExecuteJavascript(ScriptText);
	}
}

FText UCustomWebBrowser::GetTitleText() const
{
	if (WebBrowserWidget.IsValid())
	{
		return WebBrowserWidget->GetTitleText();
	}

	return FText::GetEmpty();
}

FString UCustomWebBrowser::GetUrl() const
{
	if (WebBrowserWidget.IsValid())
	{
		return WebBrowserWidget->GetUrl();
	}

	return FString();
}

void UCustomWebBrowser::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	WebBrowserWidget.Reset();
}

TSharedRef<SWidget> UCustomWebBrowser::RebuildWidget()
{
	if (IsDesignTime())
	{
		return SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("Custom Web Browser", "Custom Web Browser"))
			];
	}
	else
	{
		WebBrowserWidget = SNew(SWebBrowser)
			.InitialURL(InitialURL)
			.ShowControls(false)
			.SupportsTransparency(bSupportsTransparency)
			.OnUrlChanged(BIND_UOBJECT_DELEGATE(FOnTextChanged, HandleOnUrlChanged))
			.OnBeforePopup(BIND_UOBJECT_DELEGATE(FOnBeforePopupDelegate, HandleOnBeforePopup))
			.OnConsoleMessage(BIND_UOBJECT_DELEGATE(FOnConsoleMessageDelegate, HandleOnConsoleMessage))
			.OnBeforeNavigation(BIND_UOBJECT_DELEGATE(FOnBeforeBrowse, HandleOnBeforeBrowse))
			.OnLoadUrl(BIND_UOBJECT_DELEGATE(FOnLoadUrl, HandleOnLoadUrl))
			.OnLoadCompleted(BIND_UOBJECT_DELEGATE(FOnLoadCompletedDelegate, HandleOnLoadCompleted));
		
		return WebBrowserWidget.ToSharedRef();
	}
}

void UCustomWebBrowser::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	if (WebBrowserWidget.IsValid())
	{
	}
}

void UCustomWebBrowser::HandleOnUrlChanged(const FText& InText)
{
	OnUrlChanged.Broadcast(InText);
	
	Logging(FString::Printf(TEXT("HandleOnUrlChanged: InText={%s}"), *InText.ToString()));
}

void UCustomWebBrowser::HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity)
{
	OnConsoleMessage.Broadcast(Message, Source, Line);
}

bool UCustomWebBrowser::HandleOnBeforePopup(FString URL, FString Frame)
{
	if (OnBeforePopup.IsBound())
	{
		if (IsInGameThread())
		{
			OnBeforePopup.Broadcast(URL, Frame);
		}
		else
		{
			// Retry on the GameThread.
			TWeakObjectPtr<UCustomWebBrowser> WeakThis = this;
			FFunctionGraphTask::CreateAndDispatchWhenReady([WeakThis, URL, Frame]()
			{
				if (WeakThis.IsValid())
				{
					WeakThis->HandleOnBeforePopup(URL, Frame);
				}
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		}

		return true;
	}

	return false;
}

#if WITH_EDITOR

const FText UCustomWebBrowser::GetPaletteCategory()
{
	return LOCTEXT("Experimental", "Experimental");
}

#endif

/////////////////////////////////////////////////////

void UCustomWebBrowser::BindUObject(const FString& Name, UObject* Object, bool bIsPermanent) const
{
	if (WebBrowserWidget.IsValid())
	{
		WebBrowserWidget->BindUObject(Name, Object, bIsPermanent);
	}
}

bool UCustomWebBrowser::HandleOnBeforeBrowse(const FString& Url, const FWebNavigationRequest& WebNavigationRequest)
{
	Logging(FString::Printf(TEXT("HandleOnBeforeBrowse: Url={%s}"), *Url));

	if (Url.StartsWith(MESSAGING_SCHEME))
	{
		if (OnMessageReceived.IsBound())
		{
			if (IsInGameThread())
			{
				OnMessageReceived.Broadcast(Url);
			}
			else
			{
				// Retry on the GameThread.
				TWeakObjectPtr<UCustomWebBrowser> WeakThis = this;
				FFunctionGraphTask::CreateAndDispatchWhenReady([WeakThis, Url, WebNavigationRequest]()
				{
					if (WeakThis.IsValid())
					{
						WeakThis->HandleOnBeforeBrowse(Url, WebNavigationRequest);
					}
				}, TStatId(), nullptr, ENamedThreads::GameThread);
			}
		}
		
		return true;
	}
	
	return false;
}

bool UCustomWebBrowser::HandleOnLoadUrl(const FString& Method, const FString& Url, FString& Response) const
{
	Logging(FString::Printf(TEXT("HandleOnLoadUrl: Method={%s}, Url={%s}, Response={%s}"), *Method, *Url, *Response));
	
	return false;
}

void UCustomWebBrowser::HandleOnLoadCompleted()
{
	Logging(TEXT("HandleOnLoadCompleted"));

	if (OnLoadCompleted.IsBound())
	{
		if (IsInGameThread())
		{
			OnLoadCompleted.Broadcast();
		}
		else
		{
			// Retry on the GameThread.
			TWeakObjectPtr<UCustomWebBrowser> WeakThis = this;
			FFunctionGraphTask::CreateAndDispatchWhenReady([WeakThis]()
			{
				if (WeakThis.IsValid())
				{
					WeakThis->HandleOnLoadCompleted();
				}
			}, TStatId(), nullptr, ENamedThreads::GameThread);
		}
	}
}

void UCustomWebBrowser::Logging(const FString& Msg) const
{
	if constexpr (!DEBUGGING) return;
	
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "cwbLogDebug", "(Ljava/lang/String;)V", false);
		jstring JStringMsg = Env->NewStringUTF(TCHAR_TO_UTF8(*Msg));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JStringMsg);
	}
#elif PLATFORM_IOS
	NSLog(@"[CustomWebBrowser] %@", Msg.GetNSString());
#else
	UE_LOG(LogTemp, Display, TEXT("[CustomWebBrowser] %s"), *Msg);
#endif
}

#undef LOCTEXT_NAMESPACE