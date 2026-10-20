#include "Game/Actor/Action/actionCollaboShootingStartFlying.h"
#include <codec/seadHashCRC32.h>
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <gfx/seadViewport.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

CollaboShootingStartFlying::CollaboShootingStartFlying(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CollaboShootingStartFlying::~CollaboShootingStartFlying() = default;

bool CollaboShootingStartFlying::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: initial parameter and singleton load scheduling differs.
void CollaboShootingStartFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    _78 = 0.0f;
    _7c = 0.0f;
    _80 = 0.0f;
    _84 = sead::GlobalRandom::instance()->getF32Range(*mInitialVelocityMin_s,
                                                   *mInitialVelocityMax_s) * 30.0f;
    if (const auto* anchor = ksys::world::ShootingStarMgrEx::sub_71010D0464(mIdentifier)) {
        if (auto* body = mActor->getMainBody()) {
            sead::Vector3f direction = anchor->_48 - mActor->getMtx().getTranslation();
            direction.normalize();
            body->setLinearVelocity(direction * _84);
        }
    }
    mActor->getMainBody()->setGravityFactor(0.0f);
}

void CollaboShootingStartFlying::leave_() {
    ksys::act::ai::Action::leave_();
}

void CollaboShootingStartFlying::loadParams_() {
    getStaticParam(&mInitialVelocityMax_s, "InitialVelocityMax");
    getStaticParam(&mInitialVelocityMin_s, "InitialVelocityMin");
    getStaticParam(&mLookSuccessRate_s, "LookSuccessRate");
    getAITreeVariable(&mCollaboShootingStarId_a, "CollaboShootingStarId");
    const sead::SafeString id = mCollaboShootingStarId_a->cstr();
    mIdentifier.name = id;
    mIdentifier.hash = sead::HashCRC32::calcStringHash(id.cstr());
}

void CollaboShootingStartFlying::calc_() {
    ksys::act::ai::Action::calc_();
}

bool CollaboShootingStartFlying::sub_71000E1384() {
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

}  // namespace uking::action
