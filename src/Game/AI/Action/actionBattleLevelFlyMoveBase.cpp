#include "Game/AI/Action/actionBattleLevelFlyMoveBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: scheduling only (the vtable address add and the VFRVec3f address are ordered differently)
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
    _84 = {0, 0, 1};
    _90 = {0, 0, 1};
    mFlags.set(Flag::Changeable);
}

void BattleLevelFlyMoveBase::leave_() {
    auto* actor = mActor;
    _cc.resetRigidBodyMotion(actor);
    _cc.resetMotionType(_cc.sub_710072ACF8(actor));
}

void BattleLevelFlyMoveBase::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mCheckStopSpeed_s, "CheckStopSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void BattleLevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
