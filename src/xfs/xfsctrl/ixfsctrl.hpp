#pragma once

#ifndef __H_IXFSCTRL__
#define __H_IXFSCTRL__

namespace __N_XFSCTRL__
{
    class IXFSCTRL
    {
    private:
    protected:
        bool m_bInitialized{ false };

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