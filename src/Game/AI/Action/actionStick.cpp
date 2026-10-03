#include "Game/AI/Action/actionStick.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

Stick::Stick(const InitArg& arg) : ActionEx(arg) {}

Stick::~Stick() = default;

void Stick::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Stick::leave_() {
    auto* actor = mActor;
    if (_160 == 3)
        actor->sub_71011DA834(&_c0);
    else
        actor->sub_71011DA834(&_48);
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
