#include "Game/AI/Behavior/behaviorPosControl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/VFR.h"

namespace uking::behavior {

PosControl::PosControl(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

PosControl::~PosControl() = default;

bool PosControl::m6(sead::Heap* heap) {
    return true;
}

void PosControl::m8() {}

void PosControl::m9() {}

void PosControl::loadParams() {
    getStaticParam(&mImpulse_s, "Impulse");
}

// NON_MATCHING: scheduling (the original loads the impulse param before the matrix elements)
void PosControl::m7() {
    auto* body = mActor->getMainBody();
    if (!body)
        return;
    sead::Matrix34f mtx;
    mActor->getHomeMtx(&mtx);
    sead::Vector3f impulse;
    impulse.setRotated(mtx, {0, *mImpulse_s, 0});
    impulse *= ksys::VFR::instance()->getDeltaFrame();
    impulse *= body->getTimeFactor();
    body->applyLinearImpulse(impulse);
}

}  // namespace uking::behavior
