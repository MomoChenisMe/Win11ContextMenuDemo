# Win11ContextMenuDemo

NuGet
Microsoft.Windows.CppWinRT
Microsoft.Windows.ImplementationLibrary

```
.\makeappx.exe pack /d <Appx Path> /p <Appx Path>\Win11ContextMenuDemo.msix
.\signtool.exe sign /debug /fd SHA256 /a /f <Appx Path>\Win11ContextMenu.pfx /t http://timestamp.digicert.com /p <Password> <Appx Path>\Win11ContextMenuDemo.msix
```