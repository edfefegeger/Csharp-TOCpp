#ifndef CONFIG_HPP
#define CONFIG_HPP

class Config {
public:
    static Config& Instance() {
        static Config instance;
        return instance;
    }

    const int BufferSize = 1000000;
    const char ClientHost[16] = "64.226.68.205"; // IP-адрес в виде строки
    const int ClientPort = 443;
    const char encKey[45] = "RVsYtI+ZE5hrcKWxyBFv5MGMn5svmJ5oIz10D1/OC+w=";

private:
    Config() {}
};

#endif
