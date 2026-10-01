#include "Game/AI/AI/aiHorseRideChaseBattleMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideChaseBattleMove::HorseRideChaseBattleMove(const InitArg& arg)
    : HorseRideChaseBattleMoveBase(arg) {}

HorseRideChaseBattleMove::~HorseRideChaseBattleMove() = default;

bool HorseRideChaseBattleMove::init_(sead::Heap* heap) {
    return HorseRideChaseBattleMoveBase::init_(heap);
}

void HorseRideChaseBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideChaseBattleMoveBase::enter_(params);
}

void HorseRideChaseBattleMove::leave_() {
    HorseRideChaseBattleMoveBase::leave_();
}

void HorseRideChaseBattleMove::loadParams_() {
    HorseRideChaseBattleMoveBase::loadParams_();
}

void HorseRideChaseBattleMove::calc_() {
    HorseRideChaseBattleMoveBase::calc_();
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
        changeChild("待機", &pack);
    } else {
        child->isChangeable();
    }
}

void HorseRideChaseBattleMove::sub_7100440144(int gear) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
    pack.addInt(gear, "Gear", -1);
    changeChild("ギア指令", &pack);
}

bool HorseRideChaseBattleMove::m36() {
    return isCurrentChild("待機");
}

void HorseRideChaseBattleMove::m34(int gear) {
    sub_7100440144(gear);
}

void HorseRideChaseBattleMove::m35() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D93CC(mActor), "TargetPos", -1);
    changeChild("待機", &pack);
}

}  // namespace uking::ai
