#include "Game/AI/Action/actionEat.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Eat::Eat(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Eat::~Eat() = default;

void Eat::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    m32();
}

void Eat::leave_() {
    if (auto* child = sead::DynamicCast<ksys::act::Actor>(mActor->getConnectedCalcChild()))
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    ActionWithPosAngReduce::leave_();
}

void Eat::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsHeal_s, "IsHeal");
}

void Eat::calc_() {
    ActionWithPosAngReduce::calc_();
}

void Eat::m32() {
    playAS("Eat", false, 0, 0, -1.0f);
}

}  // namespace uking::action
