#include "Game/AI/Action/actionBindAction.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BindAction::BindAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void BindAction::loadParams_() {
    if (!mActor->getParam())
        return;
    getDynamicParam(&mNodeName_d, "NodeName");
    getDynamicParam(&mRotOffset_d, "RotOffset");
    getDynamicParam(&mTransOffset_d, "TransOffset");
}

void BindAction::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    m32();
    m34();
}

void BindAction::calc_() {
    _38._68.makeRT(*mRotOffset_d * sead::Mathf::deg2rad(1), *mTransOffset_d);
}

void BindAction::leave_() {
    m35();
}

void BindAction::m34() {
    _38.x(m33());
    _38._28 = mNodeName_d->cstr();
    _38._30.getKey().reset();
    _38._68.makeRT(*mRotOffset_d * sead::Mathf::deg2rad(1), *mTransOffset_d);
    mActor->sub_71011DA824(&_38);
}

void BindAction::m35() {
    mActor->sub_71011DA834(&_38);
}

}  // namespace uking::action
