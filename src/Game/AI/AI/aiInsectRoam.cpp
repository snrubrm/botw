#include "Game/AI/AI/aiInsectRoam.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

InsectRoam::InsectRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InsectRoam::~InsectRoam() = default;

bool InsectRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InsectRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    _64 = *mTerritoryRadius_s + *mTerritoryRadiusRnd_s * sead::GlobalRandom::instance()->getF32();
    _60 = false;
    mActor->getMtx().getBase(_68, 2);
    _68.normalize();
    mActor->getMtx().getTranslation(_74);
    _80 = mActor->getMtx().getBase(2);
    _8c = _74;
    _98 = ksys::Timer(0, 0, 1);
    _a4 = ksys::Timer(0, 0);
    changeChild("徘徊待機");
}

void InsectRoam::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("徘徊歩行")) {
            _60 = child->isFailed();
            changeChild("徘徊待機");
        } else {
            isCurrentChild("徘徊待機");
            changeToRoamWalk();
        }
    }
    if (isCurrentChild("徘徊歩行") && *mMoveSpeed_s > 0) {
        _a4.update();
        if (_a4.value <= sead::Mathf::epsilon() && child->isChangeable()) {
            _98 = ksys::Timer(0, 0);
            _60 = true;
            changeChild("徘徊待機");
        }
    }
}

void InsectRoam::changeToRoamWalk() {
    sub_710044ACE4(&_74, &_68);
    if (*mMoveSpeed_s > 0) {
        const f32 time = *mMoveDist_s / *mMoveSpeed_s + 30.0f;
        _a4 = ksys::Timer(time, time);
    }
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_74, "TargetPos", -1);
    changeChild("徘徊歩行", &params);
}

void InsectRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InsectRoam::loadParams_() {
    getStaticParam(&mTerritoryRadius_s, "TerritoryRadius");
    getStaticParam(&mTerritoryRadiusRnd_s, "TerritoryRadiusRnd");
    getStaticParam(&mMoveDist_s, "MoveDist");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
