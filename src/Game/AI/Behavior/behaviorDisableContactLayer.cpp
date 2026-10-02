#include "Game/AI/Behavior/behaviorDisableContactLayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::behavior {

DisableContactLayer::DisableContactLayer(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops (SafeString member).
DisableContactLayer::~DisableContactLayer() {
    ;
}

// NON_MATCHING: ContactLayer::fromText (sead) builds a SafeString temporary per candidate and calls
// its virtual cstr() through memory; the original compares the name against text(i) with a single
// virtual call on the name and devirtualised access to the candidate
bool DisableContactLayer::m6(sead::Heap* heap) {
    ksys::phys::ContactLayer layer(int(_40._10));
    const bool found = layer.fromText(mLayerNameToDisable_s);
    _40._10 = layer;
    _40._8 = layer;
    return found;
}

void DisableContactLayer::m7() {}

void DisableContactLayer::m8() {
    if (auto* cc = mActor->getCharacterController()) {
        cc->enableContactLayer(ksys::phys::ContactLayer(_40._10));
        if (*mIgnoreContactPoint_s) {
            if (auto* info = cc->sub_7100F635D8())
                info->setContactCallback(&_40);
        }
    } else if (auto* body = mActor->getMainBody()) {
        body->enableContactLayer(ksys::phys::ContactLayer(_40._10));
        if (*mIgnoreContactPoint_s) {
            if (auto* info = body->getContactPointInfo())
                info->setContactCallback(&_40);
        }
    }
}

void DisableContactLayer::m9() {
    if (auto* cc = mActor->getCharacterController()) {
        cc->disableContactLayer(ksys::phys::ContactLayer(_40._10));
        if (*mIgnoreContactPoint_s) {
            if (auto* info = cc->sub_7100F635D8())
                info->setContactCallback(nullptr);
        }
    } else if (auto* body = mActor->getMainBody()) {
        body->disableContactLayer(ksys::phys::ContactLayer(_40._10));
        if (*mIgnoreContactPoint_s) {
            if (auto* info = body->getContactPointInfo())
                info->setContactCallback(nullptr);
        }
    }
}

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
