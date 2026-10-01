#include "Game/AI/AI/aiIAIAttack.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

IAIAttack::IAIAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

IAIAttack::~IAIAttack() = default;

bool IAIAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void IAIAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    sub_71004449A8(&pos);
    if (*mIsAbleSkipNear_s && m36(pos))
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
    getStaticParam(&mOffsetLR_s, "OffsetLR");
    getStaticParam(&mCloseDistLR_s, "CloseDistLR");
    getStaticParam(&mClsoeDistFB_s, "ClsoeDistFB");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsAbleSkipNear_s, "IsAbleSkipNear");
    getStaticParam(&mTiredAngle_s, "TiredAngle");
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
    sead::Vector3f dir = -(mtx.getTranslation() - *mTargetPos_d);
    dir.normalize();
    const sead::Vector3f front = {mtx(0, 2), mtx(1, 2), mtx(2, 2)};
    return !(dir.dot(front) >= sead::Mathf::cos(*mTiredAngle_s));
}

}  // namespace uking::ai
