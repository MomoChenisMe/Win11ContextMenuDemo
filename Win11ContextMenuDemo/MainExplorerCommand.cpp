#include "pch.h"
#include "MainExplorerCommand.h"
#include "Path.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

IFACEMETHODIMP MainExplorerCommand::GetTitle(IShellItemArray* psiItemArray, LPWSTR* ppszName)
{
    UNREFERENCED_PARAMETER(psiItemArray);

    wstring title = L"MomoWin11ContextMennu";
    SHStrDup(title.data(), ppszName);

    return S_OK;
}

IFACEMETHODIMP MainExplorerCommand::GetIcon(IShellItemArray* psiItemArray, LPWSTR* ppszIcon)
{
    UNREFERENCED_PARAMETER(psiItemArray);
    wstring iconPath = Win11ContextMenuDemo::Path::GetContextMenuDirectoryPath() + L"\\Assets\\MainIcon.ico";
    return SHStrDupW(iconPath.data(), ppszIcon);
}

//IFACEMETHODIMP MainExplorerCommand::GetFlags(EXPCMDFLAGS* flags)
//{
//    *flags = ECF_HASSUBCOMMANDS;
//    return S_OK;
//}

IFACEMETHODIMP MainExplorerCommand::EnumSubCommands(IEnumExplorerCommand** ppEnum)
{
    *ppEnum = nullptr;
    return E_NOTIMPL;
    //vector<winrt::com_ptr<IExplorerCommand>> subCommands;
    //auto subCommand = winrt::make<TSubExplorerCommand>();
    //subCommands.push_back(subCommand.as<IExplorerCommand>());
    //auto enumCommands = winrt::make_self<TSubEnumExplorerCommand>(move(subCommands));
    //*ppEnum = enumCommands.detach();

    //return S_OK;
}

IFACEMETHODIMP MainExplorerCommand::Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept try
{
    UNREFERENCED_PARAMETER(psiItemArray);
    UNREFERENCED_PARAMETER(pbc);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    wstring commandLine = L"cmd.exe /C echo Hello World. Welcome to use MomoWin11ContextMennu && pause;";

    if (!CreateProcessW(nullptr,   // 不需要指定應用程式名稱，因為它在命令行中指定
        (LPWSTR)commandLine.c_str(), // 命令行
        nullptr, // 不使用 process attributes
        nullptr, // 不使用 thread attributes
        false,   // 不繼承 handles
        0,       // 沒有創建標誌
        nullptr, // 不使用環境變數
        nullptr, // 使用當前目錄
        &si,     // 指向 STARTUPINFO 結構的指針
        &pi))    // 指向 PROCESS_INFORMATION 結構的指針
    {
        return S_OK;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return S_OK;
}
CATCH_RETURN();