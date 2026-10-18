#pragma once

#include <thread/seadCriticalSection.h>
#include "Game/Actor/AI/aiGiantArmorAsWeakPoint.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

struct Unk_7100739634Result;

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
    void m73() override;
    void calcMaybe() override;
    void m76(ksys::VFR::ScopedDeltaSetter* setter) override;
    void updatePositionMaybe() override;
    Actor* m31() override;
    // 0x7100029b54 (unnamed in the CSV, placeholder name): the GiantArmor param's DamageScale.
    f32 sub_7100029B54() const;
    // GiantEnemy::init_ passes its Actor owner and the armor index; stores the link under _b90.
    bool sub_7100029E7C(Actor* owner, s32 index);
    void sub_7100029AF8(f32* out_scale, s32* out_level,
                        const ai::Unk_71023f36d8::Info* info);
    // 0x7100029aa8 (declared only): when `actor` is one of the two linked armors, forwards it to
    // sub_7100029308 and sets _c18. Called by GiantEnemy::Unk1::sub_710002A94C.
    void sub_7100029AA8(Actor* actor);

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
    // The object at 0xc00: a self pointer, a u16 and the weak point object. Its method takes &_c00 as
    // `this`, so it is an embedded object rather than a bare self pointer.
    struct Unk_c00 {
        explicit Unk_c00(GiantArmor* owner) : mOwner(owner) {}
        // 0x7100029308: refreshes the two weak-point state bits from the actor's attacks.
        void sub_7100029308(Actor* actor);
        // 0x71000294f0: classifies the matching attack of the actor linked at _be8.
        bool sub_71000294F0(Unk_7100739634Result* out, Actor* actor);

        /* 0x00 */ GiantArmor* mOwner;
        /* 0x08 */ u16 _8 = 0;
        // GiantArmorAsWeakPoint::enter_ stores a pointer to its member at +0x38 here (a two-level
        // vtable object), leave_ clears it.
        /* 0x10 */ ai::Unk_71023f36d8* _10 = nullptr;  // non-owning; enter_/leave_ bind and clear it
    };
    KSYS_CHECK_SIZE_NX150(Unk_c00, 0x18);
    /* 0xc00 */ Unk_c00 _c00{this};
    /* 0xc18 */ u8 _c18 = 0;
};
KSYS_CHECK_SIZE_NX150(GiantArmor, 0xc20);

}  // namespace uking::act
