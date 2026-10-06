#include "Game/AI/Action/actionStalEnemyHideWait.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

StalEnemyHideWait::StalEnemyHideWait(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

StalEnemyHideWait::~StalEnemyHideWait() = default;

bool StalEnemyHideWait::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void StalEnemyHideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    ksys::act::disableAllAttClients(actor);
    if (controller) {
        controller->mFlags.set(0x400);
        controller->sub_7100F636B0(false);
        controller->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        controller->sub_7100F62BB0();
    }
    playAS(mASName_s.cstr(), true, 0, 0, -1.0f);
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        dynamic_actor->_a68 &= ~1;
    mFlags.set(Flag::Changeable);
}

void StalEnemyHideWait::leave_() {
    ActionWithPosAngReduce::leave_();
    auto* actor = mActor;
    auto* controller = actor->getCharacterController();
    ksys::act::enableAllAttClients(actor);
    if (controller) {
        controller->mFlags.reset(0x400);
        controller->sub_7100F636B0(true);
        controller->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        controller->sub_7100F62BB8();
    }
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(mActor))
        dynamic_actor->_a68 |= 1;
}

void StalEnemyHideWait::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void StalEnemyHideWait::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
