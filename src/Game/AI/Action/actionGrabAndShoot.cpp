#include "Game/AI/Action/actionGrabAndShoot.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

GrabAndShoot::GrabAndShoot(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GrabAndShoot::~GrabAndShoot() = default;

void GrabAndShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    if (!controller)
        return;

    playAS("GrabAndShoot", false, 0, 0, -1.0f);
    sead::Vector3f velocity = mActor->getVelocity();
    const f32 speed = velocity.normalize();
    _74.value = speed;
    _74.prev_value = speed;
    sub_710072C1B4(controller, velocity);

    sead::Vector3f ang_velocity = mActor->getAngVelocity();
    const sead::Vector3f up = getUpDir(controller->get70());
    ksys::util::sub_71011EFA54(&ang_velocity, ang_velocity, up);
    controller->sub_7100F5FB24(ang_velocity);
    sub_710073FA90(&_50, mActor);
    _80 = 0;
}

void GrabAndShoot::leave_() {
    ksys::act::ai::Action::leave_();
}

void GrabAndShoot::loadParams_() {
    getStaticParam(&mParams.mGrabIdx_s, "GrabIdx");
    getStaticParam(&mParams.mShootSpeed_s, "ShootSpeed");
    getStaticParam(&mParams.mShootAng_s, "ShootAng");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    getStaticParam(&mParams.mBlurMax_s, "BlurMax");
}

void GrabAndShoot::calc_() {
    ksys::act::ai::Action::calc_();
}

bool GrabAndShoot::isChangeable() const {
    return false;
}

}  // namespace uking::action
