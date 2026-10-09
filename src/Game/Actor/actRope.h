#pragma once

#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"

namespace uking::act {

class Rope : public ksys::act::RopeBase {
    SEAD_RTTI_OVERRIDE(Rope, ksys::act::RopeBase)
public:
    ~Rope() override;
    void initMaybe() override;
    void updatePositionMaybe() override;
    ksys::act::Unk_71025ae640* getAtk() override;

    // RopeBase slot 149.
    void m149() override;
    s32* getLife() override;
    uking::dmg::DamageManagerBase* getDamageMgr() override;

    // Constructor241DC constructs DamageManager atA00 and ActorAtk atC30.
    /* 0xa00 */ uking::dmg::DamageManager _a00;
    /* 0xc30 */ ksys::act::ActorAtk _c30;
    /* 0xcb0 */ s32 _cb0;
};

}  // namespace uking::act
