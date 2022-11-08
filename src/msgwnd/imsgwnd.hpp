#pragma once

#ifndef __H_IMSGWND__
#define __H_IMSGWND__

#include <functional>
#include <string>
#include <memory>

namespace __N_MSGWND__
{
    using WND_HWND      = int;
    using WND_MSG       = unsigned int;
    using WND_WPARAM    = int;
    using WND_LPARAM    = int;
	using WND_LAMBDA    = std::function<void(const WND_HWND, const WND_MSG, const WND_WPARAM, const WND_LPARAM)>;
    using WND_INDEX     = unsigned short int;

    typedef struct _cppmsgwnd_init
    {
        std::string window_class{};
        std::string window_name{};
    } MSGWND_INIT, * LP_MSGWND_INIT;

	class IMSGWND
	{
	private:
	protected:
	public:
		IMSGWND() = default;
		IMSGWND(const IMSGWND&) = delete;
		IMSGWND(IMSGWND&&) = delete;
		IMSGWND& operator = (const IMSGWND&) = delete;
		IMSGWND& operator = (IMSGWND&&) = delete;
		virtual ~IMSGWND() = default;

		virtual bool Initialize(const MSGWND_INIT&) noexcept = 0;
		virtual bool UnInitialize() noexcept = 0;
		virtual bool IsInitialized() const noexcept = 0;

        virtual bool CreateWND() noexcept = 0;
        virtual bool DestroyWND() noexcept = 0;

		virtual WND_INDEX RegisterCallbackFunction(const WND_HWND, WND_LAMBDA) noexcept = 0;
		virtual void DeRegisterCallbackFunction(const WND_INDEX) noexcept = 0;
		virtual WND_HWND GetHWND() const noexcept(false) = 0;

        virtual std::string getLastError() const noexcept = 0;
	};

	std::shared_ptr<IMSGWND> CreateMSGWND() noexcept;
} // !__N_CPPMSGWND__

#endif // !__N_MSGWND__