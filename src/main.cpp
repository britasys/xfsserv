#include <iostream>
#include <json.hpp>

#include <json.hpp>

using json = nlohmann::json;

int main()
{
    std::cout << "MAIN" << std::endl;

    json ex = json::parse(R"(
    {
        "pi": 3.141,
        "happy": true,
        "name": "Niels",
        "nothing": null,
        "answer": {
            "everything": 42
        },
        "list": [1, 0, 2],
        "object": {
          "currency": "USD",
          "value": 42.99
        }
    })");
    
    std::cout << ex["object"] << '\n';
    
    return 0;
}
