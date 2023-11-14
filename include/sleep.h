#ifndef SLEEP_H
#define SLEEP_H

#include <chrono>
#include <thread>

namespace sleep{
void milliseconds(int time){
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
void seconds(int time){
    std::this_thread::sleep_for(std::chrono::seconds(time));
}
void minutes(int time){
    std::this_thread::sleep_for(std::chrono::minutes(time));
}
}
#endif