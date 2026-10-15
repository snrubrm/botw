#include "Game/Actor/actRope.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/gameSceneSubsysMisc.h"

// Existing global damage callback cleanup, also called by DynamicActor.
void sub_7100D2D424(uking::act::DamageManagerBase* manager);

namespace uking::act {

Rope::Rope(const CreateArg& arg) : RopeBase(arg), _a00(this), _c30(this), _cc8(this, 0x800002a) {}

void Rope::m63() {
    RopeBase::m63();
    sub_71007394E8(this);
    sub_7100739108(getActorAttackSensor(this));
    sub_7100739168(sub_71007A2844(this));
    _a00.clearCallbacks();
    _cc8._8 = &getMessageTransceiver();
}

ksys::act::BaseProc* Rope::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Rope(arg);
}

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

uking::act::DamageManagerBase* Rope::getDamageMgr() {
    return &_a00;
}

// NON_MATCHING: the original inlines the destructors of RopeBase and ActorAtk; both are out of line here until
// their key functions (RopeBase::initMaybe 0x7100ecf66c, ActorAtk::init 0x710079d7b0) are decompiled.
Rope::~Rope() = default;

}  // namespace uking::act
