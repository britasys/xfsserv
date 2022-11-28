#pragma once

#ifndef __H_ISYSTEM__
#define __H_ISYSTEM__

#include <memory>

namespace __N_SYSTEM__
{
    class ISystem
    {
    private:
    protected:
    public:
        ISystem() = default;
        ISystem(const ISystem&) = delete;
        ISystem(ISystem&&) = delete;
        ISystem& operator = (const ISystem&) = default;
        ISystem& operator = (ISystem&&) = default;
        virtual ~ISystem() = default;

        virtual void run() const noexcept = 0;
    };

    std::shared_ptr<ISystem>createSystem() noexcept;
} // !__N_SYSTEM__

#endif // !__H_ISYSTEM__