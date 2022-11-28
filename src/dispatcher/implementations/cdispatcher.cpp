
#include "cdispatcher.hpp"

#include <data.hpp>

#include <iostream>
#include <deque>

namespace __N_DISPATCHER__
{
    void CDispatcher::dispatch(std::string in, std::string& out) const noexcept
    {
        __N_DATA__::PACKET l_packet{ in };

        // TODO dispatch

        out.assign(l_packet.body.get());
    }

    std::shared_ptr<IDispatcher>createDispatcher() noexcept
    {
        return std::make_shared<CDispatcher>();
    }
} // !__N_DISPATCHER__