#include "Game/AI/Action/actionForkChemicalChuchuAttack.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"

namespace uking::action {

ForkChemicalChuchuAttack::ForkChemicalChuchuAttack(const InitArg& arg)
    : ForkNoWeaponAttackAllTime(arg) {}

ForkChemicalChuchuAttack::~ForkChemicalChuchuAttack() = default;

bool ForkChemicalChuchuAttack::init_(sead::Heap* heap) {
    return ForkNoWeaponAttackAllTime::init_(heap);
}

void ForkChemicalChuchuAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkNoWeaponAttackAllTime::enter_(params);
    _e0 = 0;
    _d8 = 0;
}

void ForkChemicalChuchuAttack::leave_() {
    if (_d0)
        _d0->setRadius(_dc);
    ForkNoWeaponAttackAllTime::leave_();
}

void ForkChemicalChuchuAttack::loadParams_() {
    ForkNoWeaponAttackAllTime::loadParams_();
    getStaticParam(&mLandAtkTime_s, "LandAtkTime");
    getStaticParam(&mLandAtkRadius_s, "LandAtkRadius");
}

void ForkChemicalChuchuAttack::calc_() {
    ForkNoWeaponAttackAllTime::calc_();
}

}  // namespace uking::action
