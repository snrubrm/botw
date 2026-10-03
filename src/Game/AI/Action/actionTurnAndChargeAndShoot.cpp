#include "Game/AI/Action/actionTurnAndChargeAndShoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_710073fa90.h"

namespace uking::action {

TurnAndChargeAndShoot::TurnAndChargeAndShoot(const InitArg& arg) : ChargeAndShoot(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
TurnAndChargeAndShoot::~TurnAndChargeAndShoot() {
    ;
}

bool TurnAndChargeAndShoot::init_(sead::Heap* heap) {
    return ChargeAndShoot::init_(heap);
}

void TurnAndChargeAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ChargeAndShoot::enter_(params);
    _e8 = 0;
    sub_710073FA90(&_b8, mActor);
    const f32 speed = mActor->getAngVelocity().length();
    _dc.value = speed;
    _dc.prev_value = speed;
}

void TurnAndChargeAndShoot::leave_() {
    ChargeAndShoot::leave_();
}

void TurnAndChargeAndShoot::loadParams_() {
    ChargeAndShoot::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
}

void TurnAndChargeAndShoot::calc_() {
    ChargeAndShoot::calc_();
}

}  // namespace uking::action
