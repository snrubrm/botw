#include "Game/Actor/Action/actionBattleLevelFlyMoveBase.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BattleLevelFlyMoveBase::BattleLevelFlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BattleLevelFlyMoveBase::~BattleLevelFlyMoveBase() = default;

bool BattleLevelFlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleLevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _cc.changeMotionType(controller, ksys::act::MotionType::Hover);

    const sead::Vector3f dir = getReverseDirOrUp(controller->get70());
    _60.value = actor->getVelocity();
    _60.prev_value = actor->getVelocity();
    _c0.value = _c0.prev_value = ksys::util::sub_71011EFAA4(actor->getAngVelocity(), dir);
    sub_710073FA90(&_9c, actor);
    _84 = ksys::Timer(0, 0, 1);
    _90 = ksys::Timer(0, 0, 1);
    mFlags.set(Flag::Changeable);
}

void BattleLevelFlyMoveBase::leave_() {
    auto* actor = mActor;
    _cc.resetRigidBodyMotion(actor);
    _cc.resetMotionType(_cc.sub_710072ACF8(actor));
}

void BattleLevelFlyMoveBase::loadParams_() {
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mFinRadius_s, "FinRadius");
    getStaticParam(&mParams.mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mParams.mRotRatio_s, "RotRatio");
    getStaticParam(&mParams.mCheckStopSpeed_s, "CheckStopSpeed");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

// NON_MATCHING: target loads, registers and equivalent speed selection.
void BattleLevelFlyMoveBase::calc_() {
    sead::Vector3f target = *mParams.mTargetPos_d;
    target.y += *mParams.mTargetHeightOffset_s;
    if ((target - mActor->getMtx().getTranslation()).length() <= *mParams.mFinRadius_s) {
        setFinished();
        return;
    }
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    const sead::Vector3f position = actor->getMtx().getTranslation();
    target = *mParams.mTargetPos_d;
    target.y += *mParams.mTargetHeightOffset_s;
    sead::Vector3f direction = target - position;
    const f32 distance = direction.normalize();
    actor = mActor;
    if (isLandedMaybe(actor, false) &&
        (_84.value > 0.0f || direction.dot(sub_71007A471C(actor, 0)->_c) < 0.0f)) {
        _84.update();
        if (_84.value > 5.0f) {
            setFailed();
            return;
        }
    } else {
        _84 = ksys::Timer(0, 0, 1);
    }
    const f32 speed = mActor->getVelocity().length();
    const f32 stop_speed = *mParams.mCheckStopSpeed_s;
    if (speed <= stop_speed && speed >= -stop_speed) {
        _90.update();
        if (_90.value > 5.0f) {
            setFailed();
            return;
        }
    } else {
        _90 = ksys::Timer(0, 0, 1);
    }
    sub_71000C0384(position, controller);
    const f32 current_speed = _60.value.length();
    const f32 target_speed = *mParams.mSpeed_s;
    const f32 step = current_speed <= target_speed ? target_speed * 0.1f : current_speed * 0.5f;
    _60.chase(direction * target_speed, step);
    _60.normalize(distance);
    _60.updateStats();
    sub_7100737710(controller, _60.value);
}

// NON_MATCHING: direction component loads and stores are paired differently.
void BattleLevelFlyMoveBase::sub_71000C0384(const sead::Vector3f& position,
                                           ksys::phys::CharacterController* controller) {
    sead::Vector3f direction = sub_71005D960C(mActor) - position;
    direction.normalize();
    const sead::Vector3f up = getReverseDirOrUp(controller->get70());
    sub_710074006C(&_9c, direction, up, true, *mParams.mRotRatio_s,
                   *mParams.mRotSpd_s, *mParams.mRotSpd_s / 10.0f);
    sub_7100740E04(_9c, controller);
}

}  // namespace uking::action
