#pragma once

#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"

namespace uking::act {

// Only the nominal type is recovered; owned members and construction remain undeclared.
class Rope : public ksys::act::RopeBase {
    SEAD_RTTI_OVERRIDE(Rope, ksys::act::RopeBase)
public:
    ~Rope() override;

    // RopeBase slot 149.
    void m149() override;
    // Actor slot 87 (getLife): life counter at +0xcb0. The pad covers +0xa00
    // (DamageManagerBase for getDamageMgr) and +0xc30 (Unk_71025ae640 for getAtk).
    s32* getLife() override;

    /* 0xa00 */ u8 _a00[0xcb0 - 0xa00];
    /* 0xcb0 */ s32 _cb0;
};

}  // namespace uking::act
