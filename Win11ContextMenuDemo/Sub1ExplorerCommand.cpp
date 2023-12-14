#include "pch.h"
#include "Sub1ExplorerCommand.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

Sub1ExplorerCommand::Sub1ExplorerCommand()
{
    SetTitleResourceID(ID_WIN11CONTEXTMENUDEMO_SUB1);
    SetIconFileName(L"\\Assets\\Sub1Icon.ico");
}

IFACEMETHODIMP Sub1ExplorerCommand::Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept try
{
    UNREFERENCED_PARAMETER(psiItemArray);
    UNREFERENCED_PARAMETER(pbc);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    wstring commandLine = L"cmd.exe /C echo Hello World by Sub1Win11ContextMenu. && pause;";
    if (!CreateProcessW(nullptr, (LPWSTR)commandLine.c_str(), nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi))
    {
        return S_OK;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return S_OK;
}
CATCH_RETURN();