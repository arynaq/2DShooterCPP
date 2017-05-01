#pragma once
#include "Component.hpp"
#include <iostream>
#include <string>

struct DirectionComponent : Component{
    enum Direction{
        NORTH = 0,
        SOUTH,
        WEST,
        EAST,
        UNDEFINED
    }direction;

	friend std::ostream& operator<<(std::ostream& out, const Direction dir_val){
    	const char* dir = 0;
#define PROCESS_DIR(d) case(d): dir = #d; break;
    	switch(dir_val){
    		PROCESS_DIR(NORTH);
    		PROCESS_DIR(SOUTH);
    		PROCESS_DIR(WEST);
    		PROCESS_DIR(EAST);
    		PROCESS_DIR(UNDEFINED);
    	}
#undef PROCESS_DIR
    	return out << dir;

    }
};
