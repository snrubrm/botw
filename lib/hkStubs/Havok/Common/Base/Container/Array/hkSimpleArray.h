#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

// TYPE_SIMPLEARRAY reflection and NavMeshInstance finish constructor 152e4ec
// independently establish this borrowed pointer/count representation.
// It has no capacity, ownership flag or lifetime operation.
template <typename T>
struct hkSimpleArray {
    T* m_data;
    hkInt32 m_size;
};
static_assert(sizeof(hkSimpleArray<hkInt32>) == 0x10);
