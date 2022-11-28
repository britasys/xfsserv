#include "csystem.hpp"

#include <server/iserver.hpp>
#include <dispatcher/idispatcher.hpp>

#include <iostream>

namespace __N_SYSTEM__
{
    void CSystem::run() const noexcept
    {    
        auto l_dispatcher = __N_DISPATCHER__::createDispatcher();

        auto l_lambda = [l_dispatcher](const std::string in, std::string& out) {
            std::cout << "Packet recieved" << in << std::endl;

            l_dispatcher->dispatch(in, out);
        };

        auto l_server{ __N_SERVER__::createServer() };

        __N_SERVER__::INIT l_init{};
        l_init.lambda = l_lambda;
        l_server->run(l_init);
    }

    std::shared_ptr<ISystem>createSystem() noexcept
    {
        return std::make_shared<CSystem>();
    }
} // !__N_SYSTEM__