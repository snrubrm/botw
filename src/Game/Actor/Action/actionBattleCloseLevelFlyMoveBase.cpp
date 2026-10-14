#include "Game/Actor/Action/actionBattleCloseLevelFlyMoveBase.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BattleCloseLevelFlyMoveBase::BattleCloseLevelFlyMoveBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

BattleCloseLevelFlyMoveBase::~BattleCloseLevelFlyMoveBase() = default;

bool BattleCloseLevelFlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BattleCloseLevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    _c4.changeMotionType(controller, ksys::act::MotionType::Hover);

    const sead::Vector3f dir = getReverseDirOrUp(controller->get70());
    const f32 speed = sead::Vector2f(actor->getVelocity().x, actor->getVelocity().z).length();
    _70.value = _70.prev_value = speed;
    _7c.value = actor->getVelocity().y;
    _7c.prev_value = actor->getVelocity().y;
    _ac.value = _ac.prev_value = ksys::util::sub_71011EFAA4(actor->getAngVelocity(), dir);
    sub_710073FA90(&_88, actor);
    controller->sub_7100F60AE0();
    sub_7100737708(controller, _70.value);
    mFlags.set(Flag::Changeable);
    _b8 = {0, 0, 0};
    _d0.sub_71006F3DE8();
}

void BattleCloseLevelFlyMoveBase::leave_() {
    auto* actor = mActor;
    _c4.resetRigidBodyMotion(actor);
    _c4.resetMotionType(_c4.sub_710072ACF8(actor));
    _d0.sub_71006F3DF4();
}

void BattleCloseLevelFlyMoveBase::loadParams_() {
    getStaticParam(&mParams.mXZSpeed_s, "XZSpeed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mParams.mVerticalFinLength_s, "VerticalFinLength");
    getStaticParam(&mParams.mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mParams.mRotRatio_s, "RotRatio");
    getStaticParam(&mParams.mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mParams.mDownSpeed_s, "DownSpeed");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
    _d0.sub_71006F3DF8();
}

void BattleCloseLevelFlyMoveBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
