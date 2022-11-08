#include "./ixfsdev.hpp"

namespace __N_IXFSDEV__
{
    bool IXFSDEV::Initialize() noexcept
    {
        if (this->m_bInitialized)
            return false;

        __N_MSGWND__::MSGWND_INIT l_init{};
        l_init.window_class.assign("xfs_wnd_class");
        l_init.window_name.assign("xfs_wnd_name");
        if (!this->m_hwnd->Initialize(l_init))
            return false;

        this->m_bInitialized = true;
        return true;
    }

    bool IXFSDEV::UnInitialize() noexcept
    {
        if (!this->m_bInitialized)
            return false;

        this->m_hwnd->UnInitialize();

        this->m_bInitialized = false;
        return true;
    }

    long IXFSDEV::open_sync(__N_XFSAPI_W__::WFSOPEN_P& wfsopen_p) noexcept
    {
        ASSERT_INITILIAZED

        return __N_XFSAPI_W__::IXFSAPI_W::WFSOpen(wfsopen_p);
    }

    long IXFSDEV::close_sync(__N_XFSAPI_W__::WFSCLOSE_P& wfsclose_p) noexcept
    {
        ASSERT_INITILIAZED

        return __N_XFSAPI_W__::IXFSAPI_W::WFSClose(wfsclose_p);
    }

    long IXFSDEV::open_async(__N_XFSAPI_W__::WFSOPEN_P& wfsopen, const unsigned int hwnd, unsigned long& reqid) noexcept
    {
        ASSERT_INITILIAZED

        return __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncOpen(wfsopen, (HWND)hwnd, reqid);
    }
    
    long IXFSDEV::close_async(__N_XFSAPI_W__::WFSCLOSE_P& wfsclose_p, const unsigned int hwnd, unsigned long& reqid) noexcept
    {
        ASSERT_INITILIAZED

        return __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncClose(wfsclose_p, (HWND)hwnd, reqid);
    }

     long IXFSDEV::info_async(const unsigned short category, void* lpInput, unsigned long& reqid, const unsigned short timeout) noexcept
     {
        ASSERT_INITILIAZED

        __N_XFSAPI_W__::WFSGETINFO_P l_wfsgetinfo_p{};
        l_wfsgetinfo_p.hService = this->m_hs;
        l_wfsgetinfo_p.dwCategory = category;
        l_wfsgetinfo_p.lpQueryDetails = lpInput;
        l_wfsgetinfo_p.dwTimeOut = timeout;
        
        HRESULT l_result = __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncGetInfo(l_wfsgetinfo_p, (HWND)this->m_hwnd->GetHWND(), (REQUESTID)reqid);
        if (WFS_SUCCESS == l_result)
            m_reqids.push_back(reqid);

        return l_result;
    }

     long IXFSDEV::execute_async(const unsigned short command, void* lpInput, unsigned long& reqid, const unsigned short timeout) noexcept
     {
        ASSERT_INITILIAZED

        __N_XFSAPI_W__::WFSEXECUTE_P l_wfsexecute_p{};
        l_wfsexecute_p.hService = this->m_hs;
        l_wfsexecute_p.dwCommand = command;
        l_wfsexecute_p.lpCmdData = lpInput;
        l_wfsexecute_p.dwTimeOut = timeout;
        
        HRESULT l_result =  __N_XFSAPI_W__::IXFSAPI_W::WFSAsyncExecute(l_wfsexecute_p, (HWND)this->m_hwnd->GetHWND(), (REQUESTID)reqid);
        if (WFS_SUCCESS == l_result)
            m_reqids.push_back(reqid);

        return l_result;
    }
} // !__N_IXFSDEV__