#include "Game/Actor/actNPCBase.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <gsys/gsysModel.h>

namespace uking::act {

NPCBase::NPCBase(const CreateArg& arg) : Actor(arg) {
    _1c0 = 2;
}

// NON_MATCHING: the original destructor only resets the vtables and calls Actor::~Actor (no member
// destructors)
NPCBase::~NPCBase() { ; }  // see GameDataFlagSelector::~GameDataFlagSelector() in upstream (commit 96101229)

bool NPCBase::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

void NPCBase::onPreDeleteStart_(PrepareArg& arg) {}

void NPCBase::preDelete2_(const PreDeleteArg& arg) {}

void NPCBase::initMaybe() {
    if (getModel()) {
        getModel()->setScale(getScale());
        getModel()->setMatrix(getMtx());
        getASList()->sub_710115BAF8("Root");
    }
    if (getPhysics())
        getPhysics()->setFlag2();
    if (auto* controller = getCharacterController()) {
        controller->sub_7100F60500(getMtx());
        auto direction = getMtx().getBase(2);
        direction.y = 0.0f;
        direction.normalize();
        controller->sub_7100F5EDBC(direction);
        controller->sub_7100F5EC30();
    }
    if (auto* nav = m45()) {
        ksys::phys::HavokAI::instance()->sub_7100F82BCC(nav);
        nav->sub_7100F765E8(getMtx().getTranslation());
        nav->sub_7100F76694(getMtx().getBase(2));
    }
}

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
