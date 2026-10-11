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
    // The 0x10-byte free-list values hold an Object and the next value; insertion
    // at 11ED9EC and the independent traversal at 11EDD98 use both pointers.
    struct Node {
        Object* object;
        Node* next;
    };
    static_assert(sizeof(Node) == 0x10);

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

    // Placeholder arguments of the init function 0x71011ed47c (CSV PlacementTree::x): the map bounds (x / z min and
    // max), the cell size of the finest level and a node count; PlacementMgr::initPlacementTree passes the constants.
    struct InitArg {
        sead::Heap* heap;
        f32 min_x;
        f32 min_z;
        f32 max_x;
        f32 max_z;
        f32 cell_size;
        u32 num_nodes;
    };
    void sub_71011ED47C(const InitArg& arg);

    void resetPlacementObjPtrs();
    void calledForPlaceActor1(Object* obj);
    // 11EDD98 passes two Vector2f outputs, a cell index and the expansion distance.
    u32 sub_71011EDB78(sead::Vector2f* min, sead::Vector2f* max, u32 cell, f32 distance) const;
    u32 x_1(const sead::Vector3f& pos, int level) const;
    int sub_71011ED960(f32 distance) const;

    sead::Buffer<TreeObject> mBuffer{};
    sead::Buffer<Node*> mObjects{};
    sead::FreeList mFreeList;
    u32 _30{};
    f32 _34 = F32Limits::max();
    f32 _38 = F32Limits::max();
    f32 _3c = F32Limits::lowest();
    f32 _40 = F32Limits::lowest();
    sead::ReadWriteLock mLock{};
};

}  // namespace ksys::map
