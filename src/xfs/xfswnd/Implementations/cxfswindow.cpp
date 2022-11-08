#include "cxfswindow.hpp"

#include <memory>

namespace __N_XFSWINDOW__
{
	bool CXFSWindow::Initialize(const XFSWND_INIT& init) noexcept
	{
		if (this->m_pMSGWND->IsInitialized())
			return false;

        this->m_init = init;

        __N_MSGWND__::MSGWND_INIT l_init{};
		l_init.window_class.assign(init.window_class);
		l_init.window_name.assign(init.window_name);
		if (!this->m_pMSGWND->Initialize(l_init))
			return false;

		if (!this->m_pMSGWND->CreateWND())
        {
            this->m_pMSGWND->UnInitialize();
			return false;
        }

		if (-1 == this->m_pMSGWND->RegisterCallbackFunction(this->m_pMSGWND->GetHWND(), this->m_lambda))
            return false;

		return true;
	}

	bool CXFSWindow::UnInitialize() noexcept
	{
        this->m_pMSGWND->DestroyWND();

        if (!this->m_pMSGWND->UnInitialize())
            return false;

		return true;
	}

	std::shared_ptr<IXFSWindow>CreateXFSWindow() noexcept
	{
		return std::make_shared<CXFSWindow>();
	}
} // !__N_XFSWINDOW__
