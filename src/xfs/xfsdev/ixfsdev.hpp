#pragma once

#ifndef __H_IXFSDEV__
#define __H_IXFSDEV__

#include <xfsapi_w/ixfsapi_w.hpp>
#include <xfsapi_w/xfsapi_w.hpp>

#include <deque>

namespace __N_XFSDEV__
{
    class IXFSDEV
    {
    private:
    protected:
        unsigned short m_hs{ 0 };
        std::deque<unsigned long>m_reqids{};

    public:
        IXFSDEV() = default;
        IXFSDEV(const IXFSDEV&) = delete;
        IXFSDEV(IXFSDEV&&) = delete;
        IXFSDEV& operator = (const IXFSDEV&) = delete;
        IXFSDEV& operator = (IXFSDEV&&) = delete;
        virtual ~IXFSDEV() noexcept { this->close_sync(); }

        // sync
        long open_sync(__N_XFSAPI_W__::WFSOPEN_P& wfsopen_p) noexcept;
        long close_sync() noexcept;

        template <typename T>
        long info_sync(const unsigned short, void*, T&, const unsigned short) noexcept;
        template <typename T>
        long execute_sync(const unsigned short, void*, T&, const unsigned short) noexcept;

        // async
        long open_async(__N_XFSAPI_W__::WFSOPEN_P& wfsopen_p, const unsigned int hwnd, unsigned long& reqid) noexcept;
        long close_async(const unsigned int hwnd, unsigned long& reqid) noexcept;

        long info_async(const unsigned short category, void* lpInput, const unsigned int hwnd, unsigned long& reqid, const unsigned short timeout) noexcept;
        long execute_async(const unsigned short command, void* lpInput, const unsigned int hwnd, unsigned long& reqid, const unsigned short timeout) noexcept;
    };

    template <typename T>
     long IXFSDEV::info_sync(const unsigned short category, void* lpInput, T& output, const unsigned short timeout) noexcept
     {
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

     std::shared_ptr<IXFSDEV> CreateXFSDevice() noexcept;
} // !__N_XFSDEV__

#endif // !__H_IXFSDEV__