#include "Game/AI/Action/actionRagdoll.h"
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71006ecc78.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

Ragdoll::Ragdoll(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Ragdoll::~Ragdoll() {
    _f8.release();
}

bool Ragdoll::init_(sead::Heap* heap) {
    _f8.acquire(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_f8._0)) {
        if (!(unit->_b0 & 1)) {
            unit->_8.setName("Skl_Root");
            unit->_8._68 = sead::Matrix34f::ident;
            unit->_b4 = 0;
            unit->_b0 |= 1;
        }
    }
    _f8.sub_7100137A28(heap, static_cast<Unk_71025afb58**>(mCRBOffsetUnit_a));
    _f8.x();
    return true;
}

void Ragdoll::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Ragdoll::leave_() {
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_f8.mSlot))
        unit->_8.sub_detach(mActor);
    if (auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (actor->_868)
            actor->_868->sub_71006EE2FC();
    }
    m39();
    if (auto* controller = mActor->getCharacterController()) {
        mCCAccessor.resetMotionType(controller);
        mCCAccessor.sub_710072AEEC(controller);
        controller->sub_7100F60604();
    }
}

void Ragdoll::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mInWaterDownTime_s, "InWaterDownTime");
    getStaticParam(&mForceFinishTime_s, "ForceFinishTime");
    getStaticParam(&mOnGroundDownTime_s, "OnGroundDownTime");
    getStaticParam(&mStartUpdateFriction_s, "StartUpdateFriction");
    getStaticParam(&mWeaponDropSpeedXZ_s, "WeaponDropSpeedXZ");
    getStaticParam(&mWeaponDropSpeedY_s, "WeaponDropSpeedY");
    getStaticParam(&mGetUpGroundAngle_s, "GetUpGroundAngle");
    getStaticParam(&mForceEndWaterDepth_s, "ForceEndWaterDepth");
    getStaticParam(&mIsWaitAS_s, "IsWaitAS");
    getStaticParam(&mIsItemDrop_s, "IsItemDrop");
    getStaticParam(&mIsCheckVibrate_s, "IsCheckVibrate");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPosBaseRagdollRbName_s, "PosBaseRagdollRbName");
    getStaticParam(&mStableASName_s, "StableASName");
    getStaticParam(&mDownBackCtrlOffset_s, "DownBackCtrlOffset");
    getStaticParam(&mDownFrontCtrlOffset_s, "DownFrontCtrlOffset");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void Ragdoll::calc_() {
    ksys::act::ai::Action::calc_();
}

// NON_MATCHING: the original re-reads pos.y from the stack after getAabbInWorld (ours keeps it in a callee-saved
// register)
bool Ragdoll::m34() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return true;
    if (!actor->_868)
        return false;
    if (!actor->_868->sub_71006EDF9C())
        return false;

    sead::Vector3f pos;
    actor->getMtx().getTranslation(pos);
    ksys::phys::RigidBody* body;
    if (auto* controller = actor->getCharacterController()) {
        body = controller->sub_7100F61A34();
    } else {
        body = actor->getMainBody();
        if (!body)
            return true;
    }
    f32 min_y;
    {
        sead::BoundBox3f aabb;
        body->getAabbInWorld(&aabb);
        min_y = aabb.getMin().y;
    }
    pos.y += 1.0f;
    sead::Vector3f to = pos;
    to.y = min_y - 1.5f;
    sead::Vector3f hit_pos;
    sead::Vector3f normal;
    if (!sub_710072E928(pos, to, &hit_pos, &normal, nullptr, 0.0f))
        return false;
    const f32 angle =
        std::atan2(normal.y, std::sqrt(normal.x * normal.x + normal.z * normal.z)) - sead::Mathf::pi() / 2;
    return sead::Mathf::abs(angle) < *mGetUpGroundAngle_s;
}

bool Ragdoll::m35() {
    if (_c0.z <= 0.0f || _cc.z <= 0.0f || _d8.z <= 0.0f)
        return true;
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (actor && actor->_868 && !actor->_868->sub_71006EE15C())
        return false;
    return true;
}

bool Ragdoll::m36() {
    if (m37() >= 1 && _c0.x < 0.0f)
        return true;
    return false;
}

void Ragdoll::m39() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F62CA8(true);
    }
}

s32 Ragdoll::m40() {
    return *mTime_s;
}

}  // namespace uking::action
