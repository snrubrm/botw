#include "Game/AI/AI/aiSandwormCircleMoveTarget.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

SandwormCircleMoveTarget::SandwormCircleMoveTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormCircleMoveTarget::~SandwormCircleMoveTarget() = default;

bool SandwormCircleMoveTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormCircleMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _88 = *mRadius_s;
    _8c = _8d = sub_710072E368(mActor);
    _68.mTimer = ksys::Timer(0, 0);
    _84 = 1.0f;

    const sead::Vector2f target(mTargetPos_d->x, mTargetPos_d->z);
    const auto& mtx = mActor->getMtx();
    const sead::Vector2f pos(mtx.m[0][3], mtx.m[2][3]);
    const f32 delta = (pos - target).length() - _88;
    s32 state;
    if (sead::Mathf::abs(delta) > *mRadiusMargin_s)
        state = delta < 0 ? 0 : 2;
    else
        state = 1;

    if (state == 2)
        sub_7100558598();
    else if (state == 0)
        sub_7100558774();
    else
        sub_7100558848();
}

void SandwormCircleMoveTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormCircleMoveTarget::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusMargin_s, "RadiusMargin");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mFrontCheckLength_s, "FrontCheckLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the copy of the target position shares its stack slot with the SafeString
// temporaries in the original (its lifetime ends before the param pack)
void SandwormCircleMoveTarget::sub_7100558598() {
    sead::Vector3f pos;
    const sead::Vector3f target = *mTargetPos_d;
    auto* nav = mActor->m45();
    if (nav && nav->sub_7100F76078(&pos, target, 3.6f).sub_7100F7EB40()) {
        ksys::act::ai::InlineParamPack params;
        params.addVec3(pos, "TargetPos", -1);
        changeChild("近づき", &params);
    } else {
        pos.set(*mTargetPos_d);
        ksys::act::ai::InlineParamPack params;
        params.addVec3(pos, "TargetPos", -1);
        changeChild("近づき", &params);
        setFailed();
    }
}

void SandwormCircleMoveTarget::sub_7100558774() {
    sead::Vector3f pos;
    sub_710055949C(&pos);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("遠ざかり", &params);
}

void SandwormCircleMoveTarget::sub_7100558848() {
    const f32 time = !_8c ? 120.0f : 15.0f;
    _68.mTimer = ksys::Timer(time, time);

    sead::Vector3f dir = mActor->getMtx().getTranslation() - *mTargetPos_d;
    dir.y = 0.0f;
    dir.normalize();
    _80 = std::atan2(dir.x, dir.z);
    sub_7100559954();

    const f32 add = _84 * (*mSpeed_s / _88);
    f32 angle = add * ksys::VFR::instance()->getDeltaFrame() + _80;
    const f32 radius = _88;
    angle -= sead::Mathf::floor(angle * (1.0f / sead::Mathf::pi2())) * sead::Mathf::pi2();
    if (angle >= sead::Mathf::pi2())
        angle = 0.0f;
    _80 = angle;

    sead::Vector3f target = *mTargetPos_d;
    target.x += radius * std::sin(angle);
    target.z += radius * std::cos(angle);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(target, "TargetPos", -1);
    changeChild("移動", &params);
}

}  // namespace uking::ai
