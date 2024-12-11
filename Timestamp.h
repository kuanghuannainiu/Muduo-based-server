#ifndef TIMESTAMP_
#define TIMESTAMP_
#include <cstdint>
#include <string>

class Timestamp{
public:
    Timestamp() : microSecondsSinceEpoch_(0) {}
    Timestamp(int64_t microSecondsSinceEpoch) : microSecondsSinceEpoch_(microSecondsSinceEpoch) {}

    /*
        首先，静态成员函数可以在不创建类的实例的情况下被调用
        这对于获取时间戳这种可能不需要依赖特定对象状态的操作很方便。
    */
    static Timestamp now();
    std::string toString();
private:
    int64_t microSecondsSinceEpoch_;
};
#endif