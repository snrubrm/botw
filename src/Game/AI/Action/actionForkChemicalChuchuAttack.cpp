#include "Game/AI/Action/actionForkChemicalChuchuAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"

namespace uking::action {

ForkChemicalChuchuAttack::ForkChemicalChuchuAttack(const InitArg& arg)
    : ForkNoWeaponAttackAllTime(arg) {}

ForkChemicalChuchuAttack::~ForkChemicalChuchuAttack() = default;

bool ForkChemicalChuchuAttack::init_(sead::Heap* heap) {
    if (!ForkNoWeaponAttackAllTime::init_(heap))
        return false;
    auto* actor = mActor;
    auto* body = actor->findPhysicsBodyByName(ksys::act::getStr_Atk().cstr(), mAtkBodyName_s[0].cstr());
    _d0 = sead::DynamicCast<ksys::phys::SphereRigidBody>(body);
    if (_d0)
        _dc = _d0->getRadius();
    return true;
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
