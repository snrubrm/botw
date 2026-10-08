#include "Game/AI/Action/actionIgniteThreeActorAttack.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::action {

IgniteThreeActorAttack::IgniteThreeActorAttack(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteThreeActorAttack::~IgniteThreeActorAttack() = default;

void IgniteThreeActorAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
    _90 = 0;
}

void IgniteThreeActorAttack::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteThreeActorAttack::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getDynamicParam(&mIgniteHandle2_d, "IgniteHandle2");
    getDynamicParam(&mIgniteHandle3_d, "IgniteHandle3");
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mBaseNode_s, "BaseNode");
}

void IgniteThreeActorAttack::calc_() {
    OnetimeStopASPlay::calc_();
    if (auto* as_list = mActor->getASList()) {
        if (as_list->x(71, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true)) {
            sub_71001B6AB8();
            _90 = _90 + 1;
        }
    }
}

// NON_MATCHING: register allocation, spill slots and product/scheduling order only; all
// calls, values and control flow match. Remaining diffs: base-element spill grouping, the
// _90 switch tests ==0 first (ours) vs ==2 first (original), and rot-row store scheduling.
void IgniteThreeActorAttack::sub_71001B6AB8() {    auto* actor = mActor;
    if (!actor)
        return;
    auto* model = actor->getModel();
    if (!model)
        return;
    sead::Matrix34f base_mtx;
    gsys::BoneAccessKey key;
    if (*mBaseNode_s.getStringTop() != sead::SafeString::cNullChar)
        key = model->searchBone(mBaseNode_s);
    if (key.isValid()) {
        model->getUnits()
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

    sead::Vector3f vel{base_mtx.m[0][0], base_mtx.m[1][0], base_mtx.m[2][0]};
    vel.normalize();
    vel *= *mIgniteSpeed_s;

    const sead::Vector3f rot_spd = *mIgniteRotSpeed_s;
    sead::Vector3f ang_vel;
    ang_vel.x = m00 * rot_spd.x + m01 * rot_spd.y + m02 * rot_spd.z;
    ang_vel.y = m10 * rot_spd.x + m11 * rot_spd.y + m12 * rot_spd.z;
    ang_vel.z = m20 * rot_spd.x + m21 * rot_spd.y + m22 * rot_spd.z;

    ksys::act::BaseProcHandle** handle;
    if (_90 == 2) {
        handle = mIgniteHandle3_d;
    } else if (_90 == 1) {
        handle = mIgniteHandle2_d;
    } else if (_90 == 0) {
        handle = mIgniteHandle_d;
    } else {
        return;
    }
    if (handle && *handle)
        sub_71005DFAE0(*handle, actor, &pos, &rot_mtx, &vel, &ang_vel);
}

}  // namespace uking::action
