#include "Game/AI/Action/actionRagdoll.h"
#include <algorithm>
#include <cfloat>
#include <cmath>
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiUnk_710073fa90.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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
    setupCRBOffsetUnit(_f8);
    return true;
}

void Ragdoll::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        mCCAccessor.sub_710072AD1C(controller);
        mCCAccessor._4.setDirect(0xc);
        mCCAccessor.sub_710072AE20(controller);
        controller->mFlags.reset(8);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC_NoHitPlayer);
    }
    _f4 = 1.0f;
    if (*mStartUpdateFriction_s >= 0)
        _c4 = *mStartUpdateFriction_s;
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_f8._0))
        unit->_8.sub_attach(mActor);
    sub_7100226488();
}

void Ragdoll::sub_7100226488() {
    m38();
    auto* actor = mActor;
    const auto& mtx = actor->getMtx();
    _f0 = sead::Mathf::rad2deg(
        std::atan2(mtx(1, 2), sead::Mathf::sqrt(mtx(0, 2) * mtx(0, 2) + mtx(2, 2) * mtx(2, 2))));
    actor->getASList()->x_6(9, 0, _f0);
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    _c0 = m37();
    {
        const s32 time = *mInWaterDownTime_s;
        _cc = time;
        _d0 = time;
        _c8 = time;
    }
    {
        const s32 time = *mOnGroundDownTime_s;
        _d8 = time;
        _dc = time;
        _d4 = time;
    }
    {
        const s32 time = *mOnGroundDownTime_s;
        _e4 = time;
        _e8 = time;
        _ec = 0;
        _e0 = time;
    }
}

void Ragdoll::leave_() {
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_f8._0))
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

void Ragdoll::sub_7100226A30() {
    if (!mStableASName_s.isEmpty())
        playAS(mStableASName_s.cstr(), false, 0, 0, -1.0f);
    if (*mIsWaitAS_s)
        sub_71011C24DC(0, 0);
    const s32 time = m40();
    _c0 = time;
    if (time >= 0) {
        _ec = 1;
        return;
    }
    if (*mIsWaitAS_s && !isFinishedAS(0, 0)) {
        _ec = 1;
        return;
    }
    setFinished();
}

void Ragdoll::sub_7100226B04() {
    if (!mActor->getCharacterController())
        return;
    const f32 back = mDownBackCtrlOffset_s->length();
    const f32 front = mDownFrontCtrlOffset_s->length();
    const f32 max_length = sead::Mathf::max(back, front);
    if (auto* unit = sead::DynamicCast<Unk_7102384718>(*_f8._0)) {
        auto* handle = &unit->_8.mHandle;
        if (_f0 > -180.0f && _f0 < 0.0f) {
            sub_7100744A54(handle, *mDownBackCtrlOffset_s, 1.0f, max_length + max_length,
                           max_length);
        } else {
            sub_7100744A54(handle, *mDownFrontCtrlOffset_s, 1.0f, max_length + max_length,
                           max_length);
        }
    }
}

void Ragdoll::sub_7100227134() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F60AE0();
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
        controller->sub_7100F62CA8(false);
    }
}

// NON_MATCHING: the original stores out->x = 0 before computing the address of out->y (scheduling only)
void Ragdoll::sub_7100227278(sead::Vector3f* out) {
    auto* actor = mActor;
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor)) {
        const f32 speed = *mWeaponDropSpeedXZ_s;
        if (!(speed <= FLT_EPSILON && speed >= -FLT_EPSILON)) {
            dynamic_actor->sub_71006DD908(out);
            out->y = 0.0f;
            const f32 xz_speed = *mWeaponDropSpeedXZ_s;
            const f32 length = out->length();
            if (length > 0.0f)
                *out *= xz_speed / length;
            out->y = *mWeaponDropSpeedY_s;
            return;
        }
    }
    out->x = 0.0f;
    out->z = 0.0f;
    out->y = *mWeaponDropSpeedY_s;
}

// NON_MATCHING: only the block layout of the failure returns: the original branches from every NaN check
// (and the failed casts) to one shared `mov w0, wzr`, we duplicate it per check
bool Ragdoll::m32() {
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (!actor)
        return false;
    if (actor->_868)
        actor->_868->sub_71006EE1F8(mPosBaseRagdollRbName_s);
    auto* controller = actor->getCharacterController();
    if (!controller)
        return true;

    sead::Matrix34f mtx;
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor)) {
        if (dynamic_actor->_868)
            dynamic_actor->_868->sub_71006EDE54(&mtx, mPosBaseRagdollRbName_s);
    } else {
        mtx = sead::Matrix34f(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0);
    }
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 4; ++col) {
            if (sead::Mathf::isNan(mtx(row, col)))
                return false;
        }
    }
    sead::Vector3f linear_velocity;
    sead::Vector3f angular_velocity;
    controller->sub_7100F5FBC8(&linear_velocity, &angular_velocity, mtx);
    controller->sub_7100F5F6FC(linear_velocity);
    f32 length = angular_velocity.normalize();
    if (length > 0.0f) {
        length = std::min(length, sead::Mathf::pi() * 3);
        controller->sub_7100F5FB24(angular_velocity * length);
    }
    return true;
}

bool Ragdoll::m35() {
    if (_c8 <= 0.0f || _d4 <= 0.0f || _e0 <= 0.0f)
        return true;
    auto* actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor);
    if (actor && actor->_868 && !actor->_868->sub_71006EE15C())
        return false;
    return true;
}

bool Ragdoll::m36() {
    if (m37() >= 1 && _c0 < 0.0f)
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
