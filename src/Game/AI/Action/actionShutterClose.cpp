#include "Game/AI/Action/actionShutterClose.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

ShutterClose::ShutterClose(const InitArg& arg) : ActionEx(arg) {}

ShutterClose::~ShutterClose() = default;

bool ShutterClose::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterClose::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    switch (*mMoveAxis_m) {
    case 0:
        _60.set(sead::Vector3f::ex);
        break;
    case 1:
        _60.set(sead::Vector3f::ey);
        break;
    case 2:
        _60.set(sead::Vector3f::ez);
        break;
    }
    _54.set(sead::Vector3f::zero);
    _48 = _60 * *mMoveDis_m + _54;
}

void ShutterClose::leave_() {
    ActionEx::leave_();
}

void ShutterClose::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mMoveAxis_m, "MoveAxis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mMoveSpeed_m, "MoveSpeed");
}

// NON_MATCHING: the loads of _48/_54 for the difference are scheduled differently (pre-indexed
// addressing instead of ldp pairs from this).
void ShutterClose::calc_() {
    auto* actor = mActor;
    const f32 step = *mMoveSpeed_m * ksys::VFR::instance()->getDeltaFrame();
    sead::Vector3f diff = _54;
    diff -= _48;
    const f32 len = diff.length();
    if (len <= step) {
        _48.set(_54);
        setFinished();
    } else {
        const f32 inv = 1.0f / len;
        const sead::Vector3f dir = diff * inv;
        _48 += dir * step;
    }
    sead::Matrix34f mtx;
    actor->getHomeMtx(&mtx);
    sead::Matrix34f offset;
    offset.makeT(_48);
    mtx.setMul(mtx, offset);
    if (auto* body = actor->getMainBody())
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
}

}  // namespace uking::action
