#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}  // namespace sead

namespace ksys::act {

class Actor;
class AttackSensor;
class AttackSensor2;

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
        struct AttackInfo {
            u8 _0[0x78];
        };

        void reset();
        void sub_710079E958(sead::Buffer<u8>* buffer, Actor* actor);
        void sub_710079EFBC(sead::Buffer<u8>* buffer, Actor* actor);

        u8 _0[0x3c0];
        s16 mNumAttackInfo;
    };
    // dtor 0x710079e64c: 8 entries of 0x100 bytes and their count.
    struct Unk_710079e64c {
        struct Unk1 {
            u8 _0[0x100];
        };

        void sub_71007A124C();
        void sub_71007A12CC(sead::Buffer<u8>* buffer, Actor* actor);
        void sub_71007A1C40(sead::Buffer<u8>* buffer, Actor* actor);

        u8 _0[0x800];
        s16 mNum;
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
    const Struct7::AttackInfo* getAttackInfo(int idx) const;
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
