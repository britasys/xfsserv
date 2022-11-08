#pragma once

#ifndef __H_IXFSDEV__
#define __H_IXFSDEV__

#include <msgwnd/imsgwnd.hpp>
#include <xfsapi_w/ixfsapi_w.hpp>
#include <xfsapi_w/xfsapi_w.hpp>

#include <deque>

namespace __N_IXFSDEV__
{
    #define ASSERT_INITILIAZED if (!this->IsInitialized()) return WFS_ERR_INTERNAL_ERROR;

    class IXFSDEV
    {
    private:
    protected:
        bool m_bInitialized{ false };

        unsigned short m_hs{ 0 };
        std::shared_ptr<__N_MSGWND__::IMSGWND> m_hwnd{ __N_MSGWND__::CreateMSGWND() };

        std::deque<unsigned long>m_reqids{};

    public:
        IXFSDEV() = default;
        IXFSDEV(const IXFSDEV&) = delete;
        IXFSDEV(IXFSDEV&&) = delete;
        IXFSDEV& operator = (const IXFSDEV&) = delete;
        IXFSDEV& operator = (IXFSDEV&&) = delete;
        virtual ~IXFSDEV() noexcept { this->UnInitialize(); }

        bool Initialize() noexcept;
        bool UnInitialize() noexcept;
        bool IsInitialized() const noexcept { return this->m_bInitialized; }

        // sync
        long open_sync(__N_XFSAPI_W__::WFSOPEN_P&) noexcept;
        long close_sync(__N_XFSAPI_W__::WFSCLOSE_P&) noexcept;

        template <typename T>
        long info_sync(const unsigned short, void*, T&, const unsigned short) noexcept;
        template <typename T>
        long execute_sync(const unsigned short, void*, T&, const unsigned short) noexcept;

        // async
        long open_async(__N_XFSAPI_W__::WFSOPEN_P&, const unsigned int, unsigned long&) noexcept;
        long close_async(__N_XFSAPI_W__::WFSCLOSE_P&, const unsigned int, unsigned long&) noexcept;

        long info_async(const unsigned short, void*, unsigned long&, const unsigned short) noexcept;
        long execute_async(const unsigned short, void*, unsigned long&, const unsigned short) noexcept;
    };    

    template <typename T>
     long IXFSDEV::info_sync(const unsigned short category, void* lpInput, T& output, const unsigned short timeout) noexcept
     {
        ASSERT_INITILIAZED

        __N_XFSAPI_W__::WFSGETINFO_P l_wfsgetinfo_p{};
        l_wfsgetinfo_p.hService = this->m_hs;
        l_wfsgetinfo_p.dwCategory = category;
        l_wfsgetinfo_p.lpQueryDetails = lpInput;
        l_wfsgetinfo_p.dwTimeOut = timeout;
        
        __N_XFSAPI_W__::WFSRESULT_W l_wfsresult_w{};
        HRESULT l_result = __N_XFSAPI_W__::IXFSAPI_W::WFSGetInfo(l_wfsgetinfo_p, l_wfsresult_w);
        if (WFS_SUCCESS == l_result && WFS_SUCCESS != l_wfsresult_w.liResult)
            output.assign(l_wfsresult_w.lpBuffer);

        __N_XFSAPI_W__::WFSFREERESULT_P l_wfsfreeresult_p{};
        l_wfsfreeresult_p.wfsresult_w = l_wfsresult_w;
        __N_XFSAPI_W__::IXFSAPI_W::WFSFreeResult(l_wfsfreeresult_p);

        return l_result;
     }

    template <typename T>
     long IXFSDEV::execute_sync(const unsigned short command, void* lpInput, T& output, const unsigned short timeout) noexcept
     {
        ASSERT_INITILIAZED

        __N_XFSAPI_W__::WFSEXECUTE_P l_wfsexecute_p{};
        l_wfsexecute_p.hService = this->m_hs;
        l_wfsexecute_p.dwCommand = command;
        l_wfsexecute_p.lpCmdData = lpInput;
        l_wfsexecute_p.dwTimeOut = timeout;
        
        __N_XFSAPI_W__::WFSRESULT_W l_wfsresult_w{};
        HRESULT l_result = __N_XFSAPI_W__::IXFSAPI_W::WFSExecute(l_wfsexecute_p, l_wfsresult_w);
        if (WFS_SUCCESS == l_result && WFS_SUCCESS != l_wfsresult_w.liResult)
            output.assign(l_wfsresult_w.lpBuffer);

        __N_XFSAPI_W__::WFSFREERESULT_P l_wfsfreeresult_p{};
        l_wfsfreeresult_p.wfsresult_w = l_wfsresult_w;
        __N_XFSAPI_W__::IXFSAPI_W::WFSFreeResult(l_wfsfreeresult_p);

        return l_result;
     }
} // !__N_IXFSDEV__

#endif // !__H_IXFSDEV__