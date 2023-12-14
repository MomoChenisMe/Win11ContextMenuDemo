#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::Windows11Checker
{
    // 檢查當前操作系統是否為 Windows 11。
    // Returns true if the current operating system is Windows 11, false otherwise.
    // 此函數通過檢查系統註冊表中的版本號來判斷操作系統版本。
    // This function determines the operating system version by checking the version number in the system registry.
	bool IsWindows11();
}
