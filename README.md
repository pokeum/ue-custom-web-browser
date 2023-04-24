# Custom Web Browser

## Unreal Web Browser [:link:](https://docs.unrealengine.com/4.27/ko/InteractiveExperiences/UMG/UserGuide/WidgetTypeReference/WebBrowser/)

Created a `Custom Web Browser` plugin by extending the `Web Browser Widget` provided by Unreal Engine.

```
web-browser       
  ├── WebBrowser       
  └── WebBrowserWidget
```

| File | Location |
|---|---|
| WebBrowser | :file_folder: `/Users/Shared/Epic\ Games/UE_4.26/Engine/Source/Runtime/WebBrowser` |
| WebBrowserWidget | :file_folder: `/Users/Shared/Epic\ Games/UE_4.26/Engine/Plugins/Runtime/WebBrowserWidget` |

## Web Browser to Unreal Engine - Messaging System

With the help of the Messaging System of `Custom Web Browser` (by using the HandleOnBeforeBrowse method), 
we are able to send a message from web browser through a specified URL scheme.

`Custom Web Browser` by default is inspecting any URL starting with **`uewebbrowser://`** scheme. When this kind of URL received, 
it sends a message to Unreal Engine instead of loading it in the web browser.

For example, suppose you wrote a Javascript code which loads a `uewebbrowser://` URL:

```javascript
window.location.href = "uewebbrowser://purchase?name=" + myPurchase.name + "&price=" + myPurchase.price;
```

In `Custom Web Browser`, an OnMessageReceived event will be raised when this URL is loaded.