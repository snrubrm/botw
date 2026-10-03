#include "Game/AI/Action/actionStick.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Stick::Stick(const InitArg& arg) : ActionEx(arg) {}

Stick::~Stick() = default;

void Stick::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Stick::leave_() {
    ActionEx::leave_();
}

void Stick::loadParams_() {
    if (!mActor->getParam())
        return;
    getDynamicParam(&mStickPos_d, "StickPos");
    getDynamicParam(&mStickPosDiv_d, "StickPosDiv");
    getDynamicParam(&mStickActor_d, "StickActor");
    getDynamicParam(&mStickBodyName_d, "StickBodyName");
}

void Stick::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
