#pragma once
#include "pch.h"
#include "BaseExplorerCommand.h"

namespace Win11ContextMenuDemo::ExplorerCommand
{
	class __declspec(uuid("15589FA6-768B-4826-97B8-D12DE265B3BB")) MainExplorerCommand : public BaseExplorerCommand
	{
	public:
		IFACEMETHODIMP GetTitle(IShellItemArray* psiItemArray, LPWSTR* ppszName) override;
		IFACEMETHODIMP GetIcon(IShellItemArray* psiItemArray, LPWSTR* ppszIcon) override;
		//IFACEMETHODIMP GetFlags(EXPCMDFLAGS* flags) override;
		IFACEMETHODIMP EnumSubCommands(IEnumExplorerCommand** ppEnum) override;
		IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept override;
	};
}