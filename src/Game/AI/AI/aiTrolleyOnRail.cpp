#include "Game/AI/AI/aiTrolleyOnRail.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "Game/AI/aiXlinkHandle.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::ai {

TrolleyOnRail::TrolleyOnRail(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyOnRail::~TrolleyOnRail() = default;

bool TrolleyOnRail::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrolleyOnRail::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* body = mActor->getMainBody()) {
        body->setGravityFactor(1.0f);
        body->setContactLayerAndGroundHitAndHandler(body->getContactLayer(),
                                                    ksys::phys::GroundHit::MovingTrolley,
                                                    sub_710072E804(mActor, 0));
    }
    mFlags.set(Flag::Changeable);
    _68 = 0;
    _6c = 0;
}

void TrolleyOnRail::leave_() {
    xlink::fade(_58, -1);
    if (auto* body = mActor->getMainBody()) {
        body->setGravityFactor(1.0f);
        body->setContactLayerAndGroundHitAndHandler(body->getContactLayer(),
                                                    ksys::phys::GroundHit::HitAll,
                                                    sub_710072E804(mActor, 0));
    }
}

void TrolleyOnRail::loadParams_() {
    getDynamicParam(&mRailDist_d, "RailDist");
    getDynamicParam(&mVelocityReduce_d, "VelocityReduce");
    getDynamicParam(&mRailPos_d, "RailPos");
    getDynamicParam(&mRailDir_d, "RailDir");
}

}  // namespace uking::ai
