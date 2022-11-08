#pragma once

#ifndef __H_CXFSCTRL__
#define __H_CXFSCTRL__

#include "../ixfsctrl.hpp"

namespace __N_XFSCTRL__
{
    class CXFSCTRL : public IXFSCTRL
    {
    private:
    protected:
    public:
        CXFSCTRL() = default;
        CXFSCTRL(const CXFSCTRL&) = delete;
        CXFSCTRL(IXFSCTRL&&) = delete;
        CXFSCTRL& operator = (const CXFSCTRL&) = delete;
        CXFSCTRL& operator = (CXFSCTRL&&) = delete;

        virtual bool Initialize() noexcept = 0;
        virtual bool UnInitialize() noexcept = 0;
    };
} // !__N_XFSCTRL__


#endif // !__H_CXFSCTRL__