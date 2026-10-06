#pragma once

#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::act {

// Name from the CSV (GiantArmor::*, from the vtable analysis; the namespace is a guess). Direct child of
// DynamicActor: the RTTI static 0x71025af0f0 is initialised with the Derive<DynamicActor> vtable. The
// armor pieces of the Hinox / Talus (GiantEnemy::init_ creates four of them; GiantArmorRoot,
// GiantArmorAsWeakPoint, GiantArmorEquip cast the actor to this class). Factory 0x7100029274 (CSV
// GiantArmor::construct, which inlines the ctor): new(0xc20), vtable GOT 0x25794b8.
// Layout from the factory; the virtual functions are not decompiled yet. Members are public.
class GiantArmor : public ksys::act::DynamicActor {
    SEAD_RTTI_OVERRIDE(GiantArmor, DynamicActor)
public:
    explicit GiantArmor(const CreateArg& arg);

    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    bool shouldUnload(s32* a1) override { return false; }
    void initMaybe() override;
    Actor* m31() override;
    // 0x7100029b54 (unnamed in the CSV, placeholder name): the GiantArmor param's DamageScale.
    f32 sub_7100029B54() const;

protected:
    bool canWakeUp_() override;

public:
    // A critical section followed by a link (the dtor keeps &_b90 in a register across the link's reset).
    struct Unk_b90 {
        /* 0x00 */ sead::CriticalSection _0;
        /* 0x40 */ ksys::act::BaseProcLink _40;
    };
    /* 0xb90 */ Unk_b90 _b90;
    /* 0xbe0 */ s32 _be0 = -1;
    /* 0xbe8 */ ksys::act::BaseProcLink _be8;
    /* 0xbf8 */ s32 _bf8 = -1;
    /* 0xc00 */ GiantArmor* _c00 = this;
    /* 0xc08 */ u16 _c08 = 0;
    // GiantArmorAsWeakPoint::enter_ stores a pointer to its member at +0x38 here (a two-level vtable
    // object), leave_ clears it.
    /* 0xc10 */ void* _c10 = nullptr;
    /* 0xc18 */ u8 _c18 = 0;
};
KSYS_CHECK_SIZE_NX150(GiantArmor, 0xc20);

}  // namespace uking::act
