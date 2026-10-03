#include "Game/AI/AI/aiAssassinFieldShooterBattle.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AssassinFieldShooterBattle::AssassinFieldShooterBattle(const InitArg& arg)
    : AssassinFieldShooterBattleBase(arg) {}

AssassinFieldShooterBattle::~AssassinFieldShooterBattle() = default;

bool AssassinFieldShooterBattle::init_(sead::Heap* heap) {
    return AssassinFieldShooterBattleBase::init_(heap);
}

void AssassinFieldShooterBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    AssassinFieldShooterBattleBase::enter_(params);
}

void AssassinFieldShooterBattle::calc_() {
    AssassinFieldShooterBattleBase::calc_();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed() || !child->isChangeable())
        return;
    if (!isCurrentChild("待機") || !sub_710032276C())
        return;

    ksys::act::ai::InlineParamPack params;
    params.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("転移", &params);
}

void AssassinFieldShooterBattle::leave_() {
    AssassinFieldShooterBattleBase::leave_();
}

bool AssassinFieldShooterBattle::m34() {
    return sub_71003228DC() && isCurrentChild("待機");
}

void AssassinFieldShooterBattle::loadParams_() {
    AssassinFieldShooterBattleBase::loadParams_();
}

}  // namespace uking::ai
