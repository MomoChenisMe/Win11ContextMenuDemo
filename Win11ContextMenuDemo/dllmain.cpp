// dllmain.cpp : 定義 DLL 應用程式的進入點。
#include "pch.h"
#include "InstallContextMenu.h"
#include "MainExplorerCommand.h"
#include "ClassFactory.h"

// 全域變數，用來儲存 DLL 模組的句柄。
// Global variable to store the handle of the DLL module.
HMODULE g_module; 

// DLL 的主入口函數。
// Main entry point function for the DLL.
BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // 當 DLL 被載入到進程時執行。
        // Executed when the DLL is loaded into a process.
        g_module = hModule;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        // 當線程創建或終止，或進程卸載 DLL 時執行。
        // Executed when a thread is created or terminated, or when the process unloads the DLL.
        break;
    }
    return TRUE;
}

// 註冊 DLL 以便用於上下文選單擴展。
// Register the DLL for context menu extension.
STDAPI DllRegisterServer()
{
    return Win11ContextMenuDemo::InstallContextMenu::InstallContextMenu();
}

// 注銷 DLL。
// Unregister the DLL.
STDAPI DllUnregisterServer()
{
    return Win11ContextMenuDemo::InstallContextMenu::UnInstallContextMenu();
}

// 返回一個類工廠以創建對象的實例。
// Returns a class factory to create an object's instance.
_Use_decl_annotations_ STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) try
{
    *ppv = nullptr;

    if (rclsid == __uuidof(Win11ContextMenuDemo::ExplorerCommand::MainExplorerCommand))
    {
        // 如果請求的是 MainExplorerCommand 的類工廠，則創建並返回。
        // Create and return the class factory if MainExplorerCommand is requested.
        return winrt::make<Win11ContextMenuDemo::ClassFactory::COMClassFactory<Win11ContextMenuDemo::ExplorerCommand::MainExplorerCommand>>().as(riid, ppv);
    }
    else
    {
        // 如果沒有可用的類，則返回錯誤。
        // Return an error if the class is not available.
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}
catch (...)
{
    // 捕捉並處理任何異常。
    // Catch and handle any exceptions.
    return winrt::to_hresult();
}

// 檢查是否可以卸載 DLL。
// Check whether the DLL can be unloaded.
__control_entrypoint(DllExport) STDAPI DllCanUnloadNow()
{
    // 檢查是否有活動的對象或類工廠。
    // Check for active objects or class factories.
    if (winrt::get_module_lock())
    {
        // 如果有，則不能卸載。
        // Cannot unload if there are.
        return S_FALSE;
    }
    else
    {
        // 如果沒有，則可以卸載。
        // Can unload if there are none.
        return S_OK;
    }
}
