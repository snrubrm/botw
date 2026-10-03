#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::act {

class Actor;

// Placeholder (RTTI static 0x71025ca5f8): the optional argument of Unk_71025b08f8::m4 (checked with
// a DynamicCast; its member at +0x8 is compared with 1).
class Unk_71025ca5f8;

// Placeholder name (RTTI static 0x71025b08f8; no vtable of its own in the binary). Abstract base of
// Unk_7102459df8 and the type returned by Actor vtable slot 126 (callers DynamicCast the result to
// Unk_7102459df8, e.g. BeltConveyor, Actor::isBgGroundHit-like helpers at 0x71007a40d0-0x71007a4864).
class Unk_71025b08f8 {
    SEAD_RTTI_BASE(Unk_71025b08f8)
public:
    explicit Unk_71025b08f8(Actor* actor) : mActor(actor) {}
    virtual ~Unk_71025b08f8() {}

    /*  4 */ virtual bool m4(sead::Heap* heap, const Unk_71025ca5f8* arg) = 0;
    /*  5 */ virtual void m5() = 0;
    /*  6 */ virtual void m6() = 0;
    /*  7 */ virtual void m7() = 0;
    /*  8 */ virtual void m8() = 0;
    /*  9 */ virtual bool m9() = 0;
    /* 10 */ virtual void m10() = 0;

    /* 0x08 */ Actor* mActor;
};

// Placeholder name (vtable 0x7102459df8, RTTI static 0x71025b08e8; functions 0x710079c5b0-
// 0x710079d0ec). Size 0x48, created by DynamicActor::initField858 (CSV) and in NPC/Horse/Weapon.
// TODO: incomplete.
class Unk_7102459df8 : public Unk_71025b08f8 {
    SEAD_RTTI_OVERRIDE(Unk_7102459df8, Unk_71025b08f8)
public:
    // vtable 0x7102459e60 (derived: 0x710245a0e0); 8 entries of 0x58 bytes at +0x8
    struct Unk_7102459e60 {
        struct Unk1 {
            u8 _0[0xc];
            sead::Vector3f _c;  // dotted with the actor's front (BattleCloseAction::m39)
            u8 _18[0x58 - 0x18];
        };

        virtual ~Unk_7102459e60();
        void sub_71007A5318();

        sead::SafeArray<Unk1, 8> mEntries;
        s32 mNum;
    };
    // vtable 0x7102459e88 (derived: 0x710245a028, 0x710245a000); 8 entries of 0x58 bytes at +0x8
    struct Unk_7102459e88 {
        struct Unk1 {
            sead::Vector3f _0;  // copied as a ground position by ForkOnEnterSwapDropTableActorBase
            sead::Vector3f _c;  // dotted with the gravity (KeeseDieSelect::m34)
            BaseProcLink _18;  // compared with Actor::getCreateArgBaseProcLink() (isBgGroundHit)
            u8 _28[0x58 - 0x28];
        };

        virtual ~Unk_7102459e88();
        void sub_710079FE9C();

        sead::SafeArray<Unk1, 8> mEntries;
        s32 mNum;
    };
    // dtor 0x710079d5a0; 8 entries of 0xb0 bytes
    struct Unk_710079d5a0 {
        // ctor 0x79fbe0.
        struct Unk1 : Struct8Base {
            Unk1();

            /* 0x50 */ BaseProcLink _50;
            /* 0x60 */ sead::Matrix34f _60 = sead::Matrix34f::ident;
            /* 0x90 */ sead::Vector3f _90 = sead::Vector3f::zero;
            /* 0x9c */ sead::Vector3f _9c = sead::Vector3f::ez;
            /* 0xa8 */ u32 _a8 = 0;
        };
        KSYS_CHECK_SIZE_NX150(Unk1, 0xb0);

        void sub_710079F600();

        sead::SafeArray<Unk1, 8> mEntries;
        s16 mNum;
        u8 _582;
        // cleared by BeltConveyor::leave_
        void* _588;
    };

    explicit Unk_7102459df8(Actor* actor) : Unk_71025b08f8(actor) {}
    ~Unk_7102459df8() override;

    bool m4(sead::Heap* heap, const Unk_71025ca5f8* arg) override;
    void m5() override;
    void m6() override;
    void m7() override {}
    void m8() override;
    bool m9() override;
    void m10() override;

    bool sub_710079CE78() const;
    s32 sub_710079CE98() const;
    bool sub_710079CEB0() const;
    s32 sub_710079CED0() const;
    bool sub_710079CEE8() const;
    s32 sub_710079CF08() const;
    bool sub_710079CF20() const;
    Unk_7102459e60::Unk1* sub_710079CF40(int idx) const;
    Unk_7102459e88::Unk1* sub_710079CF6C(int idx) const;
    Unk_710079d5a0::Unk1* sub_710079CF98(int idx) const;

    /* 0x10 */ Unk_7102459e60* _10 = nullptr;
    /* 0x18 */ Unk_7102459e88* _18 = nullptr;
    /* 0x20 */ Unk_710079d5a0* _20 = nullptr;
    /* 0x28 */ sead::Buffer<u8> _28;  // freed in m6 (element type unknown)
    /* 0x38 */ sead::Buffer<u8> _38;
};
KSYS_CHECK_SIZE_NX150(Unk_7102459df8, 0x48);

}  // namespace ksys::act
