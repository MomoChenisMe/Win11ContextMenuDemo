# Win11 Context Menu Demo
This is a demo project for Win11 modern context menu, implemented using the IExplorerCommand interface and Sparse package.
<br>
<br>

# Install NuGet Packages
To develop this project, you need to install the following NuGet packages:
- Microsoft.Windows.CppWinRT
- Microsoft.Windows.ImplementationLibrary
<br>
<br>

# Generating Sparse Package Process
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