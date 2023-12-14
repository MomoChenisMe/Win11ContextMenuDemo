#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::ClassFactory
{
    // COMClassFactory 是一個模板類，用於實現 IClassFactory 介面。
    // COMClassFactory is a template class for implementing the IClassFactory interface.
    template<class T>
    struct COMClassFactory : winrt::implements<COMClassFactory<T>, IClassFactory>
    {
        // CreateInstance 用於創建 COM 物件的實例。
        // CreateInstance is used to create an instance of a COM object.
        IFACEMETHODIMP CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override try
        {
            *ppvObject = nullptr;

            // 如果 pUnkOuter 不是 null，則表示請求聚合，COM 規範不允許這樣做。
            // If pUnkOuter is not null, it indicates a request for aggregation, which is not allowed in COM.
            if (pUnkOuter)
            {
                return CLASS_E_NOAGGREGATION;
            }

            // 使用 winrt::make 創建 COM 物件並返回相應的介面。
            // Use winrt::make to create the COM object and return the requested interface.
            return winrt::make<T>().as(riid, ppvObject);
        }
        catch (...)
        {
            // 捕獲所有異常，並將它們轉換為合適的 HRESULT。
            // Catch all exceptions and convert them to an appropriate HRESULT.
            return winrt::to_hresult();
        }

        // LockServer 用於增加或減少伺服器的鎖定計數。
        // LockServer is used to increment or decrement the lock count of the server.
        IFACEMETHODIMP LockServer(BOOL) noexcept override
        {
            // 通常用於控制 DLL 是否可以被卸載，這裡簡單返回 S_OK。
            // Usually used to control whether the DLL can be unloaded, here we simply return S_OK.
            return S_OK;
        }
    };
}
