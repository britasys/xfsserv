#pragma once

#ifndef __H_ISERVER__
#define __H_ISERVER__

#include <functional>
#include <memory>
#include <string>

namespace __N_SERVER__
{
    using LAMBDA = std::function<void(std::string, std::string&)>;

    typedef struct _init
    {
        std::string address{ "0.0.0.0" };
        unsigned short port{ 8080 };
        LAMBDA lambda;
    } INIT, * LPINIT;

    class IServer
    {
    private:
    protected:
        INIT m_init{};

    public:
        IServer() = default;
        IServer(const IServer&) = delete;
        IServer(IServer&&) = delete;
        IServer& operator = (const IServer&) = delete;
        IServer& operator = (IServer&&) = delete;
        virtual ~IServer() = default;

        virtual void run(const INIT& init) noexcept = 0;
    };

    std::shared_ptr<IServer> createServer();
} // !__N_SERVER__

#endif // !__H_ISERVER__