#pragma once

#ifndef __H_DATA__
#define __H_DATA__

#include <json.hpp>
using json = nlohmann::json;

#include <string>
#include <typeinfo>
#include <stdexcept>

namespace __N_DATA__
{
    // json ex = json::parse(R"(
    // {
    //     "pi": 3.141,
    //     "happy": true,
    //     "name": "Niels",
    //     "nothing": null,
    //     "answer": {
    //         "everything": 42
    //     },
    //     "list": [1, 0, 2],
    //     "object": {
    //       "currency": "USD",
    //       "value": 42.99
    //     }
    // })");    
    // std::cout << ex["object"].is_object() << '\n';

    typedef struct _data
    {
    private:
        json m_data{};

    protected:
    public:
        _data() = default;
        _data(const _data&) = default;
        _data(_data&&) = default;
        _data& operator = (const _data&) = default;
        _data& operator = (_data&&) = default;
        virtual ~_data() = default;

        explicit _data(const std::string data)
        {
            this->m_data = json::parse(data);
        }

        template <typename T>
        auto get(const std::string key) noexcept(false) -> T
        {
            return this->m_data[key].get<T>();
        }

        auto get(const std::string key) noexcept(false)
        {
            return this->m_data[key];
        }

        std::string get() const noexcept
        {
            return this->m_data.dump();
        }
    } DATA, * LPDATA, ** LPPDATA;

    typedef struct _packet
    {
        _packet() = delete;
        _packet(const _packet&) = default;
        _packet(_packet&&) = default;
        _packet& operator = (const _packet&) = default;
        _packet& operator = (_packet&&) = default;
        virtual ~_packet() = default;

        explicit _packet(const std::string data)
        {
            DATA l_packet{ data };

            this->id = l_packet.get<unsigned long int>("id");
            this->cmd = l_packet.get<unsigned long int>("cmd");

            this->body = DATA{ l_packet.get("body").dump() };
        }

        unsigned long int id{ 0 };
        unsigned long int cmd{ 0 };
        DATA body{};
    } PACKET, * LPPACKET, ** LPPPACKET;
} // !__N_DATA__

#endif // !__H_DATA__