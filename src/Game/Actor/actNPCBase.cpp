#include "Game/Actor/actNPCBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

// NON_MATCHING: the original destructor only resets the vtables and calls Actor::~Actor (no member
// destructors)
NPCBase::~NPCBase() { ; }  // see GameDataFlagSelector::~GameDataFlagSelector() in upstream (commit 96101229)

bool NPCBase::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

void NPCBase::onPreDeleteStart_(PrepareArg& arg) {}

void NPCBase::preDelete2_(const PreDeleteArg& arg) {}

void NPCBase::calcMaybe() {}

void NPCBase::updatePositionMaybe() {}

void NPCBase::m66() {}

void NPCBase::m63() {
    getASList()->sub_710115BAF8("Root");
    if (getPhysics()) {
        if (auto* body = getPhysics()->findX("Tgt", "Body"))
            body->addToWorld();
        if (auto* body = getPhysics()->findX("Body", "Body"))
            body->addToWorld();
    }
}

void NPCBase::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    if (mActorFlags2.isOn(ActorFlag2::_200))
        ksys::act::sub_7100EE9B68(this, setter);
}

}  // namespace uking::act
