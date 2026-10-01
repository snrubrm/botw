#include "KingSystem/Map/mapPlacementTree.h"
#include <basis/seadRawPrint.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadBitFlag.h>
#include <prim/seadMemUtil.h>

namespace ksys::map {

PlacementTree::PlacementTree() = default;

PlacementTree::~PlacementTree() {
    mBuffer.freeBuffer();
    mObjects.freeBuffer();
    delete[] static_cast<u8*>(mFreeList.work());
}

void PlacementTree::resetPlacementObjPtrs() {
    sead::MemUtil::fillZero(mObjects.getBufferPtr(), sizeof(u32*) * mObjects.size());
    mFreeList.setWork(mFreeList.work(), 0x10, _30);
}

u32 PlacementTree::x_1(const sead::Vector3f& pos, int level) const {
    const auto& obj = mBuffer[level];
    const f32 z = pos.z;
    const f32 size = obj._14;
    const f32 min_z = obj._10;

    int x = 0;
    if (obj._4 != 0) {
        const int i = (pos.x - obj._c) / size;
        if (i >= 0)
            x = i > int(obj._4 - 1) ? int(obj._4 - 1) : i;
    }

    int iz = 0;
    if (obj._8 != 0) {
        const int i = (z - min_z) / size;
        if (i >= 0)
            iz = i > int(obj._8 - 1) ? int(obj._8 - 1) : i;
    }

    return obj._0 + x + iz * obj._4;
}

int PlacementTree::sub_71011ED960(f32 distance) const {
    if (mBuffer[0]._14 > distance) {
        const int last = mBuffer.size() - 1;
        u32 x = sead::Mathf::floor(distance / mBuffer[last]._14);
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return last - sead::BitFlagUtil::countOnBit(x);
    }
    return 0;
}

}  // namespace ksys::map
