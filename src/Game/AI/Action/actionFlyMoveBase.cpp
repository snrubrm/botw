#include "Game/AI/Action/actionFlyMoveBase.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
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
    _6c.reset(0.0f, 1.0f);
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

bool FlyMoveBase::sub_7100134380() {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f target;
    m32(&target);
    const f32 dx = target.x - pos.x;
    const f32 dz = target.z - pos.z;
    return std::sqrt(dx * dx + dz * dz) <= *mParams.mHorizontalFinRadius_s &&
           sead::Mathf::abs(target.y - pos.y) <= *mParams.mVerticalFinLength_s;
}

void FlyMoveBase::calc_() {
    if (sub_7100134380()) {
        setFinished();
        return;
    }
    if (!sub_710013443C())
        setFailed();
}

// NON_MATCHING: the original selects the chase target through a pointer to a block-scope local
// (`half_speed`) that is used after its block ends (stack slot shared with the later velocity
// temporary); ours keeps the local alive (frame 0x10 larger). Not reproduced: it would be a dangling pointer.
bool FlyMoveBase::sub_710013443C() {
    sead::Vector3f dir;
    f32 dist;
    m33(&dir, &dist);
    sead::Vector3f forward = mActor->getMtx().getBase(2);
    forward.normalize();
    if (sub_7100134774(dir))
        return false;
    const sead::Vector3f up = getUpDir(mActor);
    sub_710074006C(&_84, dir, up, false, *mParams.mRotRatio_s, *mParams.mRotSpd_s,
                   *mParams.mRotSpd_s * 0.25f);
    sead::Vector3f axis;
    f32 angle;
    ksys::util::sub_71011EEB08(&axis, &angle, forward, dir, sead::Vector3f::ey);
    const f32* speed = mParams.mSpeed_s;
    f32 step = *mParams.mSpeed_s * 0.1f;
    f32 half_speed;
    if (*mParams.mRotSpd_s * 2.5 < angle) {
        half_speed = *mParams.mSpeed_s * 0.5f;
        step *= 0.5f;
        speed = &half_speed;
    }
    _60.chase(*speed, step);
    _60.setToMin(dist);
    _60.updateStats();
    ksys::act::sub_7100EE5980(mActor, forward * _60.value);
    sub_7100740F1C(_84, mActor);
    return true;
}

// NON_MATCHING: register allocation / scheduling of the contact point direction components.
bool FlyMoveBase::sub_7100134774(const sead::Vector3f& dir) {
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    if (isLandedMaybe(actor, false) && dir.dot(sub_71007A471C(actor, 0)->_c) < 0.0f) {
        _6c.update();
        return _6c.value > 20.0f;
    }
    if (controller && controller->sub_7100F5F264()) {
        if (auto* info = controller->sub_7100F635D8()) {
            const sead::Vector3f pos = actor->getMtx().getTranslation();
            auto it = info->begin();
            auto end = info->end();
            while (it != end) {
                sead::Vector3f point;
                it.getPointPosition(&point, ksys::phys::ContactPointInfo::Iterator::Point::BodyA);
                sead::Vector3f to_point = point - pos;
                to_point.normalize();
                if (to_point.dot(dir) >= 0.49999997f) {
                    _6c.update();
                    return _6c.value > 20.0f;
                }
                ++it;
            }
        }
    }
    _6c.reset(0.0f, 1.0f);
    return false;
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
