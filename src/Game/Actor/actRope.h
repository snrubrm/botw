#pragma once

#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"

namespace uking::act {

class Rope : public ksys::act::RopeBase {
    SEAD_RTTI_OVERRIDE(Rope, ksys::act::RopeBase)
public:
    ~Rope() override;

    // RopeBase slot 149.
    void m149() override;
    // Actor slot 87 (getLife): life counter at +0xcb0. The pad covers +0xa00
    // (DamageManagerBase for getDamageMgr) and +0xc30 (Unk_71025ae640 for getAtk).
    s32* getLife() override;
    // Actor slot 127 (getDamageMgr).
    uking::dmg::DamageManagerBase* getDamageMgr() override;

    // Embedded damage manager (returned by getDamageMgr). NOTE: the static type
    // is a guess from the slot signature (could be a derived DamageManager);
    // the Rope ctor (not decompiled) must construct it.
    /* 0xa00 */ uking::dmg::DamageManagerBase _a00;
    /* 0xa68 */ u8 _a68[0xcb0 - 0xa68];  // +0xc30: Unk_71025ae640 (getAtk)
    /* 0xcb0 */ s32 _cb0;
};

}  // namespace uking::act
