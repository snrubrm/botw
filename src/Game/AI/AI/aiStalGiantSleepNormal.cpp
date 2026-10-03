#include "Game/AI/AI/aiStalGiantSleepNormal.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actGiantEnemy.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

StalGiantSleepNormal::StalGiantSleepNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalGiantSleepNormal::~StalGiantSleepNormal() = default;

bool StalGiantSleepNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalGiantSleepNormal::sub_71005A5464() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        _b0 = enemy->_e90;
        enemy->_e90 = 1;
    }
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(actor))
        giant->_1568 = 1;
    if (auto* controller = actor->getCharacterController()) {
        controller->enableContactLayer(ksys::phys::ContactLayer(3));
        controller->enableContactLayer(ksys::phys::ContactLayer(0));
        controller->enableContactLayer(ksys::phys::ContactLayer(4));
        controller->enableContactLayer(ksys::phys::ContactLayer(13));
        controller->enableContactLayer(ksys::phys::ContactLayer(5));
        controller->enableContactLayer(ksys::phys::ContactLayer(1));
    }
    ksys::act::disableAllAttClients(actor);
    sub_71007A397C(actor);
    sub_71006F5940(actor->getChemicalStuff());
    if (auto* unit = actor->get548())
        unit->_18._50 = true;
}

void StalGiantSleepNormal::sub_71005A5E58() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        enemy->_e90 = _b0;
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(actor))
        giant->_1568 = 0;
    if (auto* controller = actor->getCharacterController())
        controller->sub_7100F60604();
    ksys::act::enableAllAttClients(actor);
    sub_71007A3800(actor);
    sub_71006F5A80(actor->getChemicalStuff());
    if (auto* unit = actor->get548())
        unit->_18._50 = false;
}

void StalGiantSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71005A5464();
    _c0 = ksys::Timer(*mAwakeDelayTime_s, *mAwakeDelayTime_s);
    _b6 = false;
    if (auto* awareness = mActor->getAwareness()) {
        _b4 = awareness->sub_7100D7E964();
        _b5 = awareness->_260[0] && awareness->_260[0]->_50;
        awareness->enable();
    }

    if (mActor->getRootAi()->getI() == 5) {
        sub_710073DE08(mActor);
        changeChild("崩れる");
    } else {
        if (auto* awareness = mActor->getAwareness()) {
            awareness->sub_7100D7EAE4(0);
            awareness->sub_7100D7EAE4(2);
            if (!*mIsAwakenByHearing_s)
                awareness->sub_7100D7EAE4(1);
        }
        sub_710073DE08(mActor);
        changeChild("崩れ待機");
    }
}

void StalGiantSleepNormal::leave_() {
    if (auto* awareness = mActor->getAwareness()) {
        if (_b4) {
            awareness->sub_7100D7E9BC(0);
        } else {
            awareness->sub_7100D7EBE0(1.0f);
            awareness->disable();
        }
    }
    sub_71005A5E58();
    sub_710073DE44(mActor);
}

void StalGiantSleepNormal::loadParams_() {
    getStaticParam(&mAwakeDelayTime_s, "AwakeDelayTime");
    getStaticParam(&mIsAwakenByHearing_s, "IsAwakenByHearing");
    getStaticParam(&mIsWaitAfterAwaken_s, "IsWaitAfterAwaken");
}

bool StalGiantSleepNormal::isChangeable() const {
    return isCurrentChild("待機");
}

bool StalGiantSleepNormal::handleMessage_(const ksys::Message* message) {
    if (isCurrentChild("退散") || _60._30)
        return false;
    return _60.m2(*message);
}

}  // namespace uking::ai

// Defined in this TU in the original (inlined into StalGiantSleepNormal::handleMessage_).
bool Unk_7102424730::m2(const ksys::Message& message) {
    if (message.getType() != 0x80000b8)
        return false;

    auto* payload = static_cast<Unk_71023c5480_Payload*>(message.getUserData());
    if (!payload)
        return false;

    payload->x(&_38.mLink);
    _30 = true;
    _18 = message.getSource();
    return true;
}

