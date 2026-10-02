#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

namespace ksys::act {

class Actor;
class AttackSensor;
class AttackSensor2;

// CSV name (ctor 0x7a0460, resetFlags 0x7a0498, operator= 0x7a0b0c): the common 0x50-byte head of
// the attack / contact info entries (ActorAtk::Struct7::AttackInfo, ActorAtk::Unk_710079e64c::Unk1,
// Unk_7102459df8::Unk_710079d5a0::Unk1), which are reset with resetFlags() and a link reset.
struct Struct8Base {
    Struct8Base();
    Struct8Base& operator=(const Struct8Base& other);

    void resetFlags();

    /* 0x00 */ sead::Vector3f _0{0, 0, 0};
    // Position (copied out by DamageMgrSword::getAttackPos for AttackInfo 0).
    /* 0x0c */ sead::Vector3f _c{0, 0, 1};
    /* 0x18 */ u32 _18 = 0;  // flags (cleared by resetFlags; bits 0-1 tested by LynelRepeatAttack::calc_)
    /* 0x20 */ phys::MaterialMask _20;
    /* 0x38 */ phys::MaterialMask _38;
};
KSYS_CHECK_SIZE_NX150(Struct8Base, 0x50);

// Placeholder name (RTTI static 0x71025ae640; it has no vtable of its own in the binary). Abstract
// base of ActorAtk and the type returned by Actor::getAtk() (vtable slot 125): callers
// DynamicCast the result to ActorAtk.
class Unk_71025ae640 {
    SEAD_RTTI_BASE(Unk_71025ae640)
public:
    explicit Unk_71025ae640(Actor* actor) : mActor(actor) {}
    virtual ~Unk_71025ae640() = default;

    /*  4 */ virtual bool init(sead::Heap* heap) = 0;
    /*  5 */ virtual void m5() = 0;
    /*  6 */ virtual void free() = 0;
    /*  7 */ virtual void m7() = 0;
    /*  8 */ virtual void m8() = 0;
    /*  9 */ virtual void m9() = 0;
    /* 10 */ virtual bool m10() = 0;
    /* 11 */ virtual bool hasAttackInfoMaybe() = 0;
    /* 12 */ virtual bool reset() = 0;
    /* 13 */ virtual void m13() = 0;

    /* 0x08 */ Actor* mActor;
};

// Placeholder name (ActorAtk's secondary vtable 0x7102459f48: only a virtual destructor).
class Unk_7102459f48 {
public:
    virtual ~Unk_7102459f48() {}
};

// Name from the CSV (ActorAtk::*, 0x710079d76c-0x710079e56c). Size 0x80 (ActorAtk::makeForActor).
// vtable 0x7102459ec8, RTTI static 0x71025ae630. Attack sensor state of an actor.
// TODO: incomplete.
class ActorAtk : public Unk_71025ae640, public Unk_7102459f48 {
    SEAD_RTTI_OVERRIDE(ActorAtk, Unk_71025ae640)
public:
    // CSV Struct7 (dtor 0x710079e574): 8 attack infos (0x78 bytes each) and their count.
    struct Struct7 {
        // ctor 0x79f28c (CSV AttackInfo::ctor).
        struct AttackInfo : Struct8Base {
            AttackInfo();

            /* 0x50 */ BaseProcLink _50;
            /* 0x60 */ u32 _60 = 0x38;
            /* 0x68 */ sead::SafeString _68 = sead::SafeString::cEmptyString;
        struct AttackInfo {
            u8 _0[0x18];
            u32 _18;  // flags (bits 0-1 tested by LynelRepeatAttack::calc_, SeqPursuit::calc_)
            u8 _1c[0x78 - 0x1c];
        };
        KSYS_CHECK_SIZE_NX150(AttackInfo, 0x78);

        void reset();
        void sub_710079E958(sead::Buffer<u8>* buffer, Actor* actor);
        void sub_710079EFBC(sead::Buffer<u8>* buffer, Actor* actor);

        sead::SafeArray<AttackInfo, 8> mAttackInfos;
        s16 mNumAttackInfo;
        u8 _3c2;
    };
    // dtor 0x710079e64c: 8 entries of 0x100 bytes and their count.
    struct Unk_710079e64c {
        // ctor 0x7a1f04 (0x58-0x88 left uninitialised).
        struct Unk1 : Struct8Base {
            Unk1();

            /* 0x50 */ s32 _50 = 0;
            /* 0x54 */ u32 _54 = 0;
            /* 0x58 */ u8 _58[0x88 - 0x58];
            /* 0x88 */ u32 _88 = 0;
            /* 0x8c */ u32 _8c = 0;
            /* 0x90 */ u32 _90 = 0;
            /* 0x94 */ u32 _94 = 0;
            /* 0x98 */ u32 _98 = 0;
            /* 0x9c */ f32 _9c = 1.0;
            /* 0xa0 */ u32 _a0 = 0;
            /* 0xa4 */ u32 _a4 = 0;
            /* 0xa8 */ u32 _a8 = 0;
            /* 0xac */ u32 _ac = 0;
            /* 0xb0 */ void* _b0 = nullptr;
            /* 0xb8 */ s32 _b8 = 1;
            /* 0xbc */ s32 _bc = -1;
            /* 0xc0 */ phys::RigidBody* _c0 = nullptr;
            /* 0xc8 */ u32 _c8 = 0;
            /* 0xcc */ u32 _cc = 0;
            /* 0xd0 */ u32 _d0 = 53;  // ContactLayer SensorNoHit?
            /* 0xd8 */ BaseProcLink _d8;
            /* 0xe8 */ BaseProcLink _e8;
            /* 0xf8 */ s32 _f8 = -1;
            /* 0xfc */ bool _fc = false;
        };
        KSYS_CHECK_SIZE_NX150(Unk1, 0x100);

        void sub_71007A124C();
        void sub_71007A12CC(sead::Buffer<u8>* buffer, Actor* actor);
        void sub_71007A1C40(sead::Buffer<u8>* buffer, Actor* actor);

        sead::SafeArray<Unk1, 8> mEntries;
        s16 mNum;
        u8 _802;
    };

    static ActorAtk* makeForActor(Actor* actor, sead::Heap* heap);

    explicit ActorAtk(Actor* actor);
    ~ActorAtk() override;

    bool init(sead::Heap* heap) override;
    void m5() override;
    void free() override;
    void m7() override;
    void m8() override;
    void m9() override;
    bool m10() override;
    bool hasAttackInfoMaybe() override;
    bool reset() override;
    void m13() override;

    s32 getNumAttackInfoMaybe() const;
    s32 sub_710079E270() const;
    // 0x710079e288 (CSV name): attack info `idx` of _18, or a static default entry.
    // Non-const result: callers acquire the actor through the entry's link (ChildDeviceReflectArrow::m37).
    Struct7::AttackInfo* getAttackInfo(int idx) const;
    // 0x710079e2c0 (CSV ActorAtk::x): entry `idx` of _48, or a static default entry.
    const Unk_710079e64c::Unk1* sub_710079E2C0(int idx) const;

    /* 0x18 */ Struct7* _18 = nullptr;
    /* 0x20 */ sead::Buffer<u8> _20;
    /* 0x30 */ sead::Buffer<u8> _30;
    /* 0x40 */ AttackSensor* _40 = nullptr;
    /* 0x48 */ Unk_710079e64c* _48 = nullptr;
    /* 0x50 */ sead::Buffer<u8> _50;
    /* 0x60 */ sead::Buffer<u8> _60;
    /* 0x70 */ AttackSensor2* _70 = nullptr;
    /* 0x78 */ u8 _78 = 0;
};
KSYS_CHECK_SIZE_NX150(ActorAtk, 0x80);

}  // namespace ksys::act
