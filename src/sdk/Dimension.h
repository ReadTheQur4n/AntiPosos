#ifndef ANTIPOSOS_DIMENSION_H
#define ANTIPOSOS_DIMENSION_H

#include <cstdint>

class BlockSource;

class Dimension {
public:
	uintptr_t** vtable;
public:
	BlockSource* getBlockSourceFromMainChunkSource();
};


#endif //ANTIPOSOS_DIMENSION_H
