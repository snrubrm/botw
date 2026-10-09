#include "Game/AI/AI/aiNPCTravelBase.h"
#include "Game/AI/aiUnk_71007130BC.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/Actor/actNPC.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actSchedule.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

NPCTravelBase::NPCTravelBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCTravelBase::~NPCTravelBase() = default;

bool NPCTravelBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCTravelBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _68 = ksys::Timer(16, 16);
}

void NPCTravelBase::calc_() {
    if (_68.value <= sead::Mathf::epsilon())
        return;
    _68.update();
}

void NPCTravelBase::leave_() {
    if (_68.value <= sead::Mathf::epsilon())
        mActor->setFlag(ksys::act::Actor::ActorFlag::_34, false);
}

void NPCTravelBase::loadParams_() {}

// 0x71004dfb9c: send this actor's link to the selected awareness entry.
// NON_MATCHING: actor load timing, awareness-link address scheduling and return register differ.
bool NPCTravelBase::sub_71004DFB9C() {
    auto* entry = sub_71004DFA90();
    if (!entry)
        return false;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_38._18.mLock);
        _38._18.mLink.acquire(mActor, false);
    }
    _38.sub_710070DCC0(&entry->_0.mLink, true);
    return true;
}

// 0x71004dfa0c
void NPCTravelBase::sub_71004DFA0C(bool crouching) {
    const sead::SafeString name = crouching ? "Crouching" : "Standing";
    auto* cc = mActor->getCharacterController();
    auto* physics = mActor->getPhysics();
    if (cc && physics) {
        const s32 idx = physics->sub_7100FBE7F0(name);
        if (idx >= 0)
            cc->sub_7100F5F270(idx);
    }
}

// 0x71004df78c
void NPCTravelBase::sub_71004DF78C() {
    if (auto* schedule = mActor->getSchedule()) {
        mActor->getASList()->goLimpFromHeadShotMaybe(0x37, schedule->_248, 0);
        mActor->getASList()->goLimpFromHeadShotMaybe(0x38, schedule->_248, 0);
    }
}

// 0x71004df7ec
// NON_MATCHING: the original keeps a branch on `a2` (a direct load of _1a8) and only selects between _1a0 / _1a4 by address;
// ours folds the three loads into selects (everything else matches, including the switch)
void NPCTravelBase::sub_71004DF7EC(bool a1, bool a2) {
    auto* npc = sead::DynamicCast<act::NPC>(mActor);
    auto* schedule = mActor->getSchedule();
    if (!npc || !schedule)
        return;
    sub_71005D7518(mActor, true);
    npc->_fe8 &= ~0x100;
    npc->_1050 = true;
    auto* awareness = mActor->getAwareness();
    if (awareness)
        awareness->sub_7100D7E9BC(2);
    const s32 value = a2 ? schedule->_1a8 : (a1 ? schedule->_1a0 : schedule->_1a4);
    switch (value) {
    case 1:
        npc->_1050 = false;
        break;
    case 2:
        sub_71005D7518(mActor, false);
        npc->_1050 = false;
        if (awareness)
            awareness->sub_7100D7EAE4(2);
        break;
    case 5:
        npc->_fe8 &= ~0x80;
        if (awareness)
            awareness->sub_7100D7EAE4(2);
        break;
    case 6:
        npc->_1050 = false;
        [[fallthrough]];
    case 3:
        npc->_fe8 |= 0x100;
        break;
    default:
        break;
    }
    npc->_1070 = value;
}

// 0x71004df978
// NON_MATCHING: same select-vs-branch difference as sub_71004DF7EC (the original branches on `a2`)
void NPCTravelBase::sub_71004DF978(bool a1, bool a2) {
    auto* schedule = mActor->getSchedule();
    if (!schedule)
        return;
    sead::SafeString name;
    const s32 idx = a2 ? schedule->_1b8 : (a1 ? schedule->_1b0 : schedule->_1b4);
    name = sub_710071300C(idx);
    mActor->getASList()->goLimpFromHeadShotMaybe(0x3b, name, 0);
}

}  // namespace uking::ai
