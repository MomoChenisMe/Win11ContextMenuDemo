#include "pch.h"
#include "InstallContextMenu.h"
#include "Windows11Checker.h"
#include "Path.h"
#include "RegistryController.h"
#include "MainExplorerCommand.h"

using namespace Win11ContextMenuDemo::RegistryController;
using namespace winrt::Windows::Management::Deployment;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;


const wstring CONTEXTMENUNAME = L"Win11ContextMenuDemo";
const wstring REGISTRYSHELLPATH = L"Software\\Classes\\*\\shell\\";
const wstring REGISTRYSHELLEXTENSIONPATH = L"Software\\Classes\\*\\shellex\\ContextMenuHandlers\\";
const wstring REGISTRYCLSIDPATH = L"Software\\Classes\\CLSID\\";
const wstring REGISTRYFILESHELLEXPATH = L"_file\\shellex";

inline Package GetSparsePackage(PackageManager& packageManager)
{
	try
	{
		auto packages = packageManager.FindPackagesForUser(L"");

		for (const auto& package : packages)
		{
			if (package.Id().Name() == CONTEXTMENUNAME)
			{
				return package;
			}
		}
	}
	catch (const winrt::hresult_error& e)
	{
		throw runtime_error("Failed to find sparse package: " + winrt::to_string(e.message()));
	}

	return nullptr;
}

inline IAsyncOperation<int32_t> UnRegisterSparsePackage()
{
	PackageManager packageManager;
	auto package = GetSparsePackage(packageManager);
	if (!package)
	{
		co_return S_FALSE;
	}

	winrt::hstring fullName = package.Id().FullName();
	auto deploymentOperation = co_await packageManager.RemovePackageAsync(fullName, RemovalOptions::None);
	//auto deployResult = deploymentOperation.get();

	if (!SUCCEEDED(deploymentOperation.ExtendedErrorCode()))
	{
		co_return deploymentOperation.ExtendedErrorCode();
	}

	co_return S_OK;
}

inline IAsyncOperation<int32_t> RegisterSparsePackage()
{
	const wstring contextMenuDirectoryPath = Win11ContextMenuDemo::Path::GetContextMenuDirectoryPath();
	const wstring sparsePackageFullPath = contextMenuDirectoryPath + L"\\" + CONTEXTMENUNAME + L".msix";

	Uri externalLocationUri(contextMenuDirectoryPath);
	Uri packageUri(sparsePackageFullPath);

	AddPackageOptions options;
	options.ExternalLocationUri(externalLocationUri);
	options.AllowUnsigned(true);

	PackageManager packageManager;
	auto deploymentOperation = co_await packageManager.AddPackageByUriAsync(packageUri, options);
	//auto deployResult = deploymentOperation.get();

	if (!SUCCEEDED(deploymentOperation.ExtendedErrorCode()))
	{
		co_return deploymentOperation.ExtendedErrorCode();
	}

	co_return S_OK;
}

inline IAsyncAction RegisterSparsePackageProgram()
{
	winrt::init_apartment();
	co_await UnRegisterSparsePackage();
	co_await RegisterSparsePackage();
}

inline wstring GetCLSIDString()
{
	const auto uuid = __uuidof(Win11ContextMenuDemo::ExplorerCommand::MainExplorerCommand);
	LPOLESTR clsidString = nullptr;
	HRESULT result = StringFromCLSID(uuid, &clsidString);
	if (FAILED(result))
	{
		throw runtime_error("Failed to parse GUID to string");
	}
	wstring clsid(clsidString);
	CoTaskMemFree(clsidString);
	return clsid;
}

inline HRESULT RegisterContextMenu()
{
	const wstring clsid = GetCLSIDString();
	RegistryControllerClass regExtController(HKEY_LOCAL_MACHINE, REGISTRYSHELLPATH + CONTEXTMENUNAME, KEY_READ | KEY_WRITE, true);
	regExtController.SetStringValue(L"", CONTEXTMENUNAME + L" - Context menu Demo");
	regExtController.SetStringValue(L"ExplorerCommandHandler", clsid);
	regExtController.SetStringValue(L"NeverDefault", L"");

	RegistryControllerClass regClsidController(HKEY_LOCAL_MACHINE, REGISTRYCLSIDPATH + clsid, KEY_READ | KEY_WRITE, true);
	regClsidController.SetStringValue(L"", CONTEXTMENUNAME);

	RegistryControllerClass regInProcController = regClsidController.GetSubKey(L"InProcServer32", true);
	regInProcController.SetStringValue(L"", Win11ContextMenuDemo::Path::GetContextMenuExecutableFullPath());
	regInProcController.SetStringValue(L"ThreadingModel", L"Apartment");

	return S_OK;
}

inline HRESULT UnRegisterContextMenu()
{
	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, REGISTRYSHELLPATH + CONTEXTMENUNAME))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, REGISTRYSHELLPATH + CONTEXTMENUNAME, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, REGISTRYSHELLEXTENSIONPATH + CONTEXTMENUNAME))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, REGISTRYSHELLEXTENSIONPATH + CONTEXTMENUNAME, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, CONTEXTMENUNAME + REGISTRYFILESHELLEXPATH))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, CONTEXTMENUNAME + REGISTRYFILESHELLEXPATH, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	const wstring clsid = GetCLSIDString();
	if (RegistryControllerClass::KeyExists(HKEY_LOCAL_MACHINE, REGISTRYCLSIDPATH + clsid))
	{
		RegistryControllerClass regController(HKEY_LOCAL_MACHINE, REGISTRYCLSIDPATH + clsid, KEY_READ | KEY_WRITE);
		regController.DeleteKey();
	}

	return S_OK;
}

HRESULT Win11ContextMenuDemo::InstallContextMenu::InstallContextMenu()
{
	HRESULT result;

	if (Win11ContextMenuDemo::Windows11Checker::IsWindows11())
	{
		UnRegisterContextMenu();

		RegisterSparsePackageProgram().get();
	}

	result = RegisterContextMenu();

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);

	return S_OK;
}

HRESULT Win11ContextMenuDemo::InstallContextMenu::UnInstallContextMenu()
{
	HRESULT result;

	result = UnRegisterContextMenu();

	if (result != S_OK)
	{
		return result;
	}

	if (Win11ContextMenuDemo::Windows11Checker::IsWindows11())
	{
		result = UnRegisterSparsePackage().get();

		if (result != S_OK)
		{
			return result;
		}
	}

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);

	return S_OK;
}
