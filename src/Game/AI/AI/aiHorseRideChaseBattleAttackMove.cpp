#include "Game/AI/AI/aiHorseRideChaseBattleAttackMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073D318.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideChaseBattleAttackMove::HorseRideChaseBattleAttackMove(const InitArg& arg)
    : HorseRideChaseBattleMoveBase(arg) {}

HorseRideChaseBattleAttackMove::~HorseRideChaseBattleAttackMove() = default;

bool HorseRideChaseBattleAttackMove::init_(sead::Heap* heap) {
    return HorseRideChaseBattleMoveBase::init_(heap);
}

void HorseRideChaseBattleAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideChaseBattleMoveBase::enter_(params);
}

void HorseRideChaseBattleAttackMove::leave_() {
    HorseRideChaseBattleMoveBase::leave_();
}

void HorseRideChaseBattleAttackMove::loadParams_() {
    HorseRideChaseBattleMoveBase::loadParams_();
}

void HorseRideChaseBattleAttackMove::calc_() {
    HorseRideChaseBattleMoveBase::calc_();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("攻撃")) {
            if (child->isFinished())
                setFinished();
            else
                setFailed();
        } else {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
            changeChild("攻撃", &pack);
        }
    } else {
        child->isChangeable();
    }
}

bool HorseRideChaseBattleAttackMove::m36() {
    return isCurrentChild("攻撃");
}

void HorseRideChaseBattleAttackMove::m35() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
    changeChild("攻撃", &pack);
}

void HorseRideChaseBattleAttackMove::m34(int gear) {
    auto* rider = sub_710073D318(mActor);
    if (!rider)
        return;
    if (gear) {
        _90._18 = gear;
        _90.sub_710070DC38(rider, true);
    } else {
        _b0.sub_710070DC38(rider, true);
    }
}

}  // namespace uking::ai
