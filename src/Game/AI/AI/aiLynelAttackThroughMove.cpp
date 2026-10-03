#include "Game/AI/AI/aiLynelAttackThroughMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

namespace uking::ai {

LynelAttackThroughMove::LynelAttackThroughMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelAttackThroughMove::~LynelAttackThroughMove() = default;

bool LynelAttackThroughMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelAttackThroughMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LynelAttackThroughMove::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

void LynelAttackThroughMove::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F7D350();
}

void LynelAttackThroughMove::loadParams_() {
    getStaticParam(&mParams.mSideOffsetDirType_s, "SideOffsetDirType");
    getStaticParam(&mParams.mCliffFailTime_s, "CliffFailTime");
    getStaticParam(&mParams.mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mParams.mSideOffset_s, "SideOffset");
    getStaticParam(&mParams.mThroughDist_s, "ThroughDist");
    getStaticParam(&mParams.mAcceptableRadius_s, "AcceptableRadius");
    getStaticParam(&mParams.mFrontAngle_s, "FrontAngle");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

bool LynelAttackThroughMove::isFinished() const {
    if (ActionBase::isFinished())
        return true;
    if (isCurrentChild("通り過ぎ"))
        return getCurrentChild()->isFinished();
    return false;
}

}  // namespace uking::ai
