#pragma once

#ifndef __H_CSYSTEM__
#define __H_CSYSTEM__

#include "../isystem.hpp"

namespace __N_SYSTEM__
{
    class CSystem : public ISystem
    {
    private:
    protected:
    public:
        CSystem() = default;
        CSystem(const CSystem&) = delete;
        CSystem(CSystem&&) = delete;
        CSystem& operator = (const CSystem&) = default;
        CSystem& operator = (CSystem&&) = default;
        virtual ~CSystem() = default;

        void run() const noexcept final;
    };
} // !__N_SYSTEM__

#endif // !__H_CSYSTEM__