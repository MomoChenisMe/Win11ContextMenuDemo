#include "pch.h"
#include "BaseExplorerCommand.h"
#include "Path.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

extern HMODULE g_module;

const wstring BaseExplorerCommand::GetMultiLanguageTitle()
{
	constexpr int bufferSize = 1024;
	WCHAR buffer[bufferSize];
	LoadStringW(g_module, titleResourceID, buffer, bufferSize);
	return wstring(buffer);
}

const wstring BaseExplorerCommand::GetIconPath()
{
	if (iconFileName == L"") {
		return L"";
	}
	return Win11ContextMenuDemo::Path::GetContextMenuDirectoryPath() + iconFileName;
}

void BaseExplorerCommand::SetTitleResourceID(UINT id)
{
	titleResourceID = id;
}

void BaseExplorerCommand::SetIconFileName(wstring fileName)
{
	iconFileName = fileName;
}

IFACEMETHODIMP BaseExplorerCommand::GetTitle(IShellItemArray* psiItemArray, LPWSTR* ppszName)
{
	UNREFERENCED_PARAMETER(psiItemArray);
	wstring title = GetMultiLanguageTitle();	
	SHStrDup(title.data(), ppszName);
	return S_OK;
}

IFACEMETHODIMP BaseExplorerCommand::GetIcon(IShellItemArray* psiItemArray, LPWSTR* ppszIcon)
{
	UNREFERENCED_PARAMETER(psiItemArray);
	wstring icon = GetIconPath();
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

IFACEMETHODIMP BaseExplorerCommand::Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept try
{
	UNREFERENCED_PARAMETER(psiItemArray);
	UNREFERENCED_PARAMETER(pbc);
	return S_OK;
}CATCH_RETURN();