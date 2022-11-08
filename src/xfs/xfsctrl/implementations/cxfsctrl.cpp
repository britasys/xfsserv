#include "./cxfsctrl.hpp"

#include <xfsapi_w/ixfsapi_w.hpp>

namespace __N_XFSCTRL__
{
    bool CXFSCTRL::Initialize() noexcept
    {
        if (this->m_bInitialized)
            return false;

        __N_MSGWND__::MSGWND_INIT l_init{};
        l_init.window_class.assign("xfs_wnd_class");
        l_init.window_name.assign("xfs_wnd_name");
        if (!this->m_hwnd->Initialize(l_init))
            return false;

        __N_XFSAPI_W__::WFSSTARTUP_P l_wfsstartup_p{};
        if (WFS_SUCCESS != __N_XFSAPI_W__::IXFSAPI_W::WFSStartUp(l_wfsstartup_p))
            return false;

        this->m_bInitialized = true;
        return true;
    }

    bool CXFSCTRL::UnInitialize() noexcept
    {
        if (!this->m_bInitialized)
            return false;            

        __N_XFSAPI_W__::IXFSAPI_W::WFSCleanUp();

        this->m_hwnd->UnInitialize();

        this->m_bInitialized = false;
        return true;
    }
} // !__N_XFSCTRL__