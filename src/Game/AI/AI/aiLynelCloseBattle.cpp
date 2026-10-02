#include "Game/AI/AI/aiLynelCloseBattle.h"

namespace uking::ai {

LynelCloseBattle::LynelCloseBattle(const InitArg& arg) : EnemyBattle(arg) {}

LynelCloseBattle::~LynelCloseBattle() = default;

bool LynelCloseBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void LynelCloseBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
    *mLynelAIFlags_a |= 0x800;
}

void LynelCloseBattle::leave_() {
    EnemyBattle::leave_();
}

void LynelCloseBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mBackAngleAction_s, "BackAngleAction");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getAITreeVariable(&mLynelAIFlags_a, "LynelAIFlags");
}

bool LynelCloseBattle::isFinished() const {
    return ActionBase::isFinished() ||
           (isCurrentChild("戦闘攻撃") && getCurrentChild()->isFinished() &&
            (*mBackAngleAction_s != 1 || !sub_710048FA58()));
}

bool LynelCloseBattle::isFailed() const {
    if (ActionBase::isFailed() || getCurrentChild()->isFailed())
        return true;
    if (*mBackAngleAction_s == 1 && isCurrentChild("戦闘攻撃") && getCurrentChild()->isFinished())
        return sub_710048FA58();
    return false;
}

}  // namespace uking::ai
