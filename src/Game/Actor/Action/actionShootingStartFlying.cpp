#include "Game/Actor/Action/actionShootingStartFlying.h"
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <gfx/seadViewport.h>
#include <math/seadQuat.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldShootingStarMgr.h"

// 0x7100d8aed0 (declared only): sets `projection` up from the camera's parameters.
void sub_7100D8AED0(sead::LookAtCamera* camera, sead::PerspectiveProjection* projection);

namespace uking::action {

ShootingStartFlying::ShootingStartFlying(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShootingStartFlying::~ShootingStartFlying() = default;

bool ShootingStartFlying::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: camera direction and quaternion rotation scheduling.
void ShootingStartFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    _70 = 0.0f;
    _74 = 0.0f;
    _78 = 0.0f;
    sead::Vector3f direction;
    ksys::sub_7100D8C7FC(&direction);
    direction.y = 0.0f;
    direction.normalize();
    sead::Vector3f velocity = direction *
        (sead::GlobalRandom::instance()->getF32Range(*mInitialVelocityMin_s,
                                                    *mInitialVelocityMax_s) * 30.0f);
    const f32 half_range = *mInitialAngleRange_s * 0.5f;
    sead::Quatf rotation;
    rotation.setAxisRadian(sead::Vector3f::ey,
        sead::GlobalRandom::instance()->getF32Range(-half_range, half_range));
    sead::Matrix33f matrix;
    matrix.fromQuat(rotation);
    velocity.setRotated(matrix, velocity);
    mActor->x_22(velocity, sead::Vector3f::zero);
}

void ShootingStartFlying::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShootingStartFlying::loadParams_() {
    getStaticParam(&mInitialVelocityMax_s, "InitialVelocityMax");
    getStaticParam(&mInitialVelocityMin_s, "InitialVelocityMin");
    getStaticParam(&mInitialAngleRange_s, "InitialAngleRange");
    getStaticParam(&mLookSuccessRate_s, "LookSuccessRate");
    getStaticParam(&mMaxWaterDepth_s, "MaxWaterDepth");
    getStaticParam(&mGravity_s, "Gravity");
}

bool ShootingStartFlying::sub_71002502E8() {
    auto* camera = ksys::CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return false;
    sead::Vector3f look;
    camera->getLookVectorByMatrix(&look);
    if ((mActor->getMtx().getTranslation() - camera->getPos()).dot(look) < 0) {
        if (auto* viewport = ksys::CameraMgr::instance()->sub_7100D8C4C8()) {
            sead::PerspectiveProjection projection;
            sub_7100D8AED0(camera, &projection);
            sead::Vector2f screen;
            camera->projectByMatrix(&screen, mActor->getMtx().getTranslation(), projection,
                                    *viewport);
            screen.x /= viewport->getSizeX();
            screen.y /= viewport->getSizeY();
            if (!(screen.x > -0.5f && screen.x < 0.5f))
                return false;
            return screen.y > -0.5f && screen.y < 0.5f;
        }
    }
    return false;
}

// NON_MATCHING: vector calculations, ray-query stack storage and branch layout.
void ShootingStartFlying::calc_() {
    if (isFinished() || isFailed())
        return;
    if (sub_71002502E8())
        ksys::Timer::update(&_70, 1.0f);
    ksys::Timer::update(&_74, 1.0f);
    mActor->getMainBody()->setGravityFactor(*mGravity_s);
    if (auto* world = ksys::world::Manager::instance()) {
        if (auto* star = world->getShootingStarMgr()) {
            if (star->sub_71010DCE2C()) {
                sead::Vector3f direction = star->getStarProperty() - mActor->getMtx().getTranslation();
                direction.normalize();
                mActor->getMainBody()->changePosition(
                    mActor->getMtx().getTranslation() + direction * *mInitialVelocityMax_s,
                    ksys::phys::KeepAngularVelocity{false}, sead::Mathf::epsilon());
            }
        }
    }
    sead::Vector3f velocity = -sead::Vector3f::ey;
    if (mActor->getVelocity() == sead::Vector3f(0.0f, 0.0f, 0.0f))
        ksys::Timer::update(&_78, 1.0f);
    else
        velocity = mActor->getVelocity();
    if (_78 > 60.0f)
        setFailed();
    if (velocity.y <= 0.0f) {
        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        query.enableLayer(ksys::phys::ContactLayer::EntityGround);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        query.enableLayer(ksys::phys::ContactLayer::EntityHitOnlyGround);
        query.enableLayer(ksys::phys::ContactLayer::EntityWater);
        sead::Vector3f position = mActor->getMtx().getTranslation();
        query.setStartAndDisplacementScaled(position, velocity,
            velocity.length() * ksys::VFR::instance()->getDeltaFrame() + 1.0f);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            query.getHitPosition(&position);
            f32 ground_height = -1.0f;
            f32 water_height = -1.0f;
            const u32 ground = sub_710072C21C(&ground_height, &position);
            const u32 water = sub_710072C494(&water_height, &position);
            const f32 depth = ground && water ? water_height - ground_height : -1.0f;
            auto* world = ksys::world::Manager::instance();
            if (depth > *mMaxWaterDepth_s || !world ||
                world->getStageType() != ksys::StageType::OpenWorld ||
                sead::Vector2f(320.0f - position.x, -3125.0f - position.z).length() < 210.0f ||
                sead::Vector2f(312.0f - position.x, -2197.0f - position.z).length() < 700.0f ||
                sead::Vector2f(-3625.0f - position.x, -1865.0f - position.z).length() < 150.0f ||
                sead::Vector2f(2435.0f - position.x, -2570.0f - position.z).length() < 90.0f ||
                sead::Vector2f(-2110.145f - position.x, 2616.955f - position.z).length() < 130.0f ||
                sead::Vector2f(2970.184f - position.x, 235.4673f - position.z).length() < 135.0f) {
                setFailed();
            } else {
                mActor->get68c() = true;
                if (_70 / _74 * 100.0f > *mLookSuccessRate_s) {
                    if (auto* world2 = ksys::world::Manager::instance()) {
                        if (auto* star = world2->getShootingStarMgr())
                            star->setStarPosition(position.x, position.y, position.z);
                    }
                    setFinished();
                } else {
                    setFailed();
                }
                return;
            }
        }
    }
    flyingObjectEmitXlink(mActor, "Tail", 2, &_50);
}

}  // namespace uking::action
