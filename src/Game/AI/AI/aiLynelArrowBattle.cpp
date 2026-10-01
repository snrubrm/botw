#include "Game/AI/AI/aiLynelArrowBattle.h"

namespace uking::ai {

LynelArrowBattle::LynelArrowBattle(const InitArg& arg) : EnemyBattle(arg) {}

LynelArrowBattle::~LynelArrowBattle() = default;

bool LynelArrowBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void LynelArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    _b8 = *mAttackCount_s;
    EnemyBattle::enter_(params);
}

void LynelArrowBattle::calc_() {
    EnemyBattle::calc_();
}

void LynelArrowBattle::leave_() {
    EnemyBattle::leave_();
}

void LynelArrowBattle::loadParams_() {
    EnemyBattle::loadParams_();
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mAttackCount_s, "AttackCount");
    getStaticParam(&mFrontCheckBoneName_s, "FrontCheckBoneName");
    getStaticParam(&mFrontDirFromBone_s, "FrontDirFromBone");
}

void LynelArrowBattle::m37() {
    EnemyBattle::m37();
}

bool LynelArrowBattle::m41() {
    return true;
}

void LynelArrowBattle::m38() {
    --_b8;
    EnemyBattle::m38();
}

bool LynelArrowBattle::isFinished() const {
    return ActionBase::isFinished() ||
           (getCurrentChild()->isFinished() && *mAttackCount_s > 0 && _b8 <= 0);
}

}  // namespace uking::ai
