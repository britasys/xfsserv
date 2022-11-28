#include "cserver.hpp"

namespace __N_SERVER__
{
    void CServer::run(const INIT& init) noexcept
    {    
        auto l_controller_lambda = [init](__N_CPPSERV__::REQUEST& req, __N_CPPSERV__::RESPONSE& res) -> bool {
            init.lambda(req.body, res.body);
            res.status = __N_CPPSERV__::RESPONSE_HEADER_STATUS::CODE_200;
            res.field("content-type", "application/json");

            return true;
        };

        __N_CPPSERV__::ROUTER l_router{};
        l_router.path.assign("/");
        l_router.controller = l_controller_lambda;

        auto l_server = __N_CPPSERV__::SERVER<__N_CPPSERV__::HTTP>{};
        l_server.routers.push_back(l_router);
        l_server.run();
    }
    
    std::shared_ptr<IServer> createServer()
    {
        return std::make_shared<CServer>();
    }
} // !__N_SERVER__