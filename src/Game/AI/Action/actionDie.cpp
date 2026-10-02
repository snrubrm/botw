#include "Game/AI/Action/actionDie.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/AI/aiUnk_710072BA90.h"

namespace uking::action {

Die::Die(const InitArg& arg) : BlownOff(arg) {}

Die::~Die() = default;

bool Die::init_(sead::Heap* heap) {
    return BlownOff::init_(heap);
}

void Die::enter_(ksys::act::ai::InlineParamPack* params) {
    BlownOff::enter_(params);
    sub_710072BB28(mActor);
}

void Die::leave_() {
    sub_71007A3800(mActor);
    BlownOff::leave_();
}

void Die::loadParams_() {
    BlownOff::loadParams_();
}

void Die::calc_() {
    BlownOff::calc_();
}

bool Die::isChangeable() const {
    return false;
}

}  // namespace uking::action
