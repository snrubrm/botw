#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include "Game/Actor/actRideable.h"

namespace uking::act {

class HorseBase;

// Placeholder (ctor 0x7100e7941c, dtor 0x7100e79450; emitted in the RideableBase::S1 TU): one of the two
// capsule bodies RideableHorse::m4 creates through 0x7100e794a8 (rigid bodies _0 / _8, contact info _10).
struct Unk_7100e7941c {
    Unk_7100e7941c();
    ~Unk_7100e7941c();
    // 0x7100e794a8 (placeholder name; declaration only, 1180 B): creates the capsule bodies and the contact
    // info for `controller` (`names`: the Jump_Gear* name table); 13 shape / layer values.
    void sub_7100E794A8(ksys::phys::CharacterController* controller,
                        const sead::SafeArray<sead::SafeString, 5>& names, sead::Heap* heap, f32 a0,
                        f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6, f32 a7, f32 a8, f32 a9, f32 a10,
                        f32 a11, f32 a12);

    ksys::phys::RigidBody* _0 = nullptr;
    ksys::phys::RigidBody* _8 = nullptr;
    ksys::phys::QueryContactPointInfo* _10 = nullptr;
    u64 _18 = 0;
    f32 _20 = 1.0f;
    f32 _24 = 0;
    f32 _28 = 0;
    f32 _2c = 0;
    f32 _30 = 0;
    f32 _34 = 1.0f;
    f32 _38[8]{};
    u64 _58 = 0;
    f32 _60 = 0.5f;
    s32 _64 = 2;
};
KSYS_CHECK_SIZE_NX150(Unk_7100e7941c, 0x68);

// Name from the CSV (RideableHorse::*). vtable 0x71024ec0c8 (47 slots: Rideable's 45 + m45 / m46), RTTI
// statics 0x7102603c78 / 0x7102603c80, size 0x2a8; created by 0x7100e7c688 (CSV RideableHorse::ctor, the
// factory) as HorseBase::_b10. `mActor` is the HorseBase. Only the simple virtuals are written so far
// (the array at +0x280 of 0x68-byte elements, constructed by m4 / destroyed by m2 / m3, is not modelled).
// TODO: incomplete.
class RideableHorse : public Rideable {
    SEAD_RTTI_OVERRIDE(RideableHorse, Rideable)
public:
    RideableHorse();
    ~RideableHorse() override;

    // 0x7100e7c688
    static RideableBase* make(sead::Heap* heap);

    // Overrides of Unk_7100e8b2b8::procLink8 / procLink13 (the primary slots 45 / 46 are their entries).
    void procLink8() override;
    f32 procLink13() override;
    void m42(s32 a) override;
    void m43() override;

    bool m4(ksys::act::Actor* actor, sead::Heap* heap) override;
    void m6() override;
    void m7() override;
    void m8() override;
    Gear m23() override;

    bool m10(const ksys::Message& message) override;
    f32 m12() override;
    void* m13() override;
    f32 m14() override;
    void m15(f32 a, f32 b) override;
    f32 m18() override;
    s32 m19() override;
    void m20(s32 a) override;
    s32 m21() override;
    f32 m26() override;
    f32 m27() override;
    f32 m28() override;
    void m29(f32 a) override;
    f32 m30(f32 delta) override;
    f32 m31() override;
    f32 m32() override;
    f32 m33() override;
    f32 m34() override;
    f32 m35() override;
    f32 m36() override;
    f32 m37() override;
    f32 m38() override;
    HorseReins* m39() override;
    HorseReins* m40() override;
    HorseReins* m41() override;

    // A sead::Buffer of the 0x68-byte elements (m13 returns its address).
    using Unk280 = sead::Buffer<Unk_7100e7941c>;
    /* 0x280 */ Unk280 _280;
    /* 0x290 */ s32 _290 = 0;
    /* 0x294 */ f32 _294 = 0;
    /* 0x298 */ f32 _298 = 0;
    /* 0x29c */ f32 _29c = 0;
    /* 0x2a0 */ f32 _2a0 = 0;
};
KSYS_CHECK_SIZE_NX150(RideableHorse, 0x2a8);

}  // namespace uking::act
