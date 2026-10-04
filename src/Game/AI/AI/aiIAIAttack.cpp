#include "Game/AI/AI/aiIAIAttack.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::ai {

IAIAttack::IAIAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IAIAttack::~IAIAttack() = default;

bool IAIAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IAIAttack::sub_71004449A8(sead::Vector3f* pos) {
    auto* actor = mActor;
    sead::Vector3f v = *mParams.mTargetPos_d;
    v -= actor->getMtx().getTranslation();
    v.y = 0;
    v.normalize();
    v.set(-v.z, 0.0f, v.x);
    v *= *mParams.mOffsetLR_s;
    v += *mParams.mTargetPos_d;
    if (sub_710072F788(actor, *mParams.mTargetPos_d, v, pos))
        *pos = v;
}

void IAIAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    sub_71004449A8(&pos);
    if (*mParams.mIsAbleSkipNear_s && m36(pos))
        m35(pos);
    else
        m34(pos);
}

void IAIAttack::calc_() {
    sead::Vector3f pos;
    sub_71004449A8(&pos);
    auto* child = getCurrentChild();
    child->setDynamicParam(pos, "TargetPos");
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild("駆け寄り")) {
            setFinished();
            return;
        }
        if (!m36(pos)) {
            setFailed();
            return;
        }
        m35(pos);
    } else if (child->isChangeable()) {
        if (m36(pos))
            m35(pos);
        else if (m37())
            setFailed();
    }
}

bool IAIAttack::isChangeable() const {
    return false;
}

void IAIAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void IAIAttack::loadParams_() {
    getStaticParam(&mParams.mOffsetLR_s, "OffsetLR");
    getStaticParam(&mParams.mCloseDistLR_s, "CloseDistLR");
    getStaticParam(&mParams.mClsoeDistFB_s, "ClsoeDistFB");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mIsAbleSkipNear_s, "IsAbleSkipNear");
    getStaticParam(&mParams.mTiredAngle_s, "TiredAngle");
}

void IAIAttack::m34(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("駆け寄り", &params);
}

void IAIAttack::m35(const sead::Vector3f& pos) {
    ksys::act::ai::InlineParamPack params;
    params.addVec3(pos, "TargetPos", -1);
    changeChild("斬り付け", &params);
}

bool IAIAttack::m37() {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f dir = -(mtx.getTranslation() - *mParams.mTargetPos_d);
    dir.normalize();
    const sead::Vector3f front = {mtx(0, 2), mtx(1, 2), mtx(2, 2)};
    return !(dir.dot(front) >= sead::Mathf::cos(*mParams.mTiredAngle_s));
}

bool IAIAttack::m36(const sead::Vector3f& pos) {
    auto* actor = mActor;
    sead::Vector3f diff;
    actor->getMtx().getTranslation(diff);
    diff -= *mParams.mTargetPos_d;
    sead::Vector3f front;
    actor->getMtx().getBase(front, 2);

    sead::Vector3f side;
    ksys::util::sub_71011EFA00(&side, diff, front);
    sead::Vector3f forward;
    ksys::util::sub_71011EFA54(&forward, diff, front);

    const f32 range = sub_71007320F0(actor, *mParams.mWeaponIdx_s);
    const f32 dist_lr = range + *mParams.mCloseDistLR_s;
    if (side.x * side.x + side.z * side.z < dist_lr * dist_lr) {
        const f32 dist_fb = range + *mParams.mClsoeDistFB_s;
        return forward.x * forward.x + forward.z * forward.z < dist_fb * dist_fb;
    }
    return false;
}

}  // namespace uking::ai
