#pragma once

#ifndef __H_CDISPATCHER__
#define __H_CDISPATCHER__

#include "../idispatcher.hpp"

namespace __N_DISPATCHER__
{
    class CDispatcher : public IDispatcher
    {
    private:
    protected:
    public:
        CDispatcher() = default;
        CDispatcher(const CDispatcher&) = delete;
        CDispatcher(CDispatcher&&) = delete;
        CDispatcher& operator = (const CDispatcher&) = delete;
        CDispatcher& operator = (CDispatcher&&) = delete;
        virtual ~CDispatcher() = default;

        void dispatch(std::string, std::string&) const noexcept final;
    };
} // !__N_DISPATCHER__

#endif // !__H_CDISPATCHER__