#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::ExplorerCommand
{
    // EnumExplorerCommand 是一個類，用於實現 IEnumExplorerCommand 介面，用於枚舉 IExplorerCommand 物件。
    // EnumExplorerCommand is a class that implements the IEnumExplorerCommand interface for enumerating IExplorerCommand objects.
    class EnumExplorerCommand : public winrt::implements<EnumExplorerCommand, IEnumExplorerCommand>
    {
    public:
        // 構造函數，接收一個 IExplorerCommand 物件列表。
        // Constructor that takes a list of IExplorerCommand objects.
        EnumExplorerCommand(std::vector<winrt::com_ptr<IExplorerCommand>> commands);

        // Next 方法用於獲取序列中的下一個命令。
        // The Next method is used to retrieve the next command in the sequence.
        IFACEMETHODIMP Next(ULONG celt, __out_ecount_part(celt, *pceltFetched) IExplorerCommand** apUICommand, __out_opt ULONG* pceltFetched);

        // Skip 方法用於跳過序列中的一定數量的命令。
        // The Skip method is used to skip a certain number of commands in the sequence.
        IFACEMETHODIMP Skip(ULONG celt);

        // Reset 方法重置枚舉器到初始狀態。
        // The Reset method resets the enumerator to its initial state.
        IFACEMETHODIMP Reset();

        // Clone 方法用於創建此枚舉器的一個副本。
        // The Clone method is used to create a copy of this enumerator.
        IFACEMETHODIMP Clone(__deref_out IEnumExplorerCommand** ppenum);

    private:
        // 儲存一系列的 IExplorerCommand 物件。
        // Stores a series of IExplorerCommand objects.
        std::vector<winrt::com_ptr<IExplorerCommand>> sub_commands;

        // 當前枚舉器的索引。
        // The current index of the enumerator.
        size_t currentIndex = 0;
    };
}
