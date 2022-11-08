#include "./ixfsdev.hpp"

namespace __N_XFSDEV__
{
    long IXFSDEV::open_sync(__N_XFSAPI_W__::WFSOPEN_P& wfsopen_p) noexcept
    {
        auto l_result = __N_XFSAPI_W__::IXFSAPI_W::WFSOpen(wfsopen_p);
        if (WFS_SUCCESS == l_result)
            this->m_hs = wfsopen_p.hService;

        return l_result;
    }

    long IXFSDEV::close_sync() noexcept
    {        
        __N_XFSAPI_W__::WFSCLOSE_P l_wfsclose_p{};
        l_wfsclose_p.hService = this->m_hs;
        return __N_XFSAPI_W__::IXFSAPI_W::WFSClose(l_wfsclose_p);
    }

    long IXFSDEV::open_async(__N_XFSAPI_W__::WFSOPEN_P& wfsopen_p, const unsigned int hwnd, unsigned long& reqid) noexcept
    {
        return __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncOpen(wfsopen_p, (HWND)hwnd, reqid);
    }
    
    long IXFSDEV::close_async(const unsigned int hwnd, unsigned long& reqid) noexcept
    {
        __N_XFSAPI_W__::WFSCLOSE_P l_wfsclose_p{};
        l_wfsclose_p.hService = this->m_hs;
        return __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncClose(l_wfsclose_p, (HWND)hwnd, reqid);
    }

     long IXFSDEV::info_async(const unsigned short category, void* lpInput, const unsigned int hwnd, unsigned long& reqid, const unsigned short timeout) noexcept
     {
        __N_XFSAPI_W__::WFSGETINFO_P l_wfsgetinfo_p{};
        l_wfsgetinfo_p.hService = this->m_hs;
        l_wfsgetinfo_p.dwCategory = category;
        l_wfsgetinfo_p.lpQueryDetails = lpInput;
        l_wfsgetinfo_p.dwTimeOut = timeout;
        
        HRESULT l_result = __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncGetInfo(l_wfsgetinfo_p, (HWND)hwnd, (REQUESTID)reqid);
        if (WFS_SUCCESS == l_result)
            m_reqids.push_back(reqid);

        return l_result;
    }

     long IXFSDEV::execute_async(const unsigned short command, void* lpInput, const unsigned int hwnd, unsigned long& reqid, const unsigned short timeout) noexcept
     {
        __N_XFSAPI_W__::WFSEXECUTE_P l_wfsexecute_p{};
        l_wfsexecute_p.hService = this->m_hs;
        l_wfsexecute_p.dwCommand = command;
        l_wfsexecute_p.lpCmdData = lpInput;
        l_wfsexecute_p.dwTimeOut = timeout;
        
        HRESULT l_result =  __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncExecute(l_wfsexecute_p, (HWND)hwnd, (REQUESTID)reqid);
        if (WFS_SUCCESS == l_result)
            m_reqids.push_back(reqid);

        return l_result;
    }
    
     std::shared_ptr<IXFSDEV> CreateXFSDevice() noexcept
     {
        return std::make_shared<IXFSDEV>();
     }
} // !__N_XFSDEV__