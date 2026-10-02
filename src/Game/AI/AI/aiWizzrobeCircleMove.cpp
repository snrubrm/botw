#include "Game/AI/AI/aiWizzrobeCircleMove.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

WizzrobeCircleMove::WizzrobeCircleMove(const InitArg& arg) : CircleMoveTarget(arg) {}

WizzrobeCircleMove::~WizzrobeCircleMove() = default;

bool WizzrobeCircleMove::init_(sead::Heap* heap) {
    return CircleMoveTarget::init_(heap);
}

void WizzrobeCircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mRadiusTimer_s > 0.0f) {
        _8c = ksys::Timer(*mRadiusTimer_s, *mRadiusTimer_s);
        _88 = false;
    } else {
        _88 = true;
        if (*mEndTimer_s > 0.0f) {
            _8c = ksys::Timer(*mEndTimer_s, *mEndTimer_s);
        } else {
            _8c = ksys::Timer();
            setFinished();
        }
    }
    CircleMoveTarget::enter_(params);
}

void WizzrobeCircleMove::calc_() {
    CircleMoveTarget::calc_();
    if (_88) {
        if (!(_8c.value <= sead::Mathf::epsilon()))
            _8c.update();
        if (!(_8c.value <= sead::Mathf::epsilon()))
            return;
    } else {
        _8c.update();
        if (!(_8c.value <= sead::Mathf::epsilon()))
            return;
        _88 = true;
        if (*mEndTimer_s > 0.0f) {
            _8c = ksys::Timer(*mEndTimer_s, *mEndTimer_s);
            return;
        }
        _8c = ksys::Timer();
    }
    if (getCurrentChild()->isChangeable())
        setFinished();
}

void WizzrobeCircleMove::leave_() {
    CircleMoveTarget::leave_();
}

void WizzrobeCircleMove::loadParams_() {
    CircleMoveTarget::loadParams_();
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mRadiusTimer_s, "RadiusTimer");
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mIsAttCentral_s, "IsAttCentral");
}

void WizzrobeCircleMove::m35(const sead::Vector3f& target_pos) {
    ksys::act::ai::InlineParamPack params;
    sead::Vector3f att_pos;
    m34(&att_pos);
    if (!*mIsAttCentral_s)
        att_pos = target_pos + (target_pos - att_pos);
    params.addVec3(att_pos, "AttPos", -1);
    params.addVec3(target_pos, "TargetPos", -1);
    changeChild("移動", &params);
}

void WizzrobeCircleMove::m36(const sead::Vector3f& target_pos) {
    auto* child = getCurrentChild();
    sead::Vector3f att_pos;
    m34(&att_pos);
    if (!*mIsAttCentral_s)
        att_pos = target_pos + (target_pos - att_pos);
    child->setDynamicParam(att_pos, "AttPos");
    child->setDynamicParam(target_pos, "TargetPos");
}

f32 WizzrobeCircleMove::m37() {
    f32 radius = *mFinRadius_s;
    if (!_88)
        radius += (*mRadius_s - radius) * (_8c.value / *mRadiusTimer_s);
    return radius;
}

}  // namespace uking::ai
