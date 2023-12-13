#pragma once

#define WIN32_LEAN_AND_MEAN             // 從 Windows 標頭排除不常使用的項目

// Windows 標頭檔
#include <windows.h>
#include <aclapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <shobjidl_core.h>
#include <string>
#include <stdexcept>
#include <filesystem>

// WinRT
#include "winrt/base.h"
#include "winrt/Windows.ApplicationModel.h"
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Management.Deployment.h"

#include "wil\winrt.h"

// Link libraries
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "runtimeobject.lib")