#include "Game/AI/Action/actionShutterOpen.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ShutterOpen::ShutterOpen(const InitArg& arg) : ActionEx(arg) {}

ShutterOpen::~ShutterOpen() = default;

bool ShutterOpen::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

// NON_MATCHING: the copy of _64 into _58 is a memory copy (ldr w + ldur x from this) in the
// original; set() addresses the source through a materialised pointer.
void ShutterOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    switch (*mMoveAxis_m) {
    case 0:
        _70.set(sead::Vector3f::ex);
        break;
    case 1:
        _70.set(sead::Vector3f::ey);
        break;
    case 2:
        _70.set(sead::Vector3f::ez);
        break;
    }
    _64 = _70 * *mMoveDis_m + sead::Vector3f::zero;
    if (*mIsPreOpen_s) {
        _58.set(_64);
        if (auto* body = actor->getMainBody()) {
            sead::Matrix34f home;
            mActor->getHomeMtx(&home);
            sead::Matrix34f offset;
            offset.makeT(_58);
            sead::Matrix34f mtx;
            mtx.setMul(home, offset);
            if (body->isAddedToWorld()) {
                actor->setMtx(mtx, false, true);
            } else {
                actor->setMtx(mtx, true, true);
                actor->nullsub_4648();
            }
        }
    } else {
        _58.set(sead::Vector3f::zero);
    }
    if (*mOnLink_s) {
        actor->emitBasicSigOn();
        actor->setRevivalFlagForUsed(true);
    }
}

void ShutterOpen::leave_() {
    ActionEx::leave_();
}

void ShutterOpen::loadParams_() {
    getStaticParam(&mOnLink_s, "OnLink");
    getStaticParam(&mIsPreOpen_s, "IsPreOpen");
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mMoveAxis_m, "MoveAxis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mMoveSpeed_m, "MoveSpeed");
}

// NON_MATCHING: the loads of _58/_64 for the difference are scheduled differently (see
// ShutterClose::calc_).
void ShutterOpen::calc_() {
    auto* actor = mActor;
    const f32 step = *mMoveSpeed_m * ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f diff = _64;
    diff -= _58;
    const f32 len = diff.length();
    if (len <= step) {
        _58.set(_64);
        setFinished();
    } else {
        const f32 inv = 1.0f / len;
        const sead::Vector3f dir = diff * inv;
        _58 += dir * step;
    }
    sead::Matrix34f home;
    actor->getHomeMtx(&home);
    sead::Matrix34f offset;
    offset.makeT(_58);
    sead::Matrix34f mtx;
    mtx.setMul(home, offset);
    if (auto* body = actor->getMainBody())
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
}

}  // namespace uking::action
