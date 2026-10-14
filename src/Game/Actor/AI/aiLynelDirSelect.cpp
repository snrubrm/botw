#include "Game/Actor/AI/aiLynelDirSelect.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

LynelDirSelect::LynelDirSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelDirSelect::~LynelDirSelect() = default;

bool LynelDirSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelDirSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    switch (sub_7100490308()) {
    case 0:
        changeChild("前", &pack);
        break;
    case 1:
        changeChild("後", &pack);
        break;
    case 2:
        changeChild("左", &pack);
        break;
    case 3:
        changeChild("右", &pack);
        break;
    default:
        break;
    }
}

bool LynelDirSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool LynelDirSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void LynelDirSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelDirSelect::loadParams_() {
    getStaticParam(&mBasePosOffsetFront_s, "BasePosOffsetFront");
    getStaticParam(&mBasePosOffsetBack_s, "BasePosOffsetBack");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getStaticParam(&mIsCheckOnlyXZ_s, "IsCheckOnlyXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LynelDirSelect::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void LynelDirSelect::m34() {}

// NON_MATCHING: the y selects use the inverted csel (wzr first), and the dot products are scheduled differently.
// Returns the side of the actor the target is on: 0 front, 1 back, 2 / 3 the two sides.
s32 LynelDirSelect::sub_7100490308() {
    const sead::Matrix34f& mtx = mActor->getMtx();
    sead::Vector3f front;
    mtx.getBase(front, 2);
    if (*mIsCheckOnlyXZ_s)
        front.y = 0.0f;
    const sead::Vector3f pos = mtx.getTranslation();
    front.normalize();

    sead::Vector3f front_base;
    front_base.setMul(mtx, sead::Vector3f(0.0f, 0.0f, *mBasePosOffsetFront_s));
    sead::Vector3f dir = *mTargetPos_d - front_base;
    if (*mIsCheckOnlyXZ_s)
        dir.y = 0.0f;
    dir.normalize();
    if (front.dot(dir) >= sead::Mathf::cos(*mFrontAngle_s))
        return 0;

    sead::Vector3f back_base;
    back_base.setMul(mtx, sead::Vector3f(0.0f, 0.0f, -*mBasePosOffsetBack_s));
    dir = *mTargetPos_d - back_base;
    if (*mIsCheckOnlyXZ_s)
        dir.y = 0.0f;
    dir.normalize();
    if ((-front).dot(dir) >= sead::Mathf::cos(*mBackAngle_s))
        return 1;

    dir = *mTargetPos_d - pos;
    if (*mIsCheckOnlyXZ_s)
        dir.y = 0.0f;
    dir.normalize();
    if (front.cross(dir).y >= 0.0f)
        return 2;
    return 3;
}

}  // namespace uking::ai
