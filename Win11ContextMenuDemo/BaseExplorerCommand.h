#pragma once
#include "pch.h"

namespace Win11ContextMenuDemo::ExplorerCommand
{
	class BaseExplorerCommand : public winrt::implements<BaseExplorerCommand, IExplorerCommand>
	{
	public:
		virtual IFACEMETHODIMP GetTitle(IShellItemArray* psiItemArray, LPWSTR* ppszName);
		virtual IFACEMETHODIMP GetIcon(IShellItemArray* psiItemArray, LPWSTR* ppszIcon);
		virtual IFACEMETHODIMP GetToolTip(IShellItemArray* psiItemArray, LPWSTR* ppszInfotip);
		virtual IFACEMETHODIMP GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState);
		virtual IFACEMETHODIMP GetFlags(EXPCMDFLAGS* flags);
		virtual IFACEMETHODIMP GetCanonicalName(GUID* pguidCommandName);
		virtual IFACEMETHODIMP EnumSubCommands(IEnumExplorerCommand** ppEnum);

		virtual IFACEMETHODIMP Invoke(IShellItemArray* psiItemArray, IBindCtx* pbc) noexcept = 0;
	};
}