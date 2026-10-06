#include "Game/AI/Action/actionShutterOpenWait.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::action {

ShutterOpenWait::ShutterOpenWait(const InitArg& arg) : ActionEx(arg) {}

ShutterOpenWait::~ShutterOpenWait() = default;

bool ShutterOpenWait::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterOpenWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    switch (*mMoveAxis_m) {
    case 0:
        _40.set(sead::Vector3f::ex);
        break;
    case 1:
        _40.set(sead::Vector3f::ey);
        break;
    case 2:
        _40.set(sead::Vector3f::ez);
        break;
    }
    mFlags.set(Flag::Changeable);
}

void ShutterOpenWait::leave_() {
    ActionEx::leave_();
}

void ShutterOpenWait::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mMoveAxis_m, "MoveAxis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
}

void ShutterOpenWait::calc_() {
    if (auto* body = mActor->getMainBody()) {
        sead::Matrix34f mtx;
        mActor->getHomeMtx(&mtx);
        sead::Matrix34f offset;
        offset.makeT(_40 * *mMoveDis_m);
        mtx.setMul(mtx, offset);
        body->changePositionAndRotation(mtx, sead::Mathf::epsilon());
    }
}

}  // namespace uking::action
