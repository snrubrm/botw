#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class RigidBody;
}

namespace sead {
class Heap;
}

// Placeholder name = vtable address (0x710250d530; constructor 0x71010f122c, D1 0x71010f1254, D0
// 0x71010f12b4). A directional-wind box: a box rigid body (`mBody`) plus the wind element created in the
// chemical manager's holder (`mElement`, the 0x71010f1d1c ElementDirectionalWind creation); embedded in
// AscendingCurrent (+0x28). The destructor removes the body from the world and deletes it. No RTTI.
class Unk_710250d530 {
public:
    // Placeholder (the ElementDirectionalWind created by 0x71010f1d1c; only the fields the setters write are modeled).
    struct Element {
        u8 _0[0x1c];
        /* 0x1c */ sead::Vector3f mDirection;
        u8 _28[0x3c - 0x28];
        /* 0x3c */ f32 mSpeed;
    };
    // Placeholder (the holder `mElement` points to; the wind element is at +0x10). The setters read the pointer twice
    // (null check, then use), which only an atomic (volatile) load does.
    struct ElementHolder {
        u8 _0[0x10];
        /* 0x10 */ sead::Atomic<Element*> mWind;
    };

    Unk_710250d530();
    virtual ~Unk_710250d530();

    // 0x71010f13ac (declared only; 540 B): creates the box body at `pos` (size `size`, orientation / extra
    // vector `a3`, `a5` null in the only caller).
    void sub_71010F13AC(const sead::Vector3f* pos, const sead::Vector3f* size, const sead::Vector3f* a3,
                        sead::Heap* heap, void* a5);
    // 0x71010f1344 (declared only): sets the wind speed (also on the created element).
    void sub_71010F1344(f32 speed);
    // 0x71010f1364 (declared only): sets the wind direction (also on the created element).
    void sub_71010F1364(const sead::Vector3f* direction);
    // 0x71010f15c8 (declared only): sets the box body's transform (a BoxRigidBody only).
    void sub_71010F15C8(const sead::Matrix34f* mtx);
    // 0x71010f1314: true without a body, else whether the body is no longer in the world (WindBoxPlace::updateForPreDelete)
    bool sub_71010F1314();
    // 0x71010f1664 (declared only): sets the box body's extents (a BoxRigidBody only).
    void sub_71010F1664(const sead::Vector3f* extents);
    // 0x71010f16fc (declared only; 256 B): adds the body to the world and creates the wind element.
    void sub_71010F16FC();
    // 0x71010f17fc (declared only; 124 B): removes the element and the body from the world.
    void sub_71010F17FC(bool remove_links);

    /* 0x08 */ ElementHolder* mElement = nullptr;
    /* 0x10 */ ksys::phys::RigidBody* mBody = nullptr;
    /* 0x18 */ f32 mSpeed = 20.0f;
    /* 0x1c */ sead::Vector3f mDirection{1.0f, 0.0f, 0.0f};
    /* 0x28 */ u32 _28 = 0;
    /* 0x2c */ bool _2c = false;  // copied to the element (+0x68); AscendingCurrentFixedSize::init_ sets it from DisableInDemo
    /* 0x2d */ bool mEnabled = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710250d530, 0x30);
