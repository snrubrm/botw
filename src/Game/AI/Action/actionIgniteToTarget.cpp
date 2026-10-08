#include "Game/AI/Action/actionIgniteToTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::action {

IgniteToTarget::IgniteToTarget(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteToTarget::~IgniteToTarget() = default;

bool IgniteToTarget::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void IgniteToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IgniteToTarget::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteToTarget::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getStaticParam(&mBaseNode_s, "BaseNode");
}

void IgniteToTarget::calc_() {
    OnetimeStopASPlay::calc_();
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        sub_71001B734C(m32());
}

ksys::act::BaseProcHandle* IgniteToTarget::m32() {
    return *mIgniteHandle_d;
}

const sead::Vector3f* IgniteToTarget::m33() {
    return mIgniteOffset_s;
}

const sead::Vector3f* IgniteToTarget::m34() {
    return mIgniteRotate_s;
}

f32 IgniteToTarget::m35(ksys::act::Actor* actor) {
    sead::Vector3f gravity;
    sub_710072DC50(&gravity, actor);
    return gravity.y * (1.0f / 900.0f);
}

// NON_MATCHING: register allocation, spill slots and scheduling order only; all calls,
// values and control flow match (same family as IgniteToTargetSimple::m32, but the
// offset/rotation come from the m33/m34 virtuals, the front vector is the actor's Z
// column, and the velocity is solved by sub_71005DDF80 with dir-noise angles).
void IgniteToTarget::sub_71001B734C(ksys::act::BaseProcHandle* handle) {
    auto* actor = mActor;
    if (!handle)
        return;
    auto* proc = handle->getProc();
    if (sead::DynamicCast<ksys::act::Actor>(proc) == nullptr)
        return;
    auto* model = mActor->getModel();
    sead::Matrix34f base_mtx;
    gsys::BoneAccessKey key;
    if (model && *mBaseNode_s.getStringTop() != sead::SafeString::cNullChar)
        key = model->searchBone(mBaseNode_s);
    if (key.isValid()) {
        actor->getModel()
            ->getUnits()
            .unsafeAt(key.model_unit_index)
            ->mModelUnit->getBoneWorldMatrix(&base_mtx, key.bone_index);
    } else {
        base_mtx = actor->getMtx();
    }

    const f32 m00 = base_mtx.m[0][0];
    const f32 m01 = base_mtx.m[0][1];
    const f32 m02 = base_mtx.m[0][2];
    const f32 m03 = base_mtx.m[0][3];
    const f32 m10 = base_mtx.m[1][0];
    const f32 m11 = base_mtx.m[1][1];
    const f32 m12 = base_mtx.m[1][2];
    const f32 m13 = base_mtx.m[1][3];
    const f32 m20 = base_mtx.m[2][0];
    const f32 m21 = base_mtx.m[2][1];
    const f32 m22 = base_mtx.m[2][2];
    const f32 m23 = base_mtx.m[2][3];

    const sead::Vector3f* offset = m33();

    const sead::Matrix34f& actor_mtx = mActor->getMtx();
    sead::Vector3f front{actor_mtx.m[0][2], actor_mtx.m[1][2], actor_mtx.m[2][2]};
    front.normalize();

    sead::Vector3f pos;
    pos.x = offset->x * m00 + offset->y * m01 + offset->z * m02 + m03;
    pos.y = offset->x * m10 + offset->y * m11 + offset->z * m12 + m13;
    pos.z = offset->x * m20 + offset->y * m21 + offset->z * m22 + m23;

    const sead::Vector3f* rot = m34();
    const f32 sx = sinf(rot->x);
    const f32 sy = sinf(rot->y);
    const f32 sz = sinf(rot->z);
    const f32 cx = cosf(rot->x);
    const f32 cy = cosf(rot->y);
    const f32 cz = cosf(rot->z);
    sead::Matrix33f rot_mtx;
    rot_mtx.m[0][0] = m00 * (cy * cz) + m01 * (cy * sz) - m02 * sy;
    rot_mtx.m[0][1] =
        m00 * (sx * sy * cz - cx * sz) + m01 * (sx * sy * sz + cx * cz) + m02 * (sx * cy);
    rot_mtx.m[0][2] = m02 * (cx * cy) + m00 * (sx * sz + sy * cx * cz) +
                     m01 * (sy * sz * cx - sx * cz);
    rot_mtx.m[1][0] = m10 * (cy * cz) + m11 * (cy * sz) - m12 * sy;
    rot_mtx.m[1][1] =
        m10 * (sx * sy * cz - cx * sz) + m11 * (sx * sy * sz + cx * cz) + m12 * (sx * cy);
    rot_mtx.m[1][2] = m12 * (cx * cy) + m10 * (sx * sz + sy * cx * cz) +
                     m11 * (sy * sz * cx - sx * cz);
    rot_mtx.m[2][0] = m20 * (cy * cz) + m21 * (cy * sz) - m22 * sy;
    rot_mtx.m[2][1] =
        m20 * (sx * sy * cz - cx * sz) + m21 * (sx * sy * sz + cx * cz) + m22 * (sx * cy);
    rot_mtx.m[2][2] = m22 * (cx * cy) + m20 * (sx * sz + sy * cx * cz) +
                     m21 * (sy * sz * cx - sx * cz);

    sead::Vector3f target_pos = *mTargetPos_d;
    target_pos.y += *mOffsetHeight_s;
    const f32 speed = *mIgniteSpeed_s;
    const f32 gravity = m35(static_cast<ksys::act::Actor*>(proc));
    sead::Vector3f vel;
    sub_71005DDF80(&vel, &target_pos, &pos, &front, mDirMinAngle_s, mDirMaxAngle_s, speed,
                   gravity, *mMaxNoiseDist_s);

    const sead::Vector3f rot_spd = *mIgniteRotSpeed_s;
    sead::Vector3f ang_vel;
    ang_vel.x = m00 * rot_spd.x + m01 * rot_spd.y + m02 * rot_spd.z;
    ang_vel.y = m10 * rot_spd.x + m11 * rot_spd.y + m12 * rot_spd.z;
    ang_vel.z = m20 * rot_spd.x + m21 * rot_spd.y + m22 * rot_spd.z;

    sub_71005DFAE0(handle, mActor, &pos, &rot_mtx, &vel, &ang_vel);
}

}  // namespace uking::action
