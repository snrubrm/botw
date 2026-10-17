#include "Game/Actor/actNPCBase.h"
#include "KingSystem/Mii/miiNetfp.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include <gsys/gsysModel.h>

namespace uking::act {

bool NPC::isZora_(ksys::act::Actor* actor) {
    return actor && actor->getUMii() &&
           *actor->getUMii()->getBody().race == ksys::mii::UMii::Body::Race_Zora;
}

ksys::act::BaseProc* NPCBase::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) NPCBase(arg);
}

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

// 0x71000217f8 (placeholder name): fades the NPC's UMii hat / hair opacities (`rate` is the model opacity).
// NON_MATCHING: our compiler stores each of the two hat opacities as it computes it; the original keeps both in
// registers and stores them with one stp.
// In actNPCBase.cpp (not actNPC.cpp) because m61 has to keep tail-calling it: in the NPC TU our compiler
// inlines the definition into m61, but the original m61 is a 4-byte tail call.
void NPC::sub_71000217F8(f32 rate) {
    auto* umii = getUMii();
    if (!umii)
        return;

    {
        const f32 value = _1074[2];
        const f32 opacity = value * rate;
        const f32 opacity2 = (1.0f - value) * rate;
        ksys::mii::sub_7100F5C128(mModel, *umii, &opacity, &opacity2);
    }

    auto* model = mModel;
    auto* as_list = sub_71011C9A88();
    {
        const f32 opacity = _1074[0] * rate;
        ksys::mii::sub_7100F5BC74(model, as_list, *umii, &opacity);
    }
    {
        const f32 opacity = _1074[1] * rate;
        ksys::mii::sub_7100F5BFE4(model, *umii, &opacity);
    }
}

}  // namespace uking::act
