#include "Game/Actor/actRope.h"
#include "Game/gameSceneSubsysMisc.h"

// Existing global damage callback cleanup, also called by DynamicActor.
void sub_7100D2D424(uking::dmg::DamageManagerBase* manager);

namespace uking::act {

void Rope::onPreDeleteStart_(PrepareArg& arg) {
    sub_7100D2D424(&_a00);
    // called through a pointer in the original (not devirtualised)
    (&_a00)->preDelete1();
    // called through a pointer in the original (not devirtualised)
    (&_a00)->preDelete2();
    _c30.free();
}

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
