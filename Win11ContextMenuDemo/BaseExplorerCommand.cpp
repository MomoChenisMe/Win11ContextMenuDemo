#include "pch.h"
#include "BaseExplorerCommand.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

IFACEMETHODIMP BaseExplorerCommand::GetTitle(IShellItemArray* psiItemArray, LPWSTR* ppszName)
{
    UNREFERENCED_PARAMETER(psiItemArray);

    wstring title = L"Base Explorer Command";
    SHStrDup(title.data(), ppszName);

    return S_OK;
}

IFACEMETHODIMP BaseExplorerCommand::GetIcon(IShellItemArray* psiItemArray, LPWSTR* ppszIcon)
{
    UNREFERENCED_PARAMETER(psiItemArray);

    wstring icon = L"";
    SHStrDup(icon.data(), ppszIcon);

    return S_OK;
}

IFACEMETHODIMP BaseExplorerCommand::GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip)
{
    UNREFERENCED_PARAMETER(psiItemArray);
    UNREFERENCED_PARAMETER(ppszInfotip);

    return E_NOTIMPL;
}

IFACEMETHODIMP BaseExplorerCommand::GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState)
{
    UNREFERENCED_PARAMETER(fOkToBeSlow);

    *pCmdState = ECS_ENABLED;
    return S_OK;
}

IFACEMETHODIMP BaseExplorerCommand::GetFlags(EXPCMDFLAGS* flags)
{
    *flags = ECF_DEFAULT;
    return S_OK;
}

IFACEMETHODIMP BaseExplorerCommand::GetCanonicalName(GUID* pguidCommandName)
{
    *pguidCommandName = GUID_NULL;
    return S_OK;
}

IFACEMETHODIMP BaseExplorerCommand::EnumSubCommands(IEnumExplorerCommand** ppEnum)
{
    *ppEnum = nullptr;
    return E_NOTIMPL;
}