#pragma once
#include "pch.h"

// Win11ContextMenuDemo::Paths 命名空間
// 提供各種與檔案路徑和執行檔名稱相關的實用功能。
// The Win11ContextMenuDemo::Paths namespace provides various utilities related to file paths and executable names.
namespace Win11ContextMenuDemo::Path
{
    // 獲取應用程序所在目錄的路徑。
    // Retrieves the path of the directory where the application is located.
    const wstring GetAppDirectoryPath();

    // 獲取上下文菜單相關文件所在目錄的路徑。
    // Retrieves the path of the directory where context menu related files are located.
    const wstring GetContextMenuDirectoryPath();

    // 獲取上下文菜單執行檔的完整路徑。
    // Retrieves the full path of the context menu executable.
    const wstring GetContextMenuExecutableFullPath();

    // 獲取當前執行模組的檔案名。
    // Retrieves the file name of the currently executing module.
    const wstring GetCurrentExecutableName();
}
