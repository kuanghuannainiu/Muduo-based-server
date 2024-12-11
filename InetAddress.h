#ifndef INETADDRESS_
#define INETADDRESS_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>

//封裝socket地址
class InetAddress{
public:
    explicit InetAddress(uint16_t port, std::string ip = "127.0.0.1");
    explicit InetAddress(const sockaddr_in &addr);
    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;
    const sockaddr_in* getsocketAddr() const;
private:
    sockaddr_in addr_;
};
#endif