# Win11 Context Menu Demo
此為 Win11 的右鍵現代選單 Demo 用專案，透過 IExplorerCommannd 和 IEnumExplorerCommand介面，搭配Sparse package 實現客製化的上下文選單。
<br>
<br>

## 準備工具
為了開發此專案，需要準備以下工具：
- [Visual Studio 2022](https://visualstudio.microsoft.com/zh-hant/vs/whatsnew/)
- [Windows SDK](https://developer.microsoft.com/zh-tw/windows/downloads/windows-sdk/)
<br>
<br>

## 安裝 NuGet 套件
Visual Studio 2022 需要安裝以下 NuGet 套件：
- [Microsoft.Windows.CppWinRT](https://github.com/Microsoft/cppwinrt)
- [Microsoft.Windows.ImplementationLibrary](https://github.com/Microsoft/wil)
<br>
<br>

## 產生 Sparse package 流程
以下是產生 Sparse package 的步驟：

1. **準備好 Win11 客製選單 DLL**：
   確保您的 DLL 已經建置並準備好。

2. **準備 AppxManifest.xml**：
   創建並配置 AppxManifest.xml 文件，這是生成 Sparse package 的重要部分。

3. **產生 Sparse package**：
   使用以下命令來產生 Sparse package：
    ```
    makeappx.exe pack /d <Your AppxPath> /p <Your AppxPath>\Win11ContextMenuDemo.msix
    ```

4. **建立自簽名憑證**：
使用 PowerShell 命令建立一個自簽名的數位憑證：
    ```
    New-SelfSignedCertificate -Type Custom -Subject "CN=MomoChenIsMe, C=TW" -KeyUsage DigitalSignature -FriendlyName "MomoChenIsMe" -CertStoreLocation "Cert:\CurrentUser\My" -TextExtension @("2.5.29.37={text}1.3.6.1.5.5.7.3.3", "2.5.29.19={text}")
    ```

5. **查看所有憑證**：
透過以下命令查看所有憑證：
    ```
    Set-Location Cert:\CurrentUser\My
    Get-ChildItem
    ```

6. **刪除憑證（如有需要）**：
如需刪除某個憑證，可使用以下命令：
    ```
    Remove-Item Cert:\CurrentUser\My\<Your Thumbprint>
    ```

7. **導出自簽名憑證**：
將自簽名憑證導出為 .pfx 檔案：
    ```
    $password = ConvertTo-SecureString -String <Your Password> -Force -AsPlainText
    Export-PfxCertificate -cert "Cert:\CurrentUser\My\<Your Thumbprint>" -FilePath <Certificate FilePath>.pfx -Password $password
    ```

8. **簽署 Sparse package**：
使用以下命令簽署 Sparse package： 
    ```
    signtool.exe sign /fd SHA256 /a /f <Your AppxPath>\Win11ContextMenu.pfx /t http://timestamp.digicert.com /p <Your Password> <Your AppxPath>\Win11ContextMenuDemo.msix
    ```
    如果需要進入debug模式可以添加`/debug`參數。
