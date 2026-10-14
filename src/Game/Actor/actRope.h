#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"

namespace uking::act {

// vtable 0x7102358e30 (Rope::_cc8): sends message 0x800002a without a payload (D0 0x7100025068, m2 0x710002506c).
class Unk_7102358e30 : public Unk_7102357d20 {
public:
    using Unk_7102357d20::Unk_7102357d20;
    void* m2() override { return nullptr; }
};

class Rope : public ksys::act::RopeBase {
    SEAD_RTTI_OVERRIDE(Rope, ksys::act::RopeBase)
public:
    explicit Rope(const CreateArg& arg);
    ~Rope() override;

    // CSV Rope::construct (0x71000241dc): the actor factory function.
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);
    // Primary vtable slot19 at2358950 points to243E0.
    void onPreDeleteStart_(PrepareArg& arg) override;
    void initMaybe() override;
    void updatePositionMaybe() override;
    ksys::act::Unk_71025ae640* getAtk() override;

    // RopeBase slot 149.
    void m149() override;
    s32* getLife() override;
    uking::act::DamageManagerBase* getDamageMgr() override;

    // Constructor241DC constructs DamageManager atA00 and ActorAtk atC30.
    /* 0xa00 */ uking::act::DamageManager _a00;
    /* 0xc30 */ ksys::act::ActorAtk _c30;
    /* 0xcb0 */ s32 _cb0 = 1;
    /* 0xcb8 */ ksys::act::BaseProcLink _cb8;
    /* 0xcc8 */ Unk_7102358e30 _cc8;
};

}  // namespace uking::act
