#include "pch.h"
#include "RegistryController.h"
#include <sstream>

using namespace Win11ContextMenuDemo::RegistryController;

RegistryControllerClass::RegistryControllerClass(HKEY hKey, const std::wstring& subKey, REGSAM access, bool createIfMissing)
    : m_hKey(nullptr), m_regsam(access), m_originalHKey(hKey), m_originalSubKey(subKey)
{
    OpenOrCreateKey(hKey, subKey, access, createIfMissing);
}

RegistryControllerClass::~RegistryControllerClass()
{
    CloseKey();
}

void RegistryControllerClass::OpenOrCreateKey(HKEY hKey, const std::wstring& subKey, REGSAM access, bool createIfMissing)
{
    LONG status = RegOpenKeyExW(hKey, subKey.c_str(), 0, access, &m_hKey);
    if (status != ERROR_SUCCESS)
    {
        if (createIfMissing)
        {
            DWORD disposition = 0;
            status = RegCreateKeyExW(hKey, subKey.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &m_hKey, &disposition);
        }
        if (status != ERROR_SUCCESS)
        {
            ThrowLastError("Failed to open or create registry key");
        }
    }
}

void RegistryControllerClass::CloseKey()
{
    if (m_hKey != nullptr)
    {
        RegCloseKey(m_hKey);
        m_hKey = nullptr;
    }
}

bool RegistryControllerClass::KeyExists(HKEY hKey, const std::wstring& subKey)
{
    HKEY result;
    LONG status = RegOpenKeyExW(hKey, subKey.c_str(), 0, KEY_READ, &result);
    if (status == ERROR_SUCCESS)
    {
        RegCloseKey(result);
        return true;
    }
    return false;
}

bool RegistryControllerClass::ValueExists(const std::wstring& valueName) const
{
    DWORD type, size = 0;
    LONG status = RegQueryValueExW(m_hKey, valueName.c_str(), nullptr, &type, nullptr, &size);
    return status == ERROR_SUCCESS;
}

RegistryControllerClass RegistryControllerClass::GetSubKey(const std::wstring& subKey, bool createIfMissing) const
{
    if (m_hKey == nullptr)
    {
        throw std::runtime_error("Registry key is not open.");
    }

    return RegistryControllerClass(m_hKey, subKey, m_regsam, createIfMissing);
}

DWORD RegistryControllerClass::GetDwordValue(const std::wstring& valueName)
{
    EnsureKeyIsOpen();
    DWORD value = 0;
    DWORD dataSize = sizeof(DWORD);
    LONG status = RegGetValueW(m_hKey, nullptr, valueName.c_str(), RRF_RT_REG_DWORD, nullptr, &value, &dataSize);
    if (status != ERROR_SUCCESS)
    {
        ThrowLastError("Failed to get DWORD registry value.");
    }
    return value;
}

std::wstring RegistryControllerClass::GetStringValue(const std::wstring& valueName)
{
    EnsureKeyIsOpen();
    DWORD dataSize = 0;
    RegGetValueW(m_hKey, nullptr, valueName.c_str(), RRF_RT_REG_SZ, nullptr, nullptr, &dataSize);
    std::wstring value(dataSize / sizeof(wchar_t), L'\0');
    LONG status = RegGetValueW(m_hKey, nullptr, valueName.c_str(), RRF_RT_REG_SZ, nullptr, reinterpret_cast<BYTE*>(&value[0]), &dataSize);
    if (status != ERROR_SUCCESS)
    {
        ThrowLastError("Failed to get string registry value.");
    }
    return value;
}

void RegistryControllerClass::SetDwordValue(const std::wstring& valueName, DWORD value)
{
    EnsureKeyIsOpen();
    LONG status = RegSetValueExW(m_hKey, valueName.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(DWORD));
    if (status != ERROR_SUCCESS)
    {
        ThrowLastError("Failed to set DWORD registry value.");
    }
}

void RegistryControllerClass::SetStringValue(const std::wstring& valueName, const std::wstring& value)
{
    EnsureKeyIsOpen();
    LONG status = RegSetValueExW(m_hKey, valueName.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), (value.size() + 1) * sizeof(wchar_t));
    if (status != ERROR_SUCCESS)
    {
        ThrowLastError("Failed to set string registry value.");
    }
}

void RegistryControllerClass::DeleteKey()
{
    if (m_hKey == nullptr)
    {
        throw runtime_error("Registry key is not open.");
    }

    LONG status = RegDeleteTreeW(m_originalHKey, m_originalSubKey.c_str());
    if (status != ERROR_SUCCESS)
    {
        ThrowLastError("Failed to delete registry key.");
    }

    CloseKey();
}

void RegistryControllerClass::ThrowLastError(const std::string& message) const
{
    std::ostringstream oss;
    oss << message << ". Windows API Error code: " << GetLastError();
    throw runtime_error(oss.str());
}

void RegistryControllerClass::EnsureKeyIsOpen() const
{
    if (m_hKey == nullptr)
    {
        throw std::runtime_error("Registry key is not open.");
    }
}
