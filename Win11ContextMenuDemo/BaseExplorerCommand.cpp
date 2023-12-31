#include "pch.h"
#include "BaseExplorerCommand.h"
#include "Path.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

extern HMODULE g_module;

wstring BaseExplorerCommand::GetCurrentExplorerPath()
{
	wstring path;
	if (m_Site) {
		winrt::com_ptr<IServiceProvider> serviceProvider;
		if (SUCCEEDED(m_Site->QueryInterface(IID_PPV_ARGS(&serviceProvider)))) {
			winrt::com_ptr<IShellBrowser> shellBrowser;
			if (SUCCEEDED(serviceProvider->QueryService(SID_SShellBrowser, IID_PPV_ARGS(&shellBrowser)))) {
				winrt::com_ptr<IShellView> shellView;
				if (SUCCEEDED(shellBrowser->QueryActiveShellView(shellView.put()))) {
					winrt::com_ptr<IFolderView> folderView;
					if (SUCCEEDED(shellView->QueryInterface(IID_PPV_ARGS(&folderView)))) {
						winrt::com_ptr<IPersistFolder2> persistFolder;
						if (SUCCEEDED(folderView->GetFolder(IID_PPV_ARGS(&persistFolder)))) {
							PIDLIST_ABSOLUTE curFolder;
							if (SUCCEEDED(persistFolder->GetCurFolder(&curFolder))) {
								wchar_t buf[MAX_PATH] = { 0 };
								if (SHGetPathFromIDList(curFolder, buf)) {
									path = buf;
								}
								CoTaskMemFree(curFolder);
							}
						}
					}
				}
			}
		}
	}
	return path;
}

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

HRESULT BaseExplorerCommand::SetSite(IUnknown* pUnkSite)
{
	m_Site = nullptr;
	if (pUnkSite != nullptr)
	{
		m_Site.copy_from(pUnkSite);
	}
	return S_OK;
}

HRESULT BaseExplorerCommand::GetSite(REFIID riid, void** ppvSite)
{
	return S_OK;
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