#include "Game/AI/AI/aiGoronCannon.h"

namespace uking::ai {

GoronCannon::GoronCannon(const InitArg& arg) : GoronCannonBase(arg) {}

GoronCannon::~GoronCannon() = default;

bool GoronCannon::init_(sead::Heap* heap) {
    return GoronCannonBase::init_(heap);
}

void GoronCannon::enter_(ksys::act::ai::InlineParamPack* params) {
    GoronCannonBase::enter_(params);
    changeChild("発射前待機");
}

void GoronCannon::calc_() {
    GoronCannonBase::calc_();

    if (isCurrentChild("発射前待機") && _108 && _109) {
        sub_710032D5FC();
        _108 = false;
        _109 = false;
        changeChild("発射");
        return;
    }

    auto* child = getCurrentChild();
    if (isCurrentChild("発射後待機") && child->isFinished()) {
        changeChild("冷却中");
        return;
    }

    child = getCurrentChild();
    if (isCurrentChild("冷却中") && child->isFinished()) {
        changeChild("発射前待機");
        return;
    }

    child = getCurrentChild();
    if (isCurrentChild("発射") && child->isFinished())
        changeChild("発射後待機");
}

void GoronCannon::leave_() {
    GoronCannonBase::leave_();
}

void GoronCannon::loadParams_() {
    GoronCannonBase::loadParams_();
}

}  // namespace uking::ai
