#include "Game/Actor/Action/actionForkFixedAngleVacuumShootTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_710073EBD4.h"
#include "KingSystem/Utils/MathUtil.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <random/seadGlobalRandom.h>

namespace uking::action {

ForkFixedAngleVacuumShootTarget::ForkFixedAngleVacuumShootTarget(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkFixedAngleVacuumShootTarget::~ForkFixedAngleVacuumShootTarget() = default;

bool ForkFixedAngleVacuumShootTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkFixedAngleVacuumShootTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkFixedAngleVacuumShootTarget::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkFixedAngleVacuumShootTarget::loadParams_() {
    getStaticParam(&mShootSpeedMin_s, "ShootSpeedMin");
    getStaticParam(&mShootSpeedMax_s, "ShootSpeedMax");
    getStaticParam(&mAngle_s, "Angle");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mPartsKey_s, "PartsKey");
    getStaticParam(&mShootOffset_s, "ShootOffset");
    getStaticParam(&mShootRotate_s, "ShootRotate");
    getStaticParam(&mShootRotSpeed_s, "ShootRotSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: matrix lanes stay in registers and angular velocity is not copied to the stack.
void ForkFixedAngleVacuumShootTarget::sub_7100150D4C() {
    sead::Matrix34f base = mActor->getMtx();
    if (!mBaseNode_s.isEmpty()) {
        auto* model = mActor->getModel();
        const auto bone = model->searchBone(mBaseNode_s);
        if (bone.isValid())
            model->getUnits().unsafeAt(bone.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                &base, bone.bone_index);
    }
    sead::Matrix34f offset;
    offset.makeRT(*mShootRotate_s, *mShootOffset_s);
    sead::Matrix34f pose;
    pose.setMul(base, offset);
    const sead::Vector3f origin = pose.getTranslation();
    sead::Vector3f velocity;
    sub_71001511B4(&velocity, &origin);
    sead::Vector3f angular_velocity;
    angular_velocity.setRotated(base, *mShootRotSpeed_s);
    sub_710073EA44(mActor, mPartsKey_s, pose, &velocity, &angular_velocity, !*mIsReuseBullet_s);
}

// NON_MATCHING: direction stores and the up-vector loads are scheduled differently.
void ForkFixedAngleVacuumShootTarget::sub_71001511B4(sead::Vector3f* out,
                                                   const sead::Vector3f* origin) {
    sead::Vector3f target = *mTargetPos_d;
    target.y += *mOffsetHeight_s;
    sead::Vector3f noise = sead::Vector3f::ez;
    ksys::util::sub_71011EEFB4(
        &noise, sead::GlobalRandom::instance()->getF32Range(-sead::Mathf::piHalf(),
                                                          sead::Mathf::piHalf()));
    ksys::util::sub_71011EF010(
        &noise, sead::GlobalRandom::instance()->getF32Range(-sead::Mathf::piHalf(),
                                                          sead::Mathf::piHalf()));
    noise *= *mMaxNoiseDist_s * sead::GlobalRandom::instance()->getF32();
    const sead::Vector3f direction = target + noise - *origin;
    if (!sub_71005DCB3C(out, mActor, &direction, *mAngle_s, *mShootSpeedMax_s)) {
        sead::Vector3f horizontal(direction.x, 0.0f, direction.z);
        horizontal.normalize();
        sead::Vector3f velocity = horizontal * sead::Mathf::cos(*mAngle_s);
        velocity += sead::Vector3f::ey * sead::Mathf::sin(*mAngle_s);
        velocity.normalize();
        *out = velocity * *mShootSpeedMin_s;
    }
}

void ForkFixedAngleVacuumShootTarget::calc_() {
    if (sub_71005DD780(mActor, 71, nullptr, 0, 0))
        sub_7100150D4C();
}

}  // namespace uking::action
