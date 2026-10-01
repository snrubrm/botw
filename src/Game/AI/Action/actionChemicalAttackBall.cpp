#include "Game/AI/Action/actionChemicalAttackBall.h"

namespace uking::action {

ChemicalAttackBall::ChemicalAttackBall(const InitArg& arg) : ChemicalAttack(arg) {}

ChemicalAttackBall::~ChemicalAttackBall() = default;

bool ChemicalAttackBall::init_(sead::Heap* heap) {
    return ChemicalAttack::init_(heap);
}

void ChemicalAttackBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ChemicalAttack::enter_(params);
}

void ChemicalAttackBall::leave_() {
    ChemicalAttack::leave_();
}

void ChemicalAttackBall::loadParams_() {
    ChemicalAttack::loadParams_();
    getStaticParam(&mIsUseMyRange_s, "IsUseMyRange");
    getStaticParam(&mAttackType_s, "AttackType");
}

void ChemicalAttackBall::calc_() {
    ChemicalAttack::calc_();
}

int ChemicalAttackBall::m35() {
    switch (*mAttackType_s) {
    case 0:
        return 0x800;
    case 1:
        return 0x2000;
    default:
        return 0x800;
    }
}

}  // namespace uking::action
