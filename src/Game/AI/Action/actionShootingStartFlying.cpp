#include "Game/AI/Action/actionShootingStartFlying.h"
#include <gfx/seadCamera.h>
#include <gfx/seadProjection.h>
#include <gfx/seadViewport.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/CameraMgr.h"

// 0x7100d8aed0 (declared only): sets `projection` up from the camera's parameters.
void sub_7100D8AED0(sead::LookAtCamera* camera, sead::PerspectiveProjection* projection);

namespace uking::action {

ShootingStartFlying::ShootingStartFlying(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShootingStartFlying::~ShootingStartFlying() = default;

bool ShootingStartFlying::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShootingStartFlying::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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

// NON_MATCHING: only the local's destructor call differs: the original calls sead::Projection::~Projection (0xb1d898) directly,
// i.e. ~PerspectiveProjection() is inline/defaulted in the original sead; lib/sead declares it out of line.
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

void ShootingStartFlying::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
