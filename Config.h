#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

class Config {
public:
    static Config& Instance() {
        static Config instance;
        return instance;
    }

    int BufferSize = 1000000;
    std::string ClientHost = "64.226.68.205";
    int ClientPort = 443;
    const char* encKey = "RVsYtI+ZE5hrcKWxyBFv5MGMn5svmJ5oIz10D1/OC+w=";

private:
    Config() {}
};

#endif
