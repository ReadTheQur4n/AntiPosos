#ifndef ANTIPOSOS_OFFSETS_H
#define ANTIPOSOS_OFFSETS_H

#define LR (((uintptr_t) __builtin_return_address(0)) - game.base_addr)
#define LOG_LR() LOG("LR=%lx", LR)

#define CAST_VT(ptr) (*(uintptr_t**) (ptr))
#define COMPARE_VT(a1, a2) ((a1) == (uintptr_t**) (game.base_addr + (a2)))

// You can replace 1.21.41 with 1.21.44 or add a new version (you have to find offsets yourself lol)
#include "version/arm64-v8a/1.21.44/offsets.h"

#endif //ANTIPOSOS_OFFSETS_H
