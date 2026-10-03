#include "Game/AI/Action/actionFlyMoveBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

// NON_MATCHING: instruction scheduling (stp of the 0x50 params vs add x0)
FlyMoveBase::FlyMoveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool FlyMoveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FlyMoveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (auto* cc = actor->getCharacterController())
        mCCAccessor.changeMotionType(cc, ksys::act::MotionType::Hover);

    const sead::Vector3f up = getUpDir(mActor);

    const f32 speed = actor->getVelocity().length();
    _60.value = _60.prev_value = speed;
    const f32 ang = ksys::util::sub_71011EFAA4(actor->getAngVelocity(), up);
    _a8.value = _a8.prev_value = ang;
    sub_710073FA90(&_84, actor);
    _6c.set(0, 0, 1);
    _78.set(0, 0, 1);
    mFlags.set(Flag::Changeable);
}

void FlyMoveBase::leave_() {
    auto* actor = mActor;
    mCCAccessor.resetRigidBodyMotion(actor);
    mCCAccessor.resetMotionType(mCCAccessor.sub_710072ACF8(actor));
}

void FlyMoveBase::loadParams_() {
    getStaticParam(&mParams.mSpeed_s, "Speed");
    getStaticParam(&mParams.mRotSpd_s, "RotSpd");
    getStaticParam(&mParams.mFinRotate_s, "FinRotate");
    getStaticParam(&mParams.mHorizontalFinRadius_s, "HorizontalFinRadius");
    getStaticParam(&mParams.mTargetHeightOffset_s, "TargetHeightOffset");
    getStaticParam(&mParams.mRotRatio_s, "RotRatio");
    getStaticParam(&mParams.mVerticalFinLength_s, "VerticalFinLength");
    getDynamicParam(&mParams.mTargetPos_d, "TargetPos");
}

void FlyMoveBase::calc_() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f target;
    m32(&target);
    const f32 dx = target.x - pos.x;
    const f32 dz = target.z - pos.z;
    if (std::sqrt(dx * dx + dz * dz) <= *mParams.mHorizontalFinRadius_s &&
        sead::Mathf::abs(target.y - pos.y) <= *mParams.mVerticalFinLength_s) {
        setFinished();
        return;
    }
    if (!sub_710013443C())
        setFailed();
}

void FlyMoveBase::m32(sead::Vector3f* target) {
    if (!target)
        return;
    target->set(*mParams.mTargetPos_d);
    target->y += *mParams.mTargetHeightOffset_s;
}

void FlyMoveBase::m33(sead::Vector3f* dir, f32* dist) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f v;
    m32(&v);
    v -= pos;
    const f32 len = v.normalize();
    if (dir)
        dir->set(v);
    if (dist)
        *dist = len;
}

}  // namespace uking::action
