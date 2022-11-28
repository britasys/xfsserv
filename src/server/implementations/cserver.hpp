#pragma once

#ifndef __H_CSERVER__
#define __H_CSERVER__

#include "../iserver.hpp"

#include <cppserv.hpp>

namespace __N_SERVER__
{
    class CServer : public IServer
    {
    private:
        std::shared_ptr<__N_CPPSERV__::SERVER<__N_CPPSERV__::HTTP>> m_cppserv{ std::make_shared<__N_CPPSERV__::SERVER<__N_CPPSERV__::HTTP>>() };

    protected:
    public:
        CServer() = default;
        CServer(const CServer&) = delete;
        CServer(CServer&&) = delete;
        CServer& operator = (const CServer&) = delete;
        CServer& operator = (CServer&&) = delete;
        virtual ~CServer() = default;

        void run(const INIT& init) noexcept final;
    };
} // !__N_SERVER__

#endif // !__H_CSERVER__