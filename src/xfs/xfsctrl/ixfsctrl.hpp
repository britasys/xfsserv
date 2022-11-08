#pragma once

#ifndef __H_IXFSCTRL__
#define __H_IXFSCTRL__

#include <msgwnd/imsgwnd.hpp>
#include <xfsdev/ixfsdev.hpp>

namespace __N_XFSCTRL__
{
    #define ASSERT_INITILIAZED if (!this->IsInitialized()) return WFS_ERR_INTERNAL_ERROR;

    class IXFSCTRL
    {
    private:
    protected:
        bool m_bInitialized{ false };

        std::shared_ptr<__N_MSGWND__::IMSGWND> m_hwnd{ __N_MSGWND__::CreateMSGWND() };
        std::shared_ptr<__N_XFSDEV__::IXFSDEV> m_xfsdev{ __N_XFSDEV__::CreateXFSDevice() };

    public:
        IXFSCTRL() = default;
        IXFSCTRL(const IXFSCTRL&) = delete;
        IXFSCTRL(IXFSCTRL&&) = delete;
        IXFSCTRL& operator = (const IXFSCTRL&) = delete;
        IXFSCTRL& operator = (IXFSCTRL&&) = delete;

        virtual bool Initialize() noexcept = 0;
        virtual bool UnInitialize() noexcept = 0;
        bool IsInitialized() const noexcept { return this->m_bInitialized; }
    };
} // !__N_XFSCTRL__


#endif // !__H_IXFSCTRL__