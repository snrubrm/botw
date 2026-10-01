#include "Game/AI/AI/aiTrolleyGrabbedByMagnet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

TrolleyGrabbedByMagnet::TrolleyGrabbedByMagnet(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyGrabbedByMagnet::~TrolleyGrabbedByMagnet() = default;

bool TrolleyGrabbedByMagnet::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrolleyGrabbedByMagnet::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody())
        body->setFrictionScale(0.0f);
    mFlags.set(Flag::Changeable);
}

void TrolleyGrabbedByMagnet::leave_() {
    if (auto* body = mActor->getMainBody())
        body->setFrictionScale(1.0f);
}

void TrolleyGrabbedByMagnet::loadParams_() {
    getDynamicParam(&mRailDist_d, "RailDist");
    getDynamicParam(&mRailPos_d, "RailPos");
    getDynamicParam(&mRailDir_d, "RailDir");
}

}  // namespace uking::ai
