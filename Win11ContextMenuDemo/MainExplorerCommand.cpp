#include "pch.h"
#include "MainExplorerCommand.h"
#include "EnumExplorerCommand.h"
#include "Sub1ExplorerCommand.h"

using namespace Win11ContextMenuDemo::ExplorerCommand;

MainExplorerCommand::MainExplorerCommand()
{
    SetTitleResourceID(ID_WIN11CONTEXTMENUDEMO_MAIN);
    SetIconFileName(L"\\Assets\\MainIcon.ico");
}

IFACEMETHODIMP MainExplorerCommand::GetFlags(EXPCMDFLAGS* flags)
{
    *flags = ECF_HASSUBCOMMANDS;
    return S_OK;
}

IFACEMETHODIMP MainExplorerCommand::EnumSubCommands(IEnumExplorerCommand** ppEnum)
{
    vector<winrt::com_ptr<IExplorerCommand>> subCommands;
    auto subCommand = winrt::make<Sub1ExplorerCommand>();
    subCommands.push_back(subCommand.as<IExplorerCommand>());
    auto enumCommands = winrt::make_self<EnumExplorerCommand>(move(subCommands));
    *ppEnum = enumCommands.detach();
    return S_OK;
}