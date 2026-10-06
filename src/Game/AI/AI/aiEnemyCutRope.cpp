#include "Game/AI/AI/aiEnemyCutRope.h"
#include <cmath>
#include "Game/AI/aiUnk_71007320F0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actRopeBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

// NON_MATCHING: the original loads `mActor` (x0) before `*mCutDist_s` for the weapon distance call
bool EnemyCutRope::sub_7100386374() {
    auto* actor = mActor;
    sead::Vector3f target;
    {
        ksys::act::acc::RopeBase rope;
        ksys::act::acquireActor(mTargetActor_d, &rope);
        target = rope.sub_7100ED8440(!*mCutFlyAttack_s ? 1.0f : 0.7f);
    }
    const sead::Vector3f pos(actor->getMtx().m[0][3], actor->getMtx().m[1][3], actor->getMtx().m[2][3]);
    sead::Vector3f to_target = target - pos;
    const f32 dist = to_target.normalize();
    to_target.y = 0;
    to_target.normalize();
    if (!(dist < *mCutDist_s + sub_71007320F0(mActor, *mWeaponIdx_s)))
        return false;
    sead::Vector3f forward;
    actor->getMtx().getBase(forward, 2);
    return to_target.dot(forward) >= std::cos(*mCutAngle_s);
}

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

// NON_MATCHING: the original loads `mActor` (x0) before `*mCutDist_s` for the weapon distance call (same as sub_7100386374)
void EnemyCutRope::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = 3;
    if (sub_7100386374()) {
        changeToCut();
        return;
    }
    auto* actor = mActor;
    sead::Vector3f target;
    {
        ksys::act::acc::RopeBase rope;
        ksys::act::acquireActor(mTargetActor_d, &rope);
        target = rope.sub_7100ED8440(!*mCutFlyAttack_s ? 1.0f : 0.7f);
    }
    const sead::Vector3f pos(actor->getMtx().m[0][3], actor->getMtx().m[1][3], actor->getMtx().m[2][3]);
    const f32 dist = (pos - target).length();
    if (dist < *mCutDist_s + sub_71007320F0(mActor, *mWeaponIdx_s))
        changeToRotate();
    else
        changeToApproach();
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
