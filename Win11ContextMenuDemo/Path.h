#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::Path
{
    // 獲取應用程序所在目錄的路徑。
    // Retrieves the path of the directory where the application is located.
    const wstring GetAppDirectoryPath();

    // 獲取上下文選單相關文件所在目錄的路徑。
    // Retrieves the path of the directory where context menu related files are located.
    const wstring GetContextMenuDirectoryPath();

    // 獲取上下文選單執行檔的完整路徑。
    // Retrieves the full path of the context menu executable.
    const wstring GetContextMenuExecutableFullPath();

    // 獲取當前執行模組的檔案名。
    // Retrieves the file name of the currently executing module.
    const wstring GetCurrentExecutableName();
}
