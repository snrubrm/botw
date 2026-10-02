#include "Game/AI/Action/actionGanonTurnOnWall.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

GanonTurnOnWall::GanonTurnOnWall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonTurnOnWall::~GanonTurnOnWall() = default;

bool GanonTurnOnWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonTurnOnWall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mActor->getCharacterController())
        return;

    sead::Vector3f up;
    m33(&up);
    up.normalize();
    const f32 speed = mActor->getAngVelocity().length();
    _50.value = speed;
    _50.prev_value = speed;
    sub_710073FA90(&_5c, mActor);

    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= mActor->getMtx().getTranslation();
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    ksys::util::sub_71011EFA00(&front, front, up);
    front.normalize();

    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, front, to_target, sead::Vector3f::ey);
    mActor->getASList()->x_6(9, 0, sead::Mathf::rad2deg(angle) * axis.y);
    playAS("Turn_Up", false, 0, 0, -1.0f);

    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    else
        mFlags.reset(Flag::Changeable);
}

void GanonTurnOnWall::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonTurnOnWall::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void GanonTurnOnWall::calc_() {
    auto* controller = mActor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }

    sead::Vector3f up;
    m33(&up);
    up.normalize();
    sub_710073FA94(&_5c, mActor);
    m32(*mPosReduceRatio_s);

    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f to_target = *mTargetPos_d;
    to_target -= pos;
    ksys::util::sub_71011EFA00(&to_target, to_target, up);
    to_target.normalize();

    _50.lerp(*mRotSpd_s, 0.16f, *mRotSpd_s / 10.0f);
    _50.updateStats();
    sub_710074006C(&_5c, to_target, up, true, *mBaseRotRatio_s, _50.value, _50.value / 10.0f);
    sub_7100740E04(_5c, controller);

    sead::Vector3f front;
    mActor->getMtx().getBase(front, 2);
    const bool rotated = front.dot(to_target) >= std::cos(*mFinRotate_s);
    if (m34() && rotated)
        setFinished();
}

void GanonTurnOnWall::m32(f32 x) {
    if (auto* controller = mActor->getCharacterController())
        sub_7100737C0C(controller, x, controller->get70());
}

void GanonTurnOnWall::m33(sead::Vector3f* up) {
    if (auto* controller = mActor->getCharacterController())
        up->set(controller->get70());
    else
        up->set(sead::Vector3f::ey);
}

}  // namespace uking::action
