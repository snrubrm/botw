#include "Game/AI/AI/aiLynelTackleMove.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"

namespace uking::ai {

LynelTackleMove::LynelTackleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelTackleMove::~LynelTackleMove() = default;

bool LynelTackleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

bool LynelTackleMove::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool LynelTackleMove::isChangeable() const {
    return false;
}

void LynelTackleMove::leave_() {
    sub_710049BEC4();
}

void LynelTackleMove::loadParams_() {
    getStaticParam(&mThroughDist_s, "ThroughDist");
    getStaticParam(&mCloseEndAngle_s, "CloseEndAngle");
    getStaticParam(&mCloseEndDist_s, "CloseEndDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool LynelTackleMove::isFinished() const {
    return ActionBase::isFinished() || (isCurrentChild("通り過ぎ") && getCurrentChild()->isFinished());
}

void LynelTackleMove::sub_710049BEC4() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    }

    auto* body = mActor->getRigidBodyByName(ksys::act::getStr_Body().cstr());
    if (!body)
        return;
    for (int i = 0, n = body->getRigidBodies().size(); i < n; ++i) {
        if (auto* rigid_body = body->getRigidBody(i)) {
            rigid_body->disableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            rigid_body->disableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
    }
}

bool LynelTackleMove::handleMessage_(const ksys::Message& message) {
    if (message.getType().value == 0x3000003)
        sub_710049BEC4();
    else if (message.getType().value == 0x3000004)
        sub_710049B8F0();
    return false;
}

}  // namespace uking::ai
