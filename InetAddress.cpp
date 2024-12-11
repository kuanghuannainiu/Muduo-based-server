#include <string.h>
#include <strings.h>

#include "InetAddress.h"

//這裏的代碼不用動
InetAddress::InetAddress(uint16_t port, std::string ip){
    bzero(&addr_, sizeof(addr_));   //清零
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
}

InetAddress::InetAddress(const sockaddr_in &addr) : addr_(addr) {}

std::string InetAddress::toIp() const{
    char buf[128] = { 0 };
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof(buf));    //網絡字節序轉化本地字節序
    return buf;
}

uint16_t InetAddress::toPort() const{
    return ntohs(addr_.sin_port);
}

std::string InetAddress::toIpPort() const{
    char buf[128] = { 0 };
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof(buf));
    size_t len = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    /*
        組裝字符串，相當與將ip::poet組裝到一起.
        %u 表示无符号整数格式
        sprintf(buf + len, ":%u", port); 的作用是将格式化后的字符串写入到 buf 数组从 len 这个位置
        sprintf 不检查目标缓冲区的大小，可能会导致缓冲区溢出。
        snprintf 接受一个缓冲区大小参数，并且保证不会写入超过这个大小的内容，从而避免缓冲区溢出问题。
    */
    sprintf(buf + len, ":%u", port);
    // char ip[128] = { 0 };
    // strcpy(ip, buf);
    // snprintf(buf, sizeof(buf), "%s:%u", ip, port);
    return buf;
}

const sockaddr_in* InetAddress::getsocketAddr() const{
    return &addr_;
}

// #include <iostream>
// int main(void){
//     InetAddress addr(8080);
//     std::cout << addr.toIp() << "\n";
//     std::cout << addr.toPort() << "\n";
//     std::cout << addr.toIpPort() << "\n";
//     return 0;
// }