#include "Game/AI/AI/aiEnemyCutRope.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: the original selects the 0.7 / 1.0 ratio with a branch (the constant load is not speculated), ours
// with fcsel
void EnemyCutRope::changeToCut() {
    ksys::act::acc::RopeBase rope;
    ksys::act::acquireActor(mTargetActor_d, &rope);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(rope.sub_7100ED8440(*mCutFlyAttack_s ? 0.7f : 1.0f), "TargetPos", -1);
    changeChild("カット", &pack);
}

// NON_MATCHING: same as changeToCut
void EnemyCutRope::changeToRotate() {
    ksys::act::acc::RopeBase rope;
    ksys::act::acquireActor(mTargetActor_d, &rope);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(rope.sub_7100ED8440(*mCutFlyAttack_s ? 0.7f : 1.0f), "TargetPos", -1);
    changeChild("回転", &pack);
}

void EnemyCutRope::changeToApproach() {
    ksys::act::acc::RopeBase rope;
    ksys::act::acquireActor(mTargetActor_d, &rope);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(rope.sub_7100ED8440(1.0f), "TargetPos", -1);
    changeChild("接近", &pack);
}

EnemyCutRope::EnemyCutRope(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyCutRope::~EnemyCutRope() = default;

bool EnemyCutRope::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyCutRope::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyCutRope::leave_() {
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
}

void EnemyCutRope::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mCutDist_s, "CutDist");
    getStaticParam(&mCutAngle_s, "CutAngle");
    getStaticParam(&mCutFlyAttack_s, "CutFlyAttack");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mCommanderID_d, "CommanderID");
}

}  // namespace uking::ai
