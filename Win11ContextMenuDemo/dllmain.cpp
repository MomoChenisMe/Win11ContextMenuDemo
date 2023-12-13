// dllmain.cpp : 定義 DLL 應用程式的進入點。
#include "pch.h"
#include "InstallContextMenu.h"
#include "MainExplorerCommand.h"

HMODULE g_module;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_module = hModule;
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

STDAPI DllRegisterServer()
{
    return Win11ContextMenuDemo::InstallContextMenu::InstallContextMenu();
}

STDAPI DllUnregisterServer()
{
    return Win11ContextMenuDemo::InstallContextMenu::UnInstallContextMenu();
}

_Use_decl_annotations_ STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) try
{
    *ppv = nullptr;

    if (rclsid == __uuidof(Win11ContextMenuDemo::ExplorerCommand::MainExplorerCommand))
    {
        return winrt::make<Win11ContextMenuDemo::ExplorerCommand::MainExplorerCommand>().as(riid, ppv);
    }
    else
    {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}
catch (...)
{
    return winrt::to_hresult();
}

__control_entrypoint(DllExport) STDAPI DllCanUnloadNow()
{
    if (winrt::get_module_lock())
    {
        return S_FALSE;
    }
    else
    {
        return S_OK;
    }    
}