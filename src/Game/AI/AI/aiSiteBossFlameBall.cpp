#include "Game/AI/AI/aiSiteBossFlameBall.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

SiteBossFlameBall::SiteBossFlameBall(const InitArg& arg) : SiteBossChemicalProjectile(arg) {}

SiteBossFlameBall::~SiteBossFlameBall() = default;

bool SiteBossFlameBall::init_(sead::Heap* heap) {
    return SiteBossChemicalProjectile::init_(heap);
}

void SiteBossFlameBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossChemicalProjectile::enter_(params);
    _1c8 = false;
    _1c9 = true;
    _1c0 = *mCountOffset_s * f32(*mCount_m);
    _1c4 = 10.0f;

    auto* main_body = mActor->getMainBody();
    auto* physics = mActor->getPhysics();
    if (main_body && physics) {
        main_body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityNoHit,
                                             physics->get188(0));
    }

    auto* atk_body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody");
    if (physics && atk_body) {
        atk_body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorNoHit,
                                            physics->get188(1));
    }

    auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "RigidBody_0");
    if (physics && body) {
        body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorNoHit,
                                        physics->get188(1));
    }
}

void SiteBossFlameBall::calc_() {
    SiteBossChemicalProjectile::calc_();

    if (isCurrentChild("発射") && _1c4 > 0.0f) {
        ksys::Timer::update(&_1c4, -1.0f);
        if (_1c4 <= 0.0f) {
            auto* main_body = mActor->getMainBody();
            auto* physics = mActor->getPhysics();
            if (main_body && physics) {
                main_body->setContactLayerAndHandler(ksys::phys::ContactLayer::EntityObject,
                                                     physics->get188(0));
                SiteBossChemicalProjectile::m53(main_body);
            }

            if (auto* atk_body =
                    mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
                atk_body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorAttackEnemy,
                                                    physics->get188(1));
                SiteBossChemicalProjectile::m52(atk_body);
            }

            auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "RigidBody_0");
            if (physics && body) {
                body->setContactLayerAndHandler(ksys::phys::ContactLayer::SensorEnemy,
                                                physics->get188(1));
            }
        }
    }
    _1c9 = false;
}

void SiteBossFlameBall::leave_() {
    SiteBossChemicalProjectile::leave_();
}

void SiteBossFlameBall::loadParams_() {
    SiteBossChemicalProjectile::loadParams_();
    getStaticParam(&mChemicalIndex_s, "ChemicalIndex");
    getStaticParam(&mAtAttr_s, "AtAttr");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveOffset_s, "MoveOffset");
    getStaticParam(&mCountOffset_s, "CountOffset");
    getStaticParam(&mIsInfluence_s, "IsInfluence");
    getMapUnitParam(&mCount_m, "Count");
    getMapUnitParam(&mPosOffset_m, "PosOffset");
}

sead::Vector3f SiteBossFlameBall::m35() {
    return *mPosOffset_m;
}

bool SiteBossFlameBall::m40() {
    if (_1c9)
        return false;
    auto* chemical = mActor->sub_71011D8A44(*mChemicalIndex_s);
    if (chemical && chemical->_b9[0] & 2)
        return true;
    return _d9;
}

bool SiteBossFlameBall::m41() {
    if (!_1c8 && sub_71007A2604(mActor))
        _1c8 = true;
    else if (_1c8)
        return true;
    return false;
}

u32 SiteBossFlameBall::m51() {
    return *mAtAttr_s;
}

}  // namespace uking::ai
