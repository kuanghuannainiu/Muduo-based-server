#include <iostream>

#include "Logger.h"
#include "Timestamp.h"

Logger& Logger::getInstance(){
    static Logger logger;
    return logger;
}

void Logger::setLogLevel(int level){
    logLevel_ = level;
}

//TODO,將日誌信息輸出到指定位置
/*
    1. 輸出日誌等級
    2. 輸出時間
*/
void Logger::log(std::string msg){
    switch (logLevel_)
    {
    case INFO:
        std::cout << "[INFO]";
        break;
    case ERROR:
        std::cout << "[ERROR]";
        break;
    case FATAL:
        std::cout << "[FATAL]";
        break;
    case DEBUG:
        std::cout << "[DEBUG]";
        break;
    default:
        break;
    }

    std::cout << Timestamp::now().toString() << msg << "\n";
}
