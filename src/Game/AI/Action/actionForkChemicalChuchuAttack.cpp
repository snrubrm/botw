#include "Game/AI/Action/actionForkChemicalChuchuAttack.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"
#include "KingSystem/System/Timer.h"

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
    switch (_e0) {
    case 0:
        _e0 = 1;
        break;
    case 1:
        if (isBgGroundHit(mActor, false)) {
            _e0 = 2;
            _d8 = *mLandAtkTime_s;
            sub_710014A0D0();
        }
        break;
    default:
        const sead::Matrix34f mtx = _d0->getTransform();
        _e8.mELink.setMatrix(mtx, {*mLandAtkRadius_s, *mLandAtkRadius_s, *mLandAtkRadius_s});
        ksys::Timer::update(&_d8, -1.0f);
        if (_d8 <= 0.0f) {
            _e0 = 3;
            sub_710015E71C();
            setFinished();
        }
        break;
    }
}

void ForkChemicalChuchuAttack::sub_710014A0D0() {
    const f32 radius = *mLandAtkRadius_s;
    if (_d0)
        _d0->setRadius(radius);
    xlinkSearchAndEmit(mActor, "ChemicalAttack", 2, &_e8);
    if (_d0) {
        const sead::Matrix34f mtx = _d0->getTransform();
        _e8.mELink.setMatrix(mtx, {radius, radius, radius});
    } else {
        _e8.mELink.setMatrix(mActor->getMtx(), {radius, radius, radius});
    }
}

}  // namespace uking::action
