#pragma once
#include "pch.h"
#include "BaseExplorerCommand.h"

namespace Win11ContextMenuDemo::ExplorerCommand
{
    // MainExplorerCommand 是用於實現主選單的類別，繼承自 BaseExplorerCommand。
    // MainExplorerCommand is a class used to implement the main menu, inheriting from BaseExplorerCommand.
    class __declspec(uuid("15589FA6-768B-4826-97B8-D12DE265B3BB")) MainExplorerCommand : public BaseExplorerCommand
    {
    public:
        // 構造函數。
        // Constructor.
        MainExplorerCommand();

        // 獲取主選單的旗標。
        // Get the flags of the main menu.
        IFACEMETHODIMP GetFlags(EXPCMDFLAGS* flags) override;

        // 枚舉主選單的子命令。
        // Enumerate the sub-commands of the main menu.
        IFACEMETHODIMP EnumSubCommands(IEnumExplorerCommand** ppEnum) override;
    };
}
