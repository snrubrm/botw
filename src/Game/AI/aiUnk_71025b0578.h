#pragma once

#include <heap/seadHeap.h>
#include <math/seadBoundBox.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/Utils/Types.h"

// The two "vibrate checker" objects that actions / AIs share through AI tree variables
// (RefPosVibrateChecker / RefPosVibrateCheckerForAI and RefVelRotVibrateCheckerforAI); BackFlip,
// JumpMainRigidBody, MoveMainRidigBody, LevelFlyMoveBase, SandwormMove, SandwormNavMove,
// EnemyRangeKeepMove and NavMoveTarget keep a reference-counted holder of one of them.
// Placeholder names from their RTTI typeInfo statics. Each hierarchy is root Unk_71025afb58 <-
// intermediate class (no members known) <- the object; their constructors and destructors are
// inline (the vtable slots 2 / 3 are the root's trivial destructors).

// RTTI static 0x71025b0588 (parent: Unk_71025afb58).
class Unk_71025b0588 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b0588, Unk_71025afb58)
public:
};

// Placeholder name (methods 0x7100716408, 0x71007164ac, 0x7100716738, called with the object's +8 as
// `this`): the data of the reference-position vibrate checker. It is a (non-polymorphic) base of
// Unk_71025b0578: its inline constructor runs before the derived vtable store.
struct Unk_7100716408 {
    // 0x7100716408 (not decompiled): feeds a sample position.
    void sub_7100716408(const sead::Vector3f& pos);
    // BackFlip::enter_ (value 15.0f)
    void reset(f32 value) {
        _88 = value;
        _78 = value;
        _7c = 0;
        _80 = 0;
        _90.setUndef();
        _8c = false;
    }

    /* 0x00 */ u8 _0[0x78];
    /* 0x78 */ f32 _78 = 10.0f;
    /* 0x7c */ f32 _7c = 0.0f;
    /* 0x80 */ f32 _80 = 0.0f;
    /* 0x84 */ f32 _84 = 1.0f;
    /* 0x88 */ f32 _88 = 10.0f;
    /* 0x8c */ bool _8c = false;
    /* 0x90 */ sead::BoundBox3f _90;
};
KSYS_CHECK_SIZE_NX150(Unk_7100716408, 0xa8);

// RTTI static 0x71025b0578, vtable 0x71023698d0, size 0xb8: the reference-position vibrate checker.
class Unk_71025b0578 : public Unk_71025b0588, public Unk_7100716408 {
    SEAD_RTTI_OVERRIDE(Unk_71025b0578, Unk_71025b0588)
public:
    /* 0xb0 */ s32 mRefCount = 0;  // released by the holders' destructors
};
KSYS_CHECK_SIZE_NX150(Unk_71025b0578, 0xb8);

// RTTI static 0x71025b7698 (parent: Unk_71025afb58).
class Unk_71025b7698 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_71025b7698, Unk_71025afb58)
public:
};

// Placeholder name (method 0x710071f494, called with the object's +8 as `this`): the data of the
// velocity / rotation vibrate checker (a non-polymorphic base of Unk_71025b7688).
struct Unk_710071f494 {
    // 0x710071f494 (not decompiled): (count, interval).
    void sub_710071F494(s32 count, f32 interval);

    /* 0x00 */ f32 _0 = 5.0f;
    /* 0x04 */ f32 _4 = 5.0f;
    /* 0x08 */ s32 _8 = 5;
    /* 0x0c */ s32 _c = 5;
    /* 0x10 */ bool _10 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_710071f494, 0x14);

// RTTI static 0x71025b7688, vtable 0x71023ea3f8, size 0x20: the velocity / rotation vibrate checker
// (built inline by NavMoveTarget::init_ / EnemyRangeKeepMove::init_).
class Unk_71025b7688 : public Unk_71025b7698, public Unk_710071f494 {
    SEAD_RTTI_OVERRIDE(Unk_71025b7688, Unk_71025b7698)
public:
    /* 0x1c */ s32 mRefCount = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71025b7688, 0x20);

// Placeholder name (the out-of-line acquire is 0x71000b0800; the original's holder is a pointer to the
// AI tree variable slot): a reference to a shared `T` created on first use.
template <class T>
struct Unk_71000b0800 {
    ~Unk_71000b0800() { release(); }

    // Fills this with `var` and takes a reference to *var, creating the object if the slot is empty.
    bool acquire(sead::Heap* heap, Unk_71025afb58** var) {
        _0 = nullptr;
        if (!var)
            return false;
        if (auto* obj = *var) {
            auto* checker = sead::DynamicCast<T>(obj);
            if (!checker)
                return false;
            ++checker->mRefCount;
        } else {
            auto* checker = new (heap, 8) T;
            if (!checker)
                return false;
            checker->mRefCount = 1;
            *var = checker;
        }
        _0 = var;
        return true;
    }

    void release() {
        if (_0) {
            if (auto* checker = sead::DynamicCast<T>(*_0)) {
                if (checker->mRefCount > 0 && --checker->mRefCount <= 0) {
                    *_0 = nullptr;
                    delete checker;
                }
            }
            _0 = nullptr;
        }
    }

    Unk_71025afb58** _0 = nullptr;
};
