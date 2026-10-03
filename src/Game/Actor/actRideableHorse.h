#pragma once

#include "Game/Actor/actRideable.h"

namespace uking::act {

class HorseBase;

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

    // A sead::Buffer of the 0x68-byte elements (m13 returns its address).
    struct Unk280 {
        u32 mSize = 0;
        void* mBuffer = nullptr;
    };
    /* 0x280 */ Unk280 _280;
    /* 0x290 */ s32 _290 = 0;
    /* 0x294 */ s32 _294 = 0;
    /* 0x298 */ f32 _298 = 0;
    /* 0x29c */ f32 _29c = 0;
    /* 0x2a0 */ f32 _2a0 = 0;
};
KSYS_CHECK_SIZE_NX150(RideableHorse, 0x2a8);

}  // namespace uking::act
