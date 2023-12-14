#include "pch.h"
#include "EnumExplorerCommand.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

EnumExplorerCommand::EnumExplorerCommand(vector<winrt::com_ptr<IExplorerCommand>> commands)
    : sub_commands(move(commands)) {}

IFACEMETHODIMP EnumExplorerCommand::Next(ULONG celt, __out_ecount_part(celt, *pceltFetched) IExplorerCommand** apUICommand, __out_opt ULONG* pceltFetched) {
    ULONG fetched = 0;
    while (currentIndex < sub_commands.size() && fetched < celt) {
        apUICommand[fetched] = sub_commands[currentIndex].get();
        apUICommand[fetched]->AddRef();
        ++fetched;
        ++currentIndex;
    }
    if (pceltFetched) *pceltFetched = fetched;
    return fetched == celt ? S_OK : S_FALSE;
}

IFACEMETHODIMP EnumExplorerCommand::Skip(ULONG celt) {
    currentIndex = min(currentIndex + celt, sub_commands.size());
    return S_OK;
}

IFACEMETHODIMP EnumExplorerCommand::Reset() {
    currentIndex = 0;
    return S_OK;
}

IFACEMETHODIMP EnumExplorerCommand::Clone(__deref_out IEnumExplorerCommand** ppenum) {
    auto clone = winrt::make_self<EnumExplorerCommand>(sub_commands);
    *ppenum = clone.detach();
    return S_OK;
}
