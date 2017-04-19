#pragma once
#include <chrono>


template <typename T>
struct Clock {
    static double now(){
        return std::chrono::duration_cast<std::chrono::duration<T>>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

};


