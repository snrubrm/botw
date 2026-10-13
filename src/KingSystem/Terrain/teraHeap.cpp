#include "KingSystem/Terrain/teraSystem.h"
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>

namespace ksys::tera {

sead::ExpHeap* sub_7101120314(u32 size, const sead::SafeString& name, sead::Heap* parent,
                            sead::Heap::HeapDirection direction) {
    const u32 max_size = u32(parent->getMaxAllocatableSize(8));
    return sead::ExpHeap::create(sead::Mathu::min(max_size, size), name, parent, 8, direction, false);
}

}  // namespace ksys::tera
