#include "Dimension.h"
#include "../memory/offsets.h"

BlockSource* Dimension::getBlockSourceFromMainChunkSource() {
	return *(BlockSource**) ((uintptr_t) this + DIMENSION_BLOCK_SOURCE_FROM_MAIN_CHUNK_SOURCE_OFF);
}
