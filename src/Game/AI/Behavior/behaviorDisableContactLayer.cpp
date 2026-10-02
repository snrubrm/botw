#include "Game/AI/Behavior/behaviorDisableContactLayer.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

DisableContactLayer::DisableContactLayer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
DisableContactLayer::~DisableContactLayer() {
    ;
}

void DisableContactLayer::m7() {}

// NON_MATCHING: the original computes &mIgnoreContactPoint_s before the first call (as in NeckControl)
void DisableContactLayer::loadParams() {
    getStaticParam(&mLayerNameToDisable_s, "LayerNameToDisable");
    getStaticParam(&mIgnoreContactPoint_s, "IgnoreContactPoint");
}

bool Unk_71024355e8::invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                            const ksys::phys::ContactPointInfo::Event& event) {
    if (event.body && int(event.body->getContactLayer()) == int(_8))
        return false;
    return true;
}

}  // namespace uking::behavior
