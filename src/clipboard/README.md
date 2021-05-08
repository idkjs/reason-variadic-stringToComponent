# Clipboard Binding To Dom

Clipboard Binding to Dom instead of the imported copy-to-clipboard

# Source for clipboard file in this directory

https://github.com/DivertiseAsia/diversite


```reason

type navigator;
type clipboard;

// Binding to Navigator on DOM.
// https://developer.mozilla.org/en-US/docs/Web/API/Navigator
// https://www.w3schools.com/jsref/obj_navigator.asp
// A thing of this type will have all the attributes of the navigator object
[@bs.val] external navigator: navigator = "navigator";
module Navigator = {
  [@bs.get] external getClipboard: navigator => clipboard = "clipboard";
  [@bs.send]
  external writeText: (clipboard, string) => Js.Promise.t(unit) = "writeText";
};

let copyToClipboard: string => Js.Promise.t(unit) =
  s => navigator->Navigator.getClipboard->Navigator.writeText(s);
```

- usage

```reason
  let copyClick = () => {
    Clipboard.copyToClipboard("contact@divertise.asia")
    |> Js.Promise.(then_(_ => showCopySuccessMessage() |> resolve))
    |> Js.Promise.(catch(_ => showCopyFailMessage() |> resolve))
    |> ignore;
  };
```
The `navigator` type is same as `type t` you might see elsewhere. Its the type for this file.

## Binding to Navigator

```reason
[@bs.val] external navigator: navigator = "navigator";
```
If you log the navigator object you will see:
<details>
<summary>Navigator Object</summary>
```sh
{}
Navigator { globalPrivacyControl: true, permissions: Permissions, mimeTypes: MimeTypeArray, plugins: PluginArray, doNotTrack: "unspecified", maxTouchPoints: 0, mediaCapabilities: MediaCapabilities, oscpu: "Intel Mac OS X 10.15", vendor: "", vendorSub: "" }
​
activeVRDisplays: Array []
​
appCodeName: "Mozilla"
​
appName: "Netscape"
​
appVersion: "5.0 (Macintosh)"
​
buildID: "20181001000000"
​
clipboard: Clipboard {  }
​
cookieEnabled: true
​
credentials: CredentialsContainer {  }
​
doNotTrack: "unspecified"
​
geolocation: Geolocation {  }
​
globalPrivacyControl: true
​
hardwareConcurrency: 8
​
language: "en-US"
​
languages: Array [ "en-US", "en" ]
​
maxTouchPoints: 0
​
mediaCapabilities: MediaCapabilities {  }
​
mediaDevices: MediaDevices { ondevicechange: null }
​
mediaSession: MediaSession { metadata: null, playbackState: "none" }
​
mimeTypes: MimeTypeArray { length: 0 }
​
onLine: true
​
oscpu: "Intel Mac OS X 10.15"
​
permissions: Permissions {  }
​
platform: "MacIntel"
​
plugins: PluginArray { length: 0 }
​
product: "Gecko"
​
productSub: "20100101"
​
serviceWorker: ServiceWorkerContainer { controller: null, ready: Promise { "pending" }, oncontrollerchange: null, … }
​
storage: StorageManager {  }
​
userAgent: "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:88.0) Gecko/20100101 Firefox/88.0"
​
vendor: ""
​
vendorSub: ""
​
webdriver: false
​
<prototype>: NavigatorPrototype { vibrate: vibrate(), javaEnabled: javaEnabled(), getGamepads: getGamepads(), … }
​​
activeVRDisplays:
​​
appCodeName:
​​
appName:
​​
appVersion:
​​
buildID:
​​
clipboard:
​​
​​clipboard: Clipboard {  }
​​
<prototype>: ClipboardPrototype { writeText: writeText(), … }
​​​
constructor: function ()
​​​
writeText: function writeText()
​​​
Symbol(Symbol.toStringTag): "Clipboard"
​​​
<prototype>: EventTargetPrototype { addEventListener: addEventListener(), removeEventListener: removeEventListener(), dispatchEvent: dispatchEvent(), … }
...
```
</details>

A thing of the `type navigator` will have all the attributes of the `navigator` object.

In the list above you will notice the key for `clipboard` and the method `writeText` on the `clipboard` object.

  [@bs.get] external getClipboard: navigator => clipboard = "clipboard";
So when you call `copyToClipboard` with a string, you pass it to `navigator` so that now when you are calling `Navigator.getClipboard` its recieving an argument of the clipboard type which its expecting and which has the `clipboard` method on it which we are binding to with `getClipboard` and which returns the opaque type `clipboard`.

We then pass the what we got from `getClipboard` to `writeText`. Remember that `writeText` is a method on `getClipboard` so that our Navigator module is emulating the DOM `clipboard` object. By passing the `clipboard` to `writeText` we are saying `call the writeText method on the clipboard object with the passed in string`.

The way this is set up, despite all the keys on the `Navigator` object that we logged, the only thing we needed to bind to was the `Js.Promise.t(unit)` return type. We dont care what else is on it because passed it directly to its function.
