#include <Havok/Common/Base/Memory/Router/hkMemoryRouter.h>

void* sub_710158B834(hk_size_t numBytes) {
    return hkMemoryRouter::getInstance().heap().blockAlloc(numBytes);
}

void sub_710158B870(void* block, hk_size_t numBytes) {
    hkMemoryRouter::getInstance().heap().blockFree(block, numBytes);
}
