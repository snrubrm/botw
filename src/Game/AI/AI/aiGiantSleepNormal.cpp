#include "Game/AI/AI/aiGiantSleepNormal.h"
#include "Game/Actor/actGiantEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

bool sub_7100739D74(ksys::act::Actor* actor, ksys::act::BaseProcLink* link);

namespace uking::ai {

GiantSleepNormal::GiantSleepNormal(const InitArg& arg) : SpecialEnemySleep(arg) {}

// The original keeps the vtable store that a defaulted destructor drops (same form as upstream's
// GameDataFlagSelector::~GameDataFlagSelector() { ; }, commit 96101229).
GiantSleepNormal::~GiantSleepNormal() {
    ;
}

bool GiantSleepNormal::init_(sead::Heap* heap) {
    if (!SpecialEnemySleep::init_(heap))
        return false;
    _78 = mActor->findPhysicsBodyByName(ksys::act::getStr_Body().cstr(), mAwakeRbName_s.cstr());
    return true;
}

void GiantSleepNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    SpecialEnemySleep::enter_(params);
    _98 = 0;
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor)) {
        giant->_1568 = 1;
        giant->_a68 &= ~1;
    }
    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.set(0xc00);
    mActor->getMtx().getTranslation(_8c);
}

void GiantSleepNormal::leave_() {
    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.reset(0xc00);
    if (auto* giant = sead::DynamicCast<act::GiantEnemy>(mActor)) {
        giant->_1568 = false;
        giant->_a68 |= 1;
    }
    if (!sub_71005D8F28(mActor)) {
        auto* manager = sead::DynamicCast<dmg::DamageManager>(mActor->getDamageMgr());
        if (manager && manager->getField54() != -1) {
            auto* actor = mActor;
            if (sub_7100739D74(actor, manager->getAttacker())) {
                auto* current_actor = mActor;
                sub_71005D8DE8(current_actor, *manager->getAttacker(), nullptr, nullptr);
                mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
                mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_1000000);
            }
        }
    }
    SpecialEnemySleep::leave_();
}

void GiantSleepNormal::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getStaticParam(&mForceAwakeDist_s, "ForceAwakeDist");
    getStaticParam(&mAwakeRbName_s, "AwakeRbName");
}

void GiantSleepNormal::m34() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7E9BC(0);
    SpecialEnemySleep::m34();
}

void GiantSleepNormal::m35() {
    if (auto* awareness = mActor->getAwareness())
        awareness->sub_7100D7E9BC(0);
    ksys::act::ai::InlineParamPack params;
    params.addVec3(_80, "TargetPos", -1);
    changeChild("待機", &params);
}

void GiantSleepNormal::m38(int x, ksys::act::Unk_7100d78e50* entry) {
    _80 = entry->_88;
    _98 = 1;
}

bool GiantSleepNormal::m36() {
    return _98 - 2 < 3;
}

}  // namespace uking::ai
