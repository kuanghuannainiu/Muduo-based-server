#pragma once
#include <string>

#include "noncopyable.h"

//定義宏，因爲用戶只需要關注日誌的輸出即可，而像日誌的獲取以及日誌的等級直接定義爲宏即可
// LOG_INFO("%s %d", arg1, arg2),注意多行使用do-while，每一行後面需要加"\"，並且後面不能跟空格
#define LOG_INFO(LogmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(INFO); \
        char buf[1024] = { 0 }; \
        logger.log(buf); \
    }while(0)

#define LOG_ERROR(LogmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        logger.log(buf); \
    }while(0)

#define LOG_FATAL(LogmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        logger.log(buf); \
    }while(0)

/*
    由於系統中DEBUG級別的信息很多，所以開啓DEBUG導致IO打印信息很多，影響效率
    所以對於DEBUG級別默認關閉，然後定義一個宏可以去開啓
*/
#ifdef _MUDUOBUG_
#define LOG_DEBUG(LogmsgFormat, ...) \
    do \
    { \
        Logger &logger = Logger::getInstance(); \
        logger.setLogLevel(DEBUG); \
        char buf[1024] = {0}; \
        logger.log(buf); \
    }while(0)
#else
#define LOG_DEBUG(LogmsgFormat, ...)
#endif

//定義日誌級別： INFO、ERROR、FATAL、DEBUG
enum LogLevel{
    INFO,
    ERROR,
    FATAL,
    DEBUG
};

//輸出一個日誌類，注意是一個單例
class Logger : noncopyable{
public:
    static Logger& getInstance();
    void setLogLevel(int level);
    void log(std::string msg); //  寫日誌
private:
    Logger();
    int logLevel_;  //爲了和系統變量不衝突

};