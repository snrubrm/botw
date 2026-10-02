#include "Game/AI/Action/actionChemicalAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"

namespace uking::action {

ChemicalAttack::ChemicalAttack(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChemicalAttack::~ChemicalAttack() = default;

bool ChemicalAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChemicalAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChemicalAttack::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChemicalAttack::loadParams_() {
    getStaticParam(&mAttackIntensity_s, "AttackIntensity");
    getStaticParam(&mAttackMinPower_s, "AttackMinPower");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAttackPowerForPlayer_m, "AttackPowerForPlayer");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mRange_m, "Range");
    getMapUnitParam(&mRigidBodyName_m, "RigidBodyName");
}

void ChemicalAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

void ChemicalAttack::m32() {
    ksys::act::sub_7100EE5980(mActor, _6c);
}

float ChemicalAttack::m34() {
    return *mRange_m;
}

int ChemicalAttack::m35() {
    return 8192;
}

int ChemicalAttack::m37() {
    return *mAttackPower_m;
}

int ChemicalAttack::m38() {
    return *mAttackPowerForPlayer_m;
}

int ChemicalAttack::m36() {
    switch (*mAttackIntensity_s) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 4;
    default:
        return 0;
    }
}

int ChemicalAttack::m39() {
    return -1;
}

bool ChemicalAttack::m33() {
    auto* actor = mActor;
    if (isLandedMaybe(actor, false))
        return true;
    return (actor->getMtx().getTranslation() - _60).length() > m34();
}

}  // namespace uking::action
