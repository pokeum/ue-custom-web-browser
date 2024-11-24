#pragma once

#include "CoreMinimal.h"
#include "IWebBrowserWindow.h"
#include "Components/Widget.h"
#include "CustomWebBrowser.generated.h"

enum class EWebBrowserConsoleLogSeverity;

#define MESSAGING_SCHEME	TEXT("uewebbrowser://")

/**
 * UMG Widget Class
 */
UCLASS()
class CUSTOMWEBBROWSER_API UCustomWebBrowser : public UWidget
{
	GENERATED_UCLASS_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUrlChanged, const FText&, Text);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeforePopup, FString, URL, FString, Frame);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConsoleMessage, const FString&, Message, const FString&, Source, int32, Line);

	/**
	 * Load the specified URL
	 *
	 * @param NewURL New URL to load
	 */
	UFUNCTION(BlueprintCallable, Category="Custom Web Browser")
	void LoadURL(FString NewURL);

	/**
	 * Load a string as data to create a web page
	 *
	 * @param Contents String to load
	 * @param DummyURL Dummy URL for the page
	 */
	UFUNCTION(BlueprintCallable, Category="Custom Web Browser")
	void LoadString(FString Contents, FString DummyURL);

	/**
	* Executes a JavaScript string in the context of the web page
	*
	* @param ScriptText JavaScript string to execute
	*/
	UFUNCTION(BlueprintCallable, Category="Custom Web Browser")
	void ExecuteJavascript(const FString& ScriptText);

	/**
	 * Get the current title of the web page
	 */
	UFUNCTION(BlueprintCallable, Category="Web Browser")
	FText GetTitleText() const;

	/**
	* Gets the currently loaded URL.
	*
	* @return The URL, or empty string if no document is loaded.
	*/
	UFUNCTION(BlueprintCallable, Category="Custom Web Browser")
	FString GetUrl() const;

	/** Called when the Url changes. */
	UPROPERTY(BlueprintAssignable, Category = "Custom Web Browser|Event")
	FOnUrlChanged OnUrlChanged;

	/** Called when a popup is about to spawn. */
	UPROPERTY(BlueprintAssignable, Category = "Custom Web Browser|Event")
	FOnBeforePopup OnBeforePopup;

	/** Called when the browser has console spew to print */
	UPROPERTY(BlueprintAssignable, Category = "Custom Web Browser|Event")
	FOnConsoleMessage OnConsoleMessage;

public:

	//~ Begin UWidget interface
	virtual void SynchronizeProperties() override;
	// End UWidget interface

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

protected:
	/** URL that the browser will initially navigate to. The URL should include the protocol, eg http:// */
	UPROPERTY(EditAnywhere, Category=Appearance)
	FString InitialURL;

	/** Should the browser window support transparency. */
	UPROPERTY(EditAnywhere, Category=Appearance)
	bool bSupportsTransparency;

protected:
	TSharedPtr<class SWebBrowser> WebBrowserWidget;

protected:
	// UWidget interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End of UWidget interface

	void HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity);
	void HandleOnUrlChanged(const FText& Text);
	bool HandleOnBeforePopup(FString URL, FString Frame);

//////////////////////////////////////////////////////////////////////////
/// Web Browser to Unreal Engine - Messaging System

public:
	void BindUObject(const FString& Name, UObject* Object, bool bIsPermanent = true) const;
	
public:
	DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnBeforeBrowse, const FString&, const FWebNavigationRequest&);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageReceived, const FString&, Url);

protected:
	/**
	 * Called before the widget navigates to a new URL.
	 * It can be used to modify or cancel the navigation process.
	 */
	bool HandleOnBeforeBrowse(const FString& Url, const FWebNavigationRequest& WebNavigationRequest);

public:
	/**
	 * Called when URL starting with uewebbrowser:// scheme is loaded.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Custom Web Browser|Event")
	FOnMessageReceived OnMessageReceived;
	
//////////////////////////////////////////////////////////////////////////
/// OnLoadUrl

public:
	DECLARE_DELEGATE_RetVal_ThreeParams(bool, FOnLoadUrl, const FString&, const FString&, FString&);

protected:
	/** Called to allow bypassing page content on load. */
	bool HandleOnLoadUrl(const FString& Method, const FString& Url, FString& Response) const;

//////////////////////////////////////////////////////////////////////////
/// OnLoadCompleted

public:
	DECLARE_DELEGATE(FOnLoadCompletedDelegate);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadCompleted);

protected:
	/** Called when document loading completed */
	void HandleOnLoadCompleted();

public:
	UPROPERTY(BlueprintAssignable, Category = "Custom Web Browser|Event")
	FOnLoadCompleted OnLoadCompleted;

//////////////////////////////////////////////////////////////////////////
/// Logging

private:
	void Logging(const FString& Msg) const;
};
