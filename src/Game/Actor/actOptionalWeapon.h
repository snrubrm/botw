#pragma once

#include <gfx/seadColor.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act {

// Name from the CSV (OptionalWeapon::m2 / m3 = its RTTI virtuals at 0x7100ef2420 / 0x7100ef2538, between
// the WeaponBase functions; the namespace is a guess). RTTI static 0x71025b1968: a direct child of Actor
// (the static is initialised with the Derive<Actor> vtable), used by EquipedOptionalWeaponAction /
// OptionalWeaponAI. WeaponBase::m162 / m163 return the OptionalWeapon linked at WeaponBase +0x958.
// Factory 0x7100ef07f0: new(0x998) + the out-of-line ctor 0x7100ef0834.
// Layout from the ctor. TODO: incomplete (m22 .. m139 and the other overrides are not written).
class OptionalWeapon : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(OptionalWeapon, ksys::act::Actor)
public:
    // A critical section with two links and a byte (the dtor keeps &_898 and &_898._40 in registers).
    struct Unk898 {
        /* 0x00 */ sead::CriticalSection _0;
        /* 0x40 */ ksys::act::BaseProcLink _40[2];
        /* 0x60 */ u8 _60 = 0xff;
    };

    explicit OptionalWeapon(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    // 0x7100ef1adc (CSV OptionalWeaponMaybe::x; called when a WeaponBase drops its optional weapon).
    void sub_7100EF1ADC();

    Actor* m31() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;

    void sub_7100EF0A44();

protected:
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    IsSpecialJobTypeResult isSpecialJobType_(ksys::act::JobType type) override;

public:
    /* 0x83c */ u8 _83c = 0;
    /* 0x83d */ u8 _83d = 0;
    /* 0x83e */ u8 _83e = 0;
    /* 0x840 */ ksys::act::BaseProcLink _840;
    /* 0x850 */ ksys::act::BaseProcLink _850;
    /* 0x860 */ sead::FixedSafeString<32> _860;
    /* 0x898 */ Unk898 _898;
    /* 0x900 */ sead::FixedSafeString<32> _900;
    /* 0x938 */ u64 _938 = 0;
    /* 0x940 */ u32 _940 = 0;
    /* 0x944 */ f32 _944 = sead::Color4f::cElementMax;
    /* 0x948 */ u32 _948 = 0;
    /* 0x94c */ u8 _94c = 0;
    /* 0x950 */ sead::CriticalSection _950;
    /* 0x990 */ u32 _990 = 0;
    /* 0x994 */ u16 _994 = 0;
};
KSYS_CHECK_SIZE_NX150(OptionalWeapon, 0x998);

}  // namespace uking::act
