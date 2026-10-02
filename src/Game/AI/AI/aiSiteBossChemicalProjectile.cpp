#include "Game/AI/AI/aiSiteBossChemicalProjectile.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

SiteBossChemicalProjectile::SiteBossChemicalProjectile(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

SiteBossChemicalProjectile::~SiteBossChemicalProjectile() {
    if (mIsSetParentSystemGroupHandler_s && *mIsSetParentSystemGroupHandler_s) {
        if (auto* physics = mActor->getPhysics())
            physics->sub_7100FB835C();
    }
}

bool SiteBossChemicalProjectile::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossChemicalProjectile::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossChemicalProjectile::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossChemicalProjectile::loadParams_() {
    getStaticParam(&mExplosionTime_s, "ExplosionTime");
    getStaticParam(&mChaseAngleLimit_s, "ChaseAngleLimit");
    getStaticParam(&mReflectSpeedRate_s, "ReflectSpeedRate");
    getStaticParam(&mIsForceDelete_s, "IsForceDelete");
    getStaticParam(&mIsAdjustHeight_s, "IsAdjustHeight");
    getStaticParam(&mIsSetParentSystemGroupHandler_s, "IsSetParentSystemGroupHandler");
    getStaticParam(&mIsSetBindSpeed_s, "IsSetBindSpeed");
    getStaticParam(&mIsIgnoreObject_s, "IsIgnoreObject");
    getStaticParam(&mBindNodeName_s, "BindNodeName");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mScaleTime_m, "ScaleTime");
    getMapUnitParam(&mRange_m, "Range");
    getMapUnitParam(&mAtkRadiusMax_m, "AtkRadiusMax");
}

const sead::SafeString& SiteBossChemicalProjectile::m34() {
    return mBindNodeName_s;
}

sead::Vector3f SiteBossChemicalProjectile::m35() {
    return {0.0f, 2.0f, 0.0f};
}

sead::Vector3f SiteBossChemicalProjectile::m36() {
    return sead::Vector3f::ones;
}

void SiteBossChemicalProjectile::m37() {}

bool SiteBossChemicalProjectile::m39() {
    return true;
}

bool SiteBossChemicalProjectile::m40() {
    return _d9;
}

bool SiteBossChemicalProjectile::m41() {
    return false;
}

void SiteBossChemicalProjectile::m43() {}

const sead::Vector3f& SiteBossChemicalProjectile::m45() {
    return _bc;
}

void SiteBossChemicalProjectile::m46(const sead::Vector3f& v) {
    _bc = v;
    _118 = v.length();
}

void SiteBossChemicalProjectile::m47(f32 v) {
    _dc = v;
}

const sead::Vector3f& SiteBossChemicalProjectile::m48() {
    return _c8;
}

void SiteBossChemicalProjectile::m49(const sead::Vector3f& v) {
    _c8 = v;
}

u32 SiteBossChemicalProjectile::m50() {
    return 0x800;
}

u32 SiteBossChemicalProjectile::m51() {
    return 4;
}

void SiteBossChemicalProjectile::m52(ksys::phys::RigidBody* body) {
    sub_71007A2B64(body, nullptr);
    sub_71007A2EB0(body, mActor, nullptr);
}

void SiteBossChemicalProjectile::m53(ksys::phys::RigidBody* body) {
    body->setContactNone();
    body->enableContactLayer(ksys::phys::ContactLayer(3));
    body->enableContactLayer(ksys::phys::ContactLayer(4));
    body->enableContactLayer(ksys::phys::ContactLayer(5));
}

bool SiteBossChemicalProjectile::m54() {
    return *mIsAdjustHeight_s && !m55();
}

bool SiteBossChemicalProjectile::m55() {
    return _d4;
}

bool SiteBossChemicalProjectile::m56() {
    return !m55();
}

f32 SiteBossChemicalProjectile::m57() {
    return *mChaseAngleLimit_s;
}

}  // namespace uking::ai
