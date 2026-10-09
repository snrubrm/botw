#include "Game/Actor/actRope.h"
#include "Game/gameSceneSubsysMisc.h"

namespace uking::act {

void Rope::initMaybe() {
    RopeBase::initMaybe();
}

void Rope::updatePositionMaybe() {
    RopeBase::updatePositionMaybe();
}

ksys::act::Unk_71025ae640* Rope::getAtk() {
    return &_c30;
}

void Rope::m149() {
    if (GameSceneSubsys5::instance() == nullptr)
        return;
    GameSceneSubsys5::instance()->sub_7100905C70();
}

s32* Rope::getLife() {
    return &_cb0;
}

uking::dmg::DamageManagerBase* Rope::getDamageMgr() {
    return &_a00;
}

}  // namespace uking::act
