#pragma once

#ifndef __H_IDISPATCHER__
#define __H_IDISPATCHER__

#include <string>
#include <memory>

namespace __N_DISPATCHER__
{
    class IDispatcher
    {
    private:
    protected:
    public:
        IDispatcher() = default;
        IDispatcher(const IDispatcher&) = delete;
        IDispatcher(IDispatcher&&) = delete;
        IDispatcher& operator = (const IDispatcher&) = delete;
        IDispatcher& operator = (IDispatcher&&) = delete;
        virtual ~IDispatcher() = default;

        virtual void dispatch(std::string, std::string&) const noexcept = 0;
    };

    std::shared_ptr<IDispatcher>createDispatcher() noexcept;
} // !__N_DISPATCHER__

#endif // !__H_IDISPATCHER__