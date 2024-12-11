#include <time.h>

#include "Timestamp.h"

Timestamp Timestamp::now(){
    return Timestamp(time(NULL));
}

std::string Timestamp::toString(){
    char buf[128] = { 0 };
    tm* timeinfo =  localtime(&microSecondsSinceEpoch_);
    snprintf(buf, 128, "%4d-%02d-%02d %02d:%02d:%02d",
        timeinfo->tm_year + 1900,
        timeinfo->tm_mon + 1,
        timeinfo->tm_mday + 1,
        timeinfo->tm_hour,
        timeinfo->tm_min,
        timeinfo->tm_sec);
    return buf;
}

// #include <iostream>
// int main(void){
//     Timestamp t1 = Timestamp::now();
//     std::cout << t1.toString() << "\n";
//     return 0;
// }