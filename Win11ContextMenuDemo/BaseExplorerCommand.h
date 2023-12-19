#pragma once
#include "pch.h"
#include "resource.h"

namespace Win11ContextMenuDemo::ExplorerCommand
{
    // BaseExplorerCommand 是一個基礎類，用於實現 IExplorerCommand 介面。
    // BaseExplorerCommand is a base class for implementing the IExplorerCommand interface.
    class BaseExplorerCommand : public winrt::implements<BaseExplorerCommand, IExplorerCommand, IObjectWithSite>
    {
    protected:
       // 獲取當前 Explorer 路徑的方法。
       // This method retrieves the current Explorer path.
       virtual wstring GetCurrentExplorerPath();

        // 獲取多語言標題的方法。
        // Method for obtaining the multi-language title.
        virtual const wstring GetMultiLanguageTitle();

        // 獲取圖標路徑的方法。
        // Method for obtaining the icon path.
        virtual const wstring GetIconPath();

        // 用於存儲標題資源 ID 的成員變數。
        // Member variable to store the title resource ID.
        UINT titleResourceID = ID_WIN11CONTEXTMENUDEMO_DEFAULT;

        // 用於存儲圖標檔案名的成員變數。
        // Member variable to store the icon file name.
        wstring iconFileName = L"";

        // 用於存儲 site 物件的 COM 指針。
        // COM pointer to store the site object.
        winrt::com_ptr<IUnknown> m_Site;
    public:
        // 設置 site 物件的方法。
        // Method to set the site object.
        virtual HRESULT SetSite(IUnknown* pUnkSite);

        // 獲取 site 物件的方法。
        // Method to get the site object.
        virtual HRESULT GetSite(REFIID riid, void** ppvSite);

        // 設置標題資源 ID 的方法。
        // Method to set the title resource ID.
        virtual void SetTitleResourceID(UINT id);

        // 設置圖標檔案名的方法。
        // Method to set the icon file name.
        virtual void SetIconFileName(wstring fileName);

        // 獲取命令的標題。
        // Get the title of the command.
        virtual IFACEMETHODIMP GetTitle(IShellItemArray* psiItemArray, LPWSTR* ppszName);

        // 獲取命令的圖標。
        // Get the icon of the command.
        virtual IFACEMETHODIMP GetIcon(IShellItemArray* psiItemArray, LPWSTR* ppszIcon);

        // 獲取命令的工具提示。
        // Get the tooltip of the command.
        virtual IFACEMETHODIMP GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip);

        // 獲取命令的狀態。
        // Get the state of the command.
        virtual IFACEMETHODIMP GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState);

        // 獲取命令的旗標。
        // Get the flags of the command.
        virtual IFACEMETHODIMP GetFlags(EXPCMDFLAGS* flags);

        // 獲取命令的標準名稱。
        // Get the canonical name of the command.
        virtual IFACEMETHODIMP GetCanonicalName(GUID* pguidCommandName);

        // 枚舉子命令。
        // Enumerate sub-commands.
        virtual IFACEMETHODIMP EnumSubCommands(IEnumExplorerCommand** ppEnum);

        // 執行命令的方法，必須由派生類實現。
        // The method to execute the command, which must be implemented by derived classes.
        IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept override;
    };
}
