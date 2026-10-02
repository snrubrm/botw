#include "Game/AI/Action/actionForkBattleNodeForAttackGround.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkBattleNodeForAttackGround::ForkBattleNodeForAttackGround(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkBattleNodeForAttackGround::~ForkBattleNodeForAttackGround() = default;

bool ForkBattleNodeForAttackGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkBattleNodeForAttackGround::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkBattleNodeForAttackGround::leave_() {
    if (auto* spine = mActor->sub_71011D8A10())
        spine->_d4 &= ~0x40;
}

void ForkBattleNodeForAttackGround::loadParams_() {
    getStaticParam(&mIsOffsetFromBaseBone_s, "IsOffsetFromBaseBone");
    getStaticParam(&mAttackPosOffset_s, "AttackPosOffset");
}

void ForkBattleNodeForAttackGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
