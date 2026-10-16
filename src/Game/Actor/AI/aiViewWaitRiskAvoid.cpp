#include "Game/Actor/AI/aiViewWaitRiskAvoid.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include <cmath>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

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

// NON_MATCHING: float register allocation (the original keeps the constant 0 and the front vector in fewer
// registers: one saved d register less)
// 0x71005e6b84
bool ViewWaitRiskAvoid::sub_71005E6B84(const sead::Vector3f& target) {
    const sead::Matrix34f& mtx = mActor->getMtx();
    sead::Vector3f dir = target - mtx.getTranslation();
    dir.y = 0;
    dir.normalize();
    sead::Vector3f front;
    mtx.getBase(front, 2);
    front.y = 0;
    front.normalize();
    sead::Vector3f cross;
    cross.setCross(front, dir);
    return std::atan2(cross.length(), dir.dot(front)) < *mFrontAngle_s;
}

// NON_MATCHING: scheduling / registers, and the original tests `force` with eor + tbnz
void ViewWaitRiskAvoid::sub_71005E6D10(f32* side, const sead::Vector3f& dir, const sead::Matrix34f& mtx, bool force,
                                       f32 amount, f32 dist) {
    const sead::Vector3f trans = mtx.getTranslation();
    const sead::Vector3f& pos = sub_71005D9330(mActor);
    sead::Vector3f to{pos.x - trans.x, 0.0f, pos.z - trans.z};
    const f32 len = to.normalize();
    if (len > dist + 1.0f && !force)
        return;

    const f32 angle = std::acos(sead::Mathf::clamp(to.dot(dir), -0.999f, 0.999f));
    const f32 space = *mSpaceAngle_s;
    if (to.cross(dir).y < 0.0f) {
        if (angle > space)
            amount *= sead::Mathf::clamp((angle - space) * -3.0f / space + 1.0f, 0.0f, 1.0f);
        *side += amount;
    } else {
        if (angle > space)
            amount *= sead::Mathf::clamp((angle - space) * -3.0f / space + 1.0f, 0.0f, 1.0f);
        *side -= amount;
    }
}

bool ViewWaitRiskAvoid::m43(sead::Vector3f* out) {
    auto* actor = mActor;
    auto* chemical = actor->getChemicalStuff();
    if (!chemical)
        return false;
    const auto* damage_param = actor->getParam()->getRes().mDamageParam;
    if (!damage_param || !damage_param->mBurnable.ref())
        return false;
    auto* holder = chemical->_90->_0;
    if (!holder)
        return false;
    *out = holder->sub_7100D8D1E0();
    return true;
}

void ViewWaitRiskAvoid::m41(s8 dir) {
    _5c = false;
    if (isCurrentChild("横移動回避")) {
        getCurrentChild()->setDynamicParam(m34(), "TargetPos");
        getCurrentChild()->setDynamicParam(s32(dir), "RotDir");
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(m34(), "TargetPos", -1);
        pack.addInt(dir, "RotDir", -1);
        changeChild("横移動回避", &pack);
    }
}

}  // namespace uking::ai
