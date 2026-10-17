#pragma once

#include <container/seadObjList.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
}

namespace ksys::act {

class LodState;

// Placeholder name (ctor 0x71011086dc, dtor 0x71011086f0, init 0x7101108774; size 0x30): created by
// LODMgr::init (LODMgr + 0x21b8). A sead::ObjList of 0x20-byte entries: the dtor is ObjList::freeBuffer and
// the init allocates the node pool (nodes of 0x30 bytes, list node at +0x20). Defined in the terrain TU
// (teraResourceNode.cpp).
struct Unk_71011086dcEntry {
    u8 _0[0x20];
};

class Unk_71011086dc : public sead::ObjList<Unk_71011086dcEntry> {
public:
    Unk_71011086dc();
    ~Unk_71011086dc();
    // 0x7101108774: allocates room for Terrain::_3d0 * sqrt(2) + 1 entries.
    void sub_7101108774(const sead::Heap* const& heap);
};
static_assert(sizeof(Unk_71011086dc) == 0x30);

// Name from the CSV (LODMgr::createInstance 0x710125184c, instance pointer 0x71026531b8; size 0x2a60;
// TU 0x7101250ed8 - 0x7101252xxx together with LodState's later methods). Only a few members are
// declared so far; the constructor (inlined in createInstance) is not decompiled.
class LODMgr {
    SEAD_SINGLETON_DISPOSER(LODMgr)
    LODMgr();
    virtual ~LODMgr();

public:
    void init(sead::Heap* heap);
    void initBeforeStageGenB();
    // 0x7101251b08 (CSV LODMgr::__auto3): `pos` + 5 along the look direction of the look-at camera.
    void sub_7101251B08(sead::Vector3f* pos);
    // 0x7101254328 (CSV name): requests a draw for every model in _1838.
    void requestDrawModels();

    /* 0x028 */ u8 _28[0x1028 - 0x28];
    /* 0x1028 */ s32 _1028;
    /* 0x102c */ u8 _102c[0x1830 - 0x102c];
    /* 0x1830 */ s32 _1830;
    /* 0x1838 */ sead::PtrArray<gsys::Model> _1838;
    /* 0x1848 */ u8 _1848[0x1878 - 0x1848];
    /* 0x1878 */ s32 _1878;
    /* 0x187c */ u8 _187c[0x1c80 - 0x187c];
    /* 0x1c80 */ u64 _1c80;
    /* 0x1c88 */ u8 _1c88[0x2110 - 0x1c88];
    /* 0x2110 */ sead::SafeArray<u32, 24> _2110;
    /* 0x2170 */ u8 _2170[0x21a0 - 0x2170];
    /* 0x21a0 */ s32 _21a0;
    /* 0x21a4 */ u8 _21a4[0x21b8 - 0x21a4];
    /* 0x21b8 */ Unk_71011086dc* _21b8;
    /* 0x21c0 */ u8 _21c0[0x2610 - 0x21c0];
    /* 0x2610 */ u64 _2610;
    /* 0x2618 */ u8 _2618[0x2a20 - 0x2618];
    /* 0x2a20 */ u64 _2a20;
    /* 0x2a28 */ u8 _2a28[0x2a60 - 0x2a28];
};
KSYS_CHECK_SIZE_NX150(LODMgr, 0x2a60);

}  // namespace ksys::act
