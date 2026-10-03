#include "Game/AI/AI/aiViewWaitRiskAvoid.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ViewWaitRiskAvoid::ViewWaitRiskAvoid(const InitArg& arg) : ViewWait(arg) {}

ViewWaitRiskAvoid::~ViewWaitRiskAvoid() = default;

bool ViewWaitRiskAvoid::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void ViewWaitRiskAvoid::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void ViewWaitRiskAvoid::calc_() {
    ViewWait::calc_();
}

void ViewWaitRiskAvoid::leave_() {
    ViewWait::leave_();
}

void ViewWaitRiskAvoid::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mAvoidFrame_s, "AvoidFrame");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mSpaceAngle_s, "SpaceAngle");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
}

void ViewWaitRiskAvoid::m40() {
    _5c = false;
    if (isCurrentChild("後ずさり回避")) {
        getCurrentChild()->setDynamicParam(m34(), "TargetPos");
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(m34(), "TargetPos", -1);
        changeChild("後ずさり回避", &pack);
    }
}

bool ViewWaitRiskAvoid::m35() {
    if (m42()) {
        _80 = ksys::Timer(*mAvoidFrame_s, *mAvoidFrame_s);
        return true;
    }

    if (isCurrentChild("横移動回避") || isCurrentChild("後ずさり回避")) {
        _80.update();
        if (_80.value <= sead::Mathf::epsilon()) {
            m36();
            return true;
        }
    }
    return ViewWait::m35();
}

}  // namespace uking::ai
