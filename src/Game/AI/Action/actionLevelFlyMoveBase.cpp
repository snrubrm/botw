#include "Game/AI/Action/actionLevelFlyMoveBase.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

LevelFlyMoveBase::LevelFlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyMoveBase::~LevelFlyMoveBase() {
    _108.release();
}

bool LevelFlyMoveBase::init_(sead::Heap* heap) {
    return _108.acquire(heap, static_cast<Unk_71025afb58**>(mRefPosVibrateChecker_a));
}

void LevelFlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (!controller) {
        setFailed();
        return;
    }
    mFlags.set(Flag::Changeable);
    _110.changeMotionType(controller, ksys::act::MotionType::Hover);
    if (m32())
        setFinished();

    const sead::Vector3f dir = getReverseDirOrUp(controller->get70());
    const f32 speed = sead::Vector2f(actor->getVelocity().x, actor->getVelocity().z).length();
    _a8.value = _a8.prev_value = speed;
    _b4.value = actor->getVelocity().y;
    _b4.prev_value = actor->getVelocity().y;
    _fc.value = _fc.prev_value = ksys::util::sub_71011EFAA4(actor->getAngVelocity(), dir);
    sub_710073FA90(&_d8, actor);
    _c0 = {0, 0, 1};
    _cc = {0, 0, 1};

    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_108._0)) {
            if (*mVibrateMemoryStep_s > 0.0f)
                checker->_84 = *mVibrateMemoryStep_s;
            if (*mVibrateCheckFrame_s > 0.0f)
                checker->_88 = *mVibrateCheckFrame_s;
            checker->reset();
        }
    }
    _118.sub_71006F3DE8();
}

void LevelFlyMoveBase::leave_() {
    auto* actor = mActor;
    _110.resetRigidBodyMotion(actor);
    _110.resetMotionType(_110.sub_710072ACF8(actor));
    _118.sub_71006F3DF4();
}

void LevelFlyMoveBase::loadParams_() {
    getStaticParam(&mXZSpeed_s, "XZSpeed");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getStaticParam(&mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mVerticalFinLength_s, "VerticalFinLength");
    getStaticParam(&mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRiseSpeed_s, "RiseSpeed");
    getStaticParam(&mDownSpeed_s, "DownSpeed");
    getStaticParam(&mCheckStopSpeed_s, "CheckStopSpeed");
    getStaticParam(&mVibrateMemoryStep_s, "VibrateMemoryStep");
    getStaticParam(&mVibrateCheckFrame_s, "VibrateCheckFrame");
    getStaticParam(&mVibrateStopCheck_s, "VibrateStopCheck");
    getStaticParam(&mIsOverRise_s, "IsOverRise");
    getStaticParam(&mIsSlowDownNearGoal_s, "IsSlowDownNearGoal");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    _118.sub_71006F3DF8();
    getAITreeVariable(&mRefPosVibrateChecker_a, "RefPosVibrateChecker");
}

void LevelFlyMoveBase::calc_() {
    if (isFinished() || isFailed())
        return;
    sub_71001DA0D0();
    if (m32())
        setFinished();
    else
        sub_71001DA1A4();
}

void LevelFlyMoveBase::sub_71001DA0D0() {
    if (*mVibrateMemoryStep_s > 0.0f && *mVibrateCheckFrame_s > 0.0f) {
        if (auto* checker = sead::DynamicCast<Unk_71025b0578>(*_108._0))
            checker->sub_7100716408(mActor->getMtx().getTranslation());
    }
}

bool LevelFlyMoveBase::m32() {
    const f32 x = mActor->getMtx().m[0][3];
    const f32 y = mActor->getMtx().m[1][3];
    const f32 z = mActor->getMtx().m[2][3];
    sead::Vector3f target;
    m34(&target);
    const f32 dx = target.x - x;
    const f32 dz = target.z - z;
    if (sead::Mathf::sqrt(dx * dx + dz * dz) <= *mHorizontalFinRadius_s)
        return sead::Mathf::abs(target.y - y) <= *mVerticalFinLength_s;
    return false;
}

bool LevelFlyMoveBase::m33() {
    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    sead::Vector3f target;
    m34(&target);
    const f32 dx = target.x - x;
    const f32 dz = target.z - z;
    return sead::Mathf::sqrt(dx * dx + dz * dz) <= *mHorizontalFinRadius_s;
}

// NON_MATCHING: the stack slots of `axis` / `goal` are swapped and `rate * 0.5f` is computed in place instead of
// in a new register
void LevelFlyMoveBase::m35(ksys::VFRValue* speed, const sead::Vector3f& from,
                           const sead::Vector3f& to, f32 limit) {
    if (!speed)
        return;

    sead::Vector3f axis;
    f32 angle;
    sead::Vector3f goal;
    ksys::util::sub_71011EEB08(&axis, &angle, from, to, sead::Vector3f::ey);

    const f32 rate = sead::Mathf::max(speed->value, *mXZSpeed_s) * 0.1f;
    f32 target;
    f32 step = rate;
    bool slow = false;
    bool slow_near_goal = false;
    if (*mIsSlowDownNearGoal_s) {
        const f32 x = mActor->getMtx().m[0][3];
        const f32 z = mActor->getMtx().m[2][3];
        m34(&goal);
        const f32 dx = goal.x - x;
        const f32 dz = goal.z - z;
        slow_near_goal = sead::Mathf::sqrt(dx * dx + dz * dz) <= *mHorizontalFinRadius_s * 2;
    }
    if (slow_near_goal) {
        if (m33())
            target = 0;
        else
            slow = true;
    } else if (angle > *mRotSpd_s * 2.5) {
        slow = true;
    } else {
        target = *mXZSpeed_s;
    }
    if (slow) {
        target = *mXZSpeed_s * 0.5f;
        step = rate * 0.5f;
    }
    speed->chase(target, step);
    speed->setToMin(limit);
    speed->updateStats();
}

// NON_MATCHING: the negated chase target is stored before the `* 0.1f` step is computed (scheduling only).
void LevelFlyMoveBase::sub_71001DA7E4(f32 rate, f32 limit, ksys::VFRValue* value) {
    if (rate >= 0.0f) {
        value->chase(*mRiseSpeed_s, *mRiseSpeed_s * 0.1f);
        if (!*mIsOverRise_s)
            value->setToMin(limit);
    } else {
        const f32 down_speed = *mDownSpeed_s;
        value->chase(-down_speed, down_speed * 0.1f);
        if (!*mIsOverRise_s)
            value->setToMax(-limit);
    }
    value->updateStats();
    mActor->getASList()->x_6(10, 0, value->value);
}

void LevelFlyMoveBase::m34(sead::Vector3f* pos) {
    if (!pos)
        return;
    pos->set(*mTargetPos_d);
    pos->y += *mTargetHeightOffset_s;
}

}  // namespace uking::action
