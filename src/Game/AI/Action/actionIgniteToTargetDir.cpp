#include "Game/AI/Action/actionIgniteToTargetDir.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

IgniteToTargetDir::IgniteToTargetDir(const InitArg& arg) : IgniteToTargetSimple(arg) {}

IgniteToTargetDir::~IgniteToTargetDir() = default;

void IgniteToTargetDir::loadParams_() {
    IgniteToTargetSimple::loadParams_();
}

// NON_MATCHING: register allocation, spill slots and scheduling order only; all calls,
// values and control flow match (same family as IgniteToTargetSimple::m32, but the
// rotation matrix is built with sub_71011F0260 and the angular velocity is zero).
void IgniteToTargetDir::m32(ksys::act::BaseProcHandle* handle) {
    auto* actor = mActor;
    if (!handle)
        return;
    auto* proc = handle->getProc();
    if (sead::DynamicCast<ksys::act::Actor>(proc) == nullptr)
        return;
    auto* model = mActor->getModel();
    sead::SafeString name(mBaseNode_s.getStringTop());
    sead::Matrix34f base_mtx;
    gsys::BoneAccessKey key;
    if (model && *mBaseNode_s.getStringTop() != sead::SafeString::cNullChar)
        key = model->searchBone(name);
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

    const sead::Vector3f& offset = *mIgniteOffset_s;
    sead::Vector3f pos;
    pos.x = offset.x * m00 + offset.y * m01 + offset.z * m02 + m03;
    pos.y = offset.x * m10 + offset.y * m11 + offset.z * m12 + m13;
    pos.z = offset.x * m20 + offset.y * m21 + offset.z * m22 + m23;

    const sead::Vector3f& target = *mTargetPos_d;
    sead::Vector3f vel;
    vel.x = target.x - pos.x;
    vel.y = target.y + *mOffsetHeight_s - pos.y;
    vel.z = target.z - pos.z;
    vel.normalize();
    const sead::Vector3f dir = vel;
    vel *= *mIgniteSpeed_s;

    sead::Matrix34f mtx;
    ksys::util::sub_71011F0260(&mtx, dir, sead::Vector3f::ey, pos, false);
    sead::Matrix33f rot_mtx;
    rot_mtx.m[0][0] = mtx.m[0][0];
    rot_mtx.m[0][1] = mtx.m[0][1];
    rot_mtx.m[0][2] = mtx.m[0][2];
    rot_mtx.m[1][0] = mtx.m[1][0];
    rot_mtx.m[1][1] = mtx.m[1][1];
    rot_mtx.m[1][2] = mtx.m[1][2];
    rot_mtx.m[2][0] = mtx.m[2][0];
    rot_mtx.m[2][1] = mtx.m[2][1];
    rot_mtx.m[2][2] = mtx.m[2][2];

    const sead::Vector3f ang_vel = sead::Vector3f::zero;
    sub_71005DFAE0(handle, mActor, &pos, &rot_mtx, &vel, &ang_vel);
}

}  // namespace uking::action
