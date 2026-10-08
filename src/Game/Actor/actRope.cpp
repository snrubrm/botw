#include "Game/Actor/actRope.h"
#include "Game/gameSceneSubsysMisc.h"

namespace uking::act {

void Rope::m149() {
    if (GameSceneSubsys5::sInstance == nullptr)
        return;
    GameSceneSubsys5::sInstance->sub_7100905C70();
}

s32* Rope::getLife() {
    return &_cb0;
}

uking::dmg::DamageManagerBase* Rope::getDamageMgr() {
    return &_a00;
}

}  // namespace uking::act
