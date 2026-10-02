#include "Game/AI/AI/aiSandwormAttackMove.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SandwormAttackMove::SandwormAttackMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormAttackMove::~SandwormAttackMove() = default;

bool SandwormAttackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: scheduling of the two address computations for search()
void SandwormAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    _70._30.search(_70._28, mDamageBaseNode_s);
    _70._68 = *mDamageAngle_s;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    changeChild("攻撃移動", &pack);
}

void SandwormAttackMove::leave_() {
    sub_71005DA114(mActor, &_70);
}

void SandwormAttackMove::loadParams_() {
    getStaticParam(&mSecessionDist_s, "SecessionDist");
    getStaticParam(&mAttackAngle_s, "AttackAngle");
    getStaticParam(&mDamageAngle_s, "DamageAngle");
    getStaticParam(&mLostDist_s, "LostDist");
    getStaticParam(&mDamageBaseNode_s, "DamageBaseNode");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
