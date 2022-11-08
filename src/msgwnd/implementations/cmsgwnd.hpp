#pragma once

#ifndef __H_CMSGWND__
#define __H_CMSGWND__

#include "../imsgwnd.hpp"

#include <functional>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <future>

#include <Windows.h>

namespace __N_MSGWND__
{
    using WND_LAMBDA_MAP = std::unordered_map<WND_INDEX, std::pair<WND_HWND, WND_LAMBDA>>;

	class CMSGWND : public IMSGWND
	{
	private:
		unsigned short  m_iIndex{ 0 };
		HWND		    m_hwnd{};
		unsigned int    m_iThreadId{ 0 };
		std::thread	    m_hThread{};
		std::string	    m_strWindowClass{};
		std::string	    m_strWindowName{};
		std::mutex	    m_PushMutex{};

		static WND_LAMBDA_MAP m_mapRegisteredCallbakFunctions;

		void InformRegistredModules(const WND_HWND, const WND_MSG, const WND_WPARAM, const WND_LPARAM) noexcept;
		bool CreateWND_thread(std::promise<bool>&&) noexcept;
        
		bool m_bInitialized{ false };
        std::string m_strLastError{};

	protected:
	public:
		CMSGWND() = default;
		CMSGWND(const CMSGWND&) = delete;
		CMSGWND(CMSGWND&&) = delete;
		CMSGWND& operator = (const CMSGWND&) = delete;
		CMSGWND& operator = (CMSGWND&&) = delete;
		virtual ~CMSGWND() { this->UnInitialize(); }

		bool Initialize(const MSGWND_INIT&) noexcept final;
		bool UnInitialize() noexcept final;

        bool CreateWND() noexcept final;
        bool DestroyWND() noexcept final;

		WND_INDEX RegisterCallbackFunction(const WND_HWND, WND_LAMBDA) noexcept final;
		void DeRegisterCallbackFunction(const WND_INDEX) noexcept final;
		WND_HWND GetHWND() const noexcept(false) final { return (WND_HWND)this->m_hwnd; }

		static LRESULT CALLBACK AppWndProc(HWND, UINT, WPARAM, LPARAM);
        
        std::string getLastError() const noexcept final { return this->m_strLastError; }
		bool IsInitialized() const noexcept final { return this->m_bInitialized; }
	};
} // !__N_MSGWND__

#endif // !__H_CMSGWND__
