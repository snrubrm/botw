#include "Game/AI/Action/actionShutterCloseWait.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ShutterCloseWait::ShutterCloseWait(const InitArg& arg) : ActionEx(arg) {}

ShutterCloseWait::~ShutterCloseWait() = default;

bool ShutterCloseWait::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterCloseWait::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    mFlags.set(Flag::Changeable);
}

void ShutterCloseWait::leave_() {
    ActionEx::leave_();
}

void ShutterCloseWait::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void ShutterCloseWait::calc_() {
    if (auto* body = mActor->getMainBody()) {
        sead::Matrix34f mtx;
        mActor->getHomeMtx(&mtx);
        body->changePositionAndRotation(mtx);
    }
}

}  // namespace uking::action
