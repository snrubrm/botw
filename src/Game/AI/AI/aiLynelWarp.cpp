#include "Game/AI/AI/aiLynelWarp.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LynelWarp::LynelWarp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelWarp::~LynelWarp() = default;

bool LynelWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelWarp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelWarp::loadParams_() {}

bool LynelWarp::isChangeable() const {
    return isCurrentChild("出現") && getCurrentChild()->isChangeable();
}

bool LynelWarp::isFinished() const {
    if (!isCurrentChild("出現"))
        return false;
    auto* child = getCurrentChild();
    return child->isFinished() || child->isFailed();
}

void LynelWarp::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("消失")) {
            ksys::act::disableAttClient(mActor, "JumpRide");
            changeChild("ワープ");
        } else if (isCurrentChild("ワープ")) {
            mActor->get68c() = false;
            ksys::act::enableAttClient(mActor, "JumpRide");
            changeChild("出現");
        }
    } else {
        child->isChangeable();
    }
}

}  // namespace uking::ai
