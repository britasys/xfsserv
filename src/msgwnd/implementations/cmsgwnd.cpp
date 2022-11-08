
#include "cmsgwnd.hpp"

#include <sstream>

namespace __N_MSGWND__
{
    #define ASSERTINITIALIZED_VOID if (!this->IsInitialized()) { this->m_strLastError.assign("FAILED because MSGWND is not initialized"); return; }
    #define ASSERTINITIALIZED_BOOL if (!this->IsInitialized()) { this->m_strLastError.assign("FAILED because MSGWND is not initialized"); return false; }
    #define ASSERTINITIALIZED_INT if (!this->IsInitialized()) { this->m_strLastError.assign("FAILED because MSGWND is not initialized"); return 0; }

	WND_LAMBDA_MAP	CMSGWND::m_mapRegisteredCallbakFunctions;

	bool CMSGWND::Initialize(const MSGWND_INIT& init) noexcept
	{
		if (this->m_bInitialized)
		{
			this->m_strLastError.assign("CMSGWND::Initialize - FAILED because CMSGWND is already initialized");
			return false;
		}

		this->m_strWindowClass.assign(init.window_class);
		this->m_strWindowName.assign(init.window_name);

		this->m_bInitialized = true;

		return true;
	}

	bool CMSGWND::UnInitialize() noexcept
	{
		ASSERTINITIALIZED_BOOL

        this->DestroyWND();

		this->m_hThread.join();

		this->m_bInitialized = false;

		return true;
	}

    bool CMSGWND::CreateWND() noexcept
    {
        ASSERTINITIALIZED_BOOL

		std::promise<bool>_bPromiseInitialized;
		std::future<bool>_bFutureInitialized = _bPromiseInitialized.get_future();

		this->m_hThread = std::thread(&CMSGWND::CreateWND_thread, this, std::forward<std::promise<bool>>(_bPromiseInitialized));

		std::chrono::system_clock::time_point two_seconds_passed
			= std::chrono::system_clock::now() + std::chrono::seconds(2);

		if (std::future_status::ready == _bFutureInitialized.wait_until(two_seconds_passed))
			this->m_bInitialized = _bFutureInitialized.get();
		else
		{
			this->m_strLastError.assign("FAILED to start window - TIMEOUT");
			this->m_bInitialized = false;
            return false;
		}

        return true;
    }

    bool CMSGWND::DestroyWND() noexcept
    {
        ASSERTINITIALIZED_BOOL

		::PostThreadMessage(this->m_iThreadId, WM_QUIT, NULL, NULL);
		::PostThreadMessage(this->m_iThreadId, WM_CLOSE, NULL, NULL);

        return true;
    }

	WND_INDEX CMSGWND::RegisterCallbackFunction(const WND_HWND hwnd, WND_LAMBDA lambda) noexcept
	{
		ASSERTINITIALIZED_INT

		std::lock_guard<std::mutex>lock(m_PushMutex);

		int _index = m_iIndex;
		auto _mapRet = m_mapRegisteredCallbakFunctions.insert(std::make_pair(m_iIndex, std::make_pair(hwnd, lambda)));
		if (false == _mapRet.second)
		{
			this->m_strLastError.assign("CMSGWND::RegisterCallbackFunction - FAILED to insert into m_mapRegisteredCallbakFunctions");
			return -1;
		}

		this->m_iIndex++;
        
		return _index;
	}

	void CMSGWND::DeRegisterCallbackFunction(const WND_INDEX index) noexcept
	{
		ASSERTINITIALIZED_VOID

		std::lock_guard<std::mutex>_lock(m_PushMutex);
		try
		{
			auto it = m_mapRegisteredCallbakFunctions.find(index);
			if (it != m_mapRegisteredCallbakFunctions.end())
				m_mapRegisteredCallbakFunctions.erase(it);
		}
		catch (...)
		{
			this->m_strLastError.assign("EXCEPTION occurred while trying to erase");
			return;
		}
        
		return;
	}

	void CMSGWND::InformRegistredModules(const WND_HWND hwnd, const WND_MSG msg, const WND_WPARAM wparam, const WND_LPARAM lparam) noexcept
	{
		for (auto elem : m_mapRegisteredCallbakFunctions)
            if (elem.second.first == hwnd)
			    elem.second.second(hwnd, msg, wparam, lparam);
	}

	bool CMSGWND::CreateWND_thread(std::promise<bool>&& promise) noexcept
	{
		m_iThreadId = GetCurrentThreadId();

		// Register the Message structur
		HINSTANCE l_hInst = (HINSTANCE)GetCurrentProcess();

		WNDCLASSEXA wcex = {};
		wcex.cbSize = sizeof(WNDCLASSEXA);
		wcex.lpfnWndProc = (WNDPROC)CMSGWND::AppWndProc;
		wcex.hInstance = l_hInst;
		wcex.lpszClassName = this->m_strWindowClass.c_str();

		if (!RegisterClassExA(&wcex) && ERROR_CLASS_ALREADY_EXISTS != GetLastError())
		{
			this->m_strLastError.assign("RegisterClassEx FAILED to Register Window Class with error code: %d", GetLastError());
			promise.set_value(FALSE);
			return false;
		}

		// Create the main window.
		this->m_hwnd = CreateWindowExA(
			NULL,
			this->m_strWindowClass.c_str(),
			this->m_strWindowName.c_str(),
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			HWND_MESSAGE,
			NULL,
			NULL,
			NULL);

		// If the main window cannot be created, terminate the application.
		if (!m_hwnd)
		{
			this->m_strLastError.assign("CMSGWND::TTCreateWindow - CreateWindowEx FAILED to Create Window with error code: %d", GetLastError());
			UnregisterClassA(this->m_strWindowClass.c_str(), l_hInst);
			promise.set_value(FALSE);
			return false;
		}

		// promise
		promise.set_value(TRUE);

		// Start the message loop.
		MSG msg{ 0 };
        bool bRet{ true };
		while (bRet)
		{
            bRet = GetMessage(&msg, NULL, 0, 0);
			if (!bRet) {
				this->m_strLastError.assign("CMSGWND::TTCreateWindow FAILURE in GetMessage function");
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		if (!DestroyWindow(this->m_hwnd))
		{
            std::stringstream l_stream{};
            l_stream << "CMSGWND::TTDestroyWindow - DestroyWindow FAILED with error: " << GetLastError();
			this->m_strLastError.assign(l_stream.str());
			return false;
		}

		if (!UnregisterClassA(this->m_strWindowClass.c_str(), l_hInst))
		{
            std::stringstream l_stream{};
            l_stream << "CMSGWND::TTDestroyWindow - UnregisterClass FAILED with error" << GetLastError();
			this->m_strLastError.assign(l_stream.str());
			return false;
		}

		return true;
	}

	LRESULT CALLBACK CMSGWND::AppWndProc(HWND hWnd, UINT uInt, WPARAM wParam, LPARAM lParam)
	{
	//	cout << "CMSGWND::WndProc: " << uInt << endl;
	//	switch (uInt)
	//	{
	//	case WM_CREATE: cout << "CMSGWND::WndProc: WM_CREATE" << endl; break;
	//	case WM_QUIT: cout << "CMSGWND::WndProc: WM_QUIT" << endl; break;
	//	case TT_MSG_TERMINATE: /*PostQuitMessage(0);*/ cout << "CMSGWND::WndProc: TT_MSG_TERMINATE" << endl; break;
	//	case WM_NCDESTROY: /*PostQuitMessage(0);*/ cout << "CMSGWND::WndProc: WM_NCDESTROY" << endl; break;
	//	case WM_DESTROY:  /*PostQuitMessage(0);*/ cout << "CMSGWND::WndProc: WM_DESTROY" << endl; break;
	//	case WM_CLOSE: /*PostQuitMessage(0);*/ cout << "CMSGWND::WndProc: WM_CLOSE" << endl; break;
	//	}
		
		//if (WM_USER <= uInt && WM_USER + 100 >= uInt)
			for (auto elem : m_mapRegisteredCallbakFunctions)
                if (elem.second.first == (WND_HWND)hWnd)
				    if (NULL != elem.second.second)
                    {
				    	auto t = std::thread([elem, hWnd, uInt, wParam, lParam](){ elem.second.second((WND_HWND)hWnd, uInt, wParam, lParam); });
                        t.detach();
                    }
		
		return DefWindowProc(hWnd, uInt, wParam, lParam);
	}

	std::shared_ptr<IMSGWND> CreateMSGWND() noexcept
    {
        return std::make_shared<CMSGWND>();
    }
} // !__N_MSGWND__