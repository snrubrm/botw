#include "Game/AI/Action/actionGanonBeamIgnite.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

GanonBeamIgnite::GanonBeamIgnite(const InitArg& arg) : OnetimeStopASPlay(arg) {}

GanonBeamIgnite::~GanonBeamIgnite() = default;

bool GanonBeamIgnite::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void GanonBeamIgnite::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void GanonBeamIgnite::leave_() {
    OnetimeStopASPlay::leave_();
}

void GanonBeamIgnite::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIsConnectChild_s, "IsConnectChild");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteActor_d, "IgniteActor");
}

void GanonBeamIgnite::calc_() {
    OnetimeStopASPlay::calc_();
    if (sub_71005DD780(mActor, 71, nullptr, 0, 0))
        sub_71001745F8();
}

// NON_MATCHING: register allocation, spill slots and scheduling order only; all calls,
// values and control flow match (same ignite family: bone-located base matrix,
// offset pos, Euler rotation, 5ddf80 velocity solve, accessor setProperties tail).
void GanonBeamIgnite::sub_71001745F8() {
    auto* actor = mActor;
    if (!actor)
        return;
    if (sead::DynamicCast<ksys::act::Actor>(actor) == nullptr)
        return;
    auto* model = actor->getModel();
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

    const sead::Vector3f& offset = *mIgniteOffset_s;
    sead::Vector3f pos;
    pos.x = offset.x * m00 + offset.y * m01 + offset.z * m02 + m03;
    pos.y = offset.x * m10 + offset.y * m11 + offset.z * m12 + m13;
    pos.z = offset.x * m20 + offset.y * m21 + offset.z * m22 + m23;

    const sead::Vector3f& rot = *mIgniteRotate_s;
    const f32 sx = sinf(rot.x);
    const f32 sy = sinf(rot.y);
    const f32 sz = sinf(rot.z);
    const f32 cx = cosf(rot.x);
    const f32 cy = cosf(rot.y);
    const f32 cz = cosf(rot.z);

    sead::Vector3f target = *mTargetPos_d;
    target.y += *mOffsetHeight_s;

    sead::Vector3f vel = target;
    vel.x -= pos.x;
    vel.y -= pos.y;
    vel.z -= pos.z;
    vel.normalize();
    vel *= *mIgniteSpeed_s;

    const sead::Vector3f rot_spd = *mIgniteRotSpeed_s;
    sead::Vector3f ang_vel;
    ang_vel.x = m00 * rot_spd.x + m01 * rot_spd.y + m02 * rot_spd.z;
    ang_vel.y = m10 * rot_spd.x + m11 * rot_spd.y + m12 * rot_spd.z;
    ang_vel.z = m20 * rot_spd.x + m21 * rot_spd.y + m22 * rot_spd.z;

    const sead::Matrix34f& actor_mtx = mActor->getMtx();
    sead::Vector3f front{actor_mtx.m[0][2], actor_mtx.m[1][2], actor_mtx.m[2][2]};
    front.normalize();

    sub_71005DDF80(&vel, &target, &pos, &front, mDirMinAngle_s, mDirMaxAngle_s,
                   *mIgniteSpeed_s, 0.0f, 0.0f);

    auto* link = mIgniteActor_d;
    if (!link || !link->hasProc())
        return;

    sead::Matrix34f mtx;
    mtx.m[0][0] = m00 * (cy * cz) + m01 * (cy * sz) - m02 * sy;
    mtx.m[0][1] =
        m00 * (sx * sy * cz - cx * sz) + m01 * (sx * sy * sz + cx * cz) + m02 * (sx * cy);
    mtx.m[0][2] = m02 * (cx * cy) + m00 * (sx * sz + sy * cx * cz) +
                 m01 * (sy * sz * cx - sx * cz);
    mtx.m[1][0] = m10 * (cy * cz) + m11 * (cy * sz) - m12 * sy;
    mtx.m[1][1] =
        m10 * (sx * sy * cz - cx * sz) + m11 * (sx * sy * sz + cx * cz) + m12 * (sx * cy);
    mtx.m[1][2] = m12 * (cx * cy) + m10 * (sx * sz + sy * cx * cz) +
                 m11 * (sy * sz * cx - sx * cz);
    mtx.m[2][0] = m20 * (cy * cz) + m21 * (cy * sz) - m22 * sy;
    mtx.m[2][1] =
        m20 * (sx * sy * cz - cx * sz) + m21 * (sx * sy * sz + cx * cz) + m22 * (sx * cy);
    mtx.m[2][2] = m22 * (cx * cy) + m20 * (sx * sz + sy * cx * cz) +
                 m21 * (sy * sz * cx - sx * cz);

    ksys::act::ActorConstDataAccess access;
    ksys::act::acquireActor(link, &access);
    access.setThisActorAsChild(mActor, false);

    mtx.m[0][3] = pos.x;
    mtx.m[1][3] = pos.y;
    mtx.m[2][3] = pos.z;
    access.setProperties(mtx, &vel, &ang_vel, nullptr, false, 2, -1);
}

}  // namespace uking::action
