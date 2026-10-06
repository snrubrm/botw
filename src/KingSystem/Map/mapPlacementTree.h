#pragma once

#include <container/seadBuffer.h>
#include <container/seadFreeList.h>
#include <container/seadObjArray.h>
#include <math/seadVector.h>
#include <limits>
#include <thread/seadReadWriteLock.h>

using F32Limits = std::numeric_limits<f32>;

namespace ksys::map {

class Object;

// FIXME
class PlacementTree {
    struct TreeObject {
        u32 _0;
        u32 _4;
        u32 _8;
        f32 _c;
        f32 _10;
        f32 _14;
    };

public:
    PlacementTree();
    ~PlacementTree();

    void resetPlacementObjPtrs();
    // 0x71011ed9ec (CSV PlacementTree::calledForPlaceActor1; declared only; lane4 s45)
    void calledForPlaceActor1(Object* obj);
    u32 x_1(const sead::Vector3f& pos, int level) const;
    int sub_71011ED960(f32 distance) const;

    sead::Buffer<TreeObject> mBuffer{};
    sead::Buffer<u32*> mObjects{};
    sead::FreeList mFreeList;
    u32 _30{};
    f32 _34 = F32Limits::max();
    f32 _38 = F32Limits::max();
    f32 _3c = F32Limits::lowest();
    f32 _40 = F32Limits::lowest();
    sead::ReadWriteLock mLock{};
};

}  // namespace ksys::map
