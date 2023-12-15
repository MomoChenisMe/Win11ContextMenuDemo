#pragma once
#include "pch.h"
#include "BaseExplorerCommand.h"

namespace Win11ContextMenuDemo::ExplorerCommand
{
    // Sub1ExplorerCommand 是一個實現子選單的類別，繼承自 BaseExplorerCommand。
    // Sub1ExplorerCommand is a class that implements a submenu, inheriting from BaseExplorerCommand.
    class Sub1ExplorerCommand : public BaseExplorerCommand
    {
    public:
        // 構造函數。
        // Constructor.
        Sub1ExplorerCommand();

        // 執行子選單的命令邏輯。
        // Execute the command logic of the submenu.
        IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept override;
    };
}
