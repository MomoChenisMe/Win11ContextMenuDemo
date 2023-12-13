#include "pch.h"
#include "Windows11Checker.h"
#include "RegistryController.h"

bool Win11ContextMenuDemo::Windows11Checker::IsWindows11()
{
    Win11ContextMenuDemo::RegistryController::RegistryControllerClass registryControllerObj(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
    wstring buildNumberString = registryControllerObj.GetStringValue(L"CurrentBuildNumber");
    const int buildNumber = stoi(buildNumberString);
    return buildNumber >= 22000;
}