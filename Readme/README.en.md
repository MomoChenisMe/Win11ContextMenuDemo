# Win11 Context Menu Demo
This is a demo project for Win11 modern context menu, implemented using the IExplorerCommand interface and Sparse package.
<br>
<br>

## Related Articles
 - [Windows 11 - 自定義右鍵選單（IExplorerCommand 程式實作）](https://www.momochenisme.com/2023/12/windows11-custom-contextmenu-with-iexplorercommand-and-sparsepackage.html)
 - [Windows 11 - 自定義右鍵選單（Sparse Package 實作）](https://www.momochenisme.com/2023/12/windows11-custom-contextmenu-with-iexplorercommand-and-sparsepackage-part2.html)
<br>
<br>

## Preparation Tools
To develop this project, you will need the following tools:
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/whatsnew/)
- [Windows SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)
<br>
<br>

## Install NuGet Packages
For Visual Studio 2022, the following NuGet packages need to be installed:
- [Microsoft.Windows.CppWinRT](https://github.com/Microsoft/cppwinrt)
- [Microsoft.Windows.ImplementationLibrary](https://github.com/Microsoft/wil)
<br>
<br>

## Generating Sparse Package Process
Here are the steps to generate a Sparse package:

1. **Prepare Win11 Custom Menu DLL**:
Ensure your DLL is built and ready.

2. **Prepare AppxManifest.xml**:
Create and configure the AppxManifest.xml file, which is a crucial part for generating Sparse package.

3. **Generate Sparse Package**:
Use the following command to generate the Sparse package:
    ```
    makeappx.exe pack /d <Your AppxPath> /p <Your AppxPath>\Win11ContextMenuDemo.msix
    ```

4. **Create a Self-Signed Certificate**:
Use PowerShell to create a digital self-signed certificate:
    ```
    New-SelfSignedCertificate -Type Custom -Subject "CN=MomoChenIsMe, C=TW" -KeyUsage DigitalSignature -FriendlyName "MomoChenIsMe" -CertStoreLocation "Cert:\CurrentUser\My" -TextExtension @("2.5.29.37={text}1.3.6.1.5.5.7.3.3", "2.5.29.19={text}")
    ```

5. **View All Certificates**:
View all certificates with the following command:
    ```
    Set-Location Cert:\CurrentUser\My
    Get-ChildItem
    ```

6. **Delete a Certificate (if necessary)**:
To delete a certificate, use the following command:
    ```
    Remove-Item Cert:\CurrentUser\My\<Your Thumbprint>
    ```

7. **Export the Self-Signed Certificate**:
Export the self-signed certificate as a .pfx file:
    ```
    $password = ConvertTo-SecureString -String <Your Password> -Force -AsPlainText
    Export-PfxCertificate -cert "Cert:\CurrentUser\My\<Your Thumbprint>" -FilePath <Certificate FilePath>.pfx -Password $password
    ```

8. **Sign the Sparse Package**:
Sign the Sparse package with the following command:
    ```
    signtool.exe sign /fd SHA256 /a /f <Your AppxPath>\Win11ContextMenu.pfx /t http://timestamp.digicert.com /p <Your Password> <Your AppxPath>\Win11ContextMenuDemo.msix
    ```
    To enter debug mode, add the `/debug` parameter.
<br>
<br>

## Registering a DLL
To register a DLL, use the following command:

```
regsvr32.exe <Your DLL Path>
```

To unregister a DLL, use the following command:
```
regsvr32.exe /u <Your DLL Path>
```