#include "Game/AI/Action/actionDragonItemShootUp.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

DragonItemShootUp::DragonItemShootUp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonItemShootUp::~DragonItemShootUp() = default;

bool DragonItemShootUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DragonItemShootUp::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _50 = 0;
    _40 = pos;
    _4c = 0;
    _54.set(0.0f, 0.0f, 0.0f);
}

void DragonItemShootUp::leave_() {
    ksys::act::ai::Action::leave_();
}

void DragonItemShootUp::loadParams_() {
    getStaticParam(&mFlyAwaySpeed_s, "FlyAwaySpeed");
    getStaticParam(&mContactSpeedDownXZ_s, "ContactSpeedDownXZ");
    getStaticParam(&mContactSpeedDownY_s, "ContactSpeedDownY");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DragonItemShootUp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
