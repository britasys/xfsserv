#include "./cxfsctrl.hpp"

namespace __N_XFSCTRL__
{
    bool CXFSCTRL::Initialize() noexcept
    {
        if (this->m_bInitialized)
            return false;

        this->m_bInitialized = true;
        return true;
    }

    bool CXFSCTRL::UnInitialize() noexcept
    {
        if (!this->m_bInitialized)
            return false;
            
        this->m_bInitialized = false;
        return true;
    }
} // !__N_XFSCTRL__