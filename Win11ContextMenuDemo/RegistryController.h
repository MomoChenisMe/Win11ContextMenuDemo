#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::RegistryController
{
    // RegistryControllerClass 用於訪問和修改 Windows 註冊表。
    // RegistryControllerClass is used for accessing and modifying the Windows registry.
    class RegistryControllerClass
    {
    public:
        // 構造函數初始化註冊表控制器，可選擇創建不存在的鍵。
        // Constructor initializes the registry controller, with an option to create the key if it does not exist.
        RegistryControllerClass(HKEY hKey, const wstring& subKey = L"", REGSAM access = KEY_READ, bool createIfMissing = false);

        // 析構函數確保註冊表鍵被適當關閉。
        // Destructor ensures the registry key is properly closed.
        ~RegistryControllerClass();

        // 檢查指定的註冊表鍵是否存在。
        // Checks if a specified registry key exists.
        static bool KeyExists(HKEY hKey, const wstring& subKey);

        // 檢查註冊表中是否存在指定的值。
        // Checks if a specified value exists in the registry.
        bool ValueExists(const wstring& valueName) const;

        // 獲取指定子鍵的 RegistryControllerClass 實例。
        // Retrieves a RegistryControllerClass instance for a specified subkey.
        RegistryControllerClass GetSubKey(const wstring& subKey, bool createIfMissing = false) const;

        // 獲取 DWORD 類型的註冊表值。
        // Retrieves a DWORD type registry value.
        DWORD GetDwordValue(const wstring& valueName);

        // 獲取字符串類型的註冊表值。
        // Retrieves a string type registry value.
        wstring GetStringValue(const wstring& valueName);

        // 設置 DWORD 類型的註冊表值。
        // Sets a DWORD type registry value.
        void SetDwordValue(const wstring& valueName, DWORD value);

        // 設置字符串類型的註冊表值。
        // Sets a string type registry value.
        void SetStringValue(const wstring& valueName, const wstring& value);

        // 刪除當前操作的註冊表鍵。
        // Deletes the currently operated registry key.
        void DeleteKey();
    private:
        // 打開或創建註冊表鍵。
        // Opens or creates a registry key.
        void OpenOrCreateKey(HKEY hKey, const wstring& subKey, REGSAM access, bool createIfMissing);

        // 關閉註冊表鍵。
        // Closes the registry key.
        void CloseKey();

        // 確保註冊表鍵已打開。
        // Ensures the registry key is open.
        void EnsureKeyIsOpen() const;

        // 拋出 Windows API 最後一個錯誤的詳細信息。
        // Throws detailed information about the Windows API last error.
        void ThrowLastError(const std::string& message) const;

        // 註冊表鍵的句柄。
        // Handle to the registry key.
        HKEY m_hKey;

        // 訪問註冊表鍵的權限。
        // Access rights for the registry key.
        REGSAM m_regsam;

        // 原始註冊表鍵的句柄。
        // Handle to the original registry key.
        HKEY m_originalHKey;

        // 原始子鍵路徑。
        // Original subkey path.
        wstring m_originalSubKey;
    };
}
