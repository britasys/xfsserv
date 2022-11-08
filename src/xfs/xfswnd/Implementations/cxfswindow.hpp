#pragma once

#ifndef __H_CXFSWINDOW__
#define __H_CXFSWINDOW__

#include "../ixfswindow.hpp"

#include <msgwnd/imsgwnd.hpp>

#include <memory>

namespace __N_XFSWINDOW__
{
	class CXFSWindow : public IXFSWindow
	{
	private:
        XFSWND_INIT m_init{};
		std::shared_ptr<__N_MSGWND__::IMSGWND> m_pMSGWND{ __N_MSGWND__::CreateMSGWND() };
        
        __N_MSGWND__::WND_LAMBDA m_lambda{ [this](
            const __N_MSGWND__::WND_HWND     hwnd, 
            const __N_MSGWND__::WND_MSG      msg, 
            const __N_MSGWND__::WND_WPARAM   wparam, 
            const __N_MSGWND__::WND_LPARAM   lparam) {
                EVT_CONTEXT context{};
                context.msg       = msg;
                context.lparam    = lparam;
                this->notify_subscribers(context);
                this->notify_lambdas(context);
        }};

	protected:
	public:
		CXFSWindow() = default;
		CXFSWindow(const CXFSWindow&) = delete;
		CXFSWindow(CXFSWindow&&) = delete;
		CXFSWindow& operator = (const CXFSWindow&) = delete;
		CXFSWindow& operator = (CXFSWindow&&) = delete;
		virtual ~CXFSWindow() = default;

        bool Initialize(const XFSWND_INIT&) noexcept final;
        bool UnInitialize() noexcept final;
        bool IsInitialized() const noexcept final { return this->m_pMSGWND->IsInitialized(); }

		int	 GetWindowHandle() const noexcept { return this->m_pMSGWND->GetHWND(); }
        virtual std::string GetLastError() const noexcept final { return this->m_pMSGWND->getLastError(); }
	};
} // !__N_XFSWINDOW__

#endif // !__H_CXFSWINDOW__