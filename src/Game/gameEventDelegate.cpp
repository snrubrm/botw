#include "Game/gameEventDelegate.h"
#include <math/seadMathCalcCommon.h>
#include "Game/gameRumble.h"
#include "Game/gameSceneMgr.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/Event/evtAction.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtQuery.h"
#include "KingSystem/Event/evtS7.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking {

// 0x71008ac51c
ksys::evt::S5* EventDelegate::makeS5(sead::Heap* heap) {
    return new (heap, 8) ksys::evt::S5;
}

// 0x71008ac54c
ksys::evt::EventFlowHandle* EventDelegate::makeS7(const ksys::evt::EventFlowCreateArg* arg,
                                                  ksys::evt::EventFlowBase* flow) {
    if (arg->_28 || arg->_38)
        return new (arg->heap, 8) ksys::evt::S7Movie(arg->heap, flow);
    return new (arg->heap, 8) ksys::evt::S7EventFlow(arg->heap, flow);
}

// 0x71008ac5cc
ksys::evt::Actor* EventDelegate::makeActor(ksys::evt::ActorBinding* binding, ksys::evt::EventActorSet* set,
                                           sead::Heap* heap) {
    return new (heap, 8) ksys::evt::Actor(binding, set, heap);
}

// 0x71008ac620
ksys::evt::Action* EventDelegate::makeAction(const evfl::ResAction* res, ksys::evt::ActorBase* actor,
                                             sead::Heap* heap) {
    return new (heap, 8) ksys::evt::Action(res, actor);
}

// 0x71008ac66c
ksys::evt::Query* EventDelegate::makeQuery(const evfl::ResQuery* res, ksys::evt::ActorBase* actor,
                                           sead::Heap* heap) {
    return new (heap, 8) ksys::evt::Query(res, actor);
}

// NON_MATCHING: same instructions, but the original keeps a separate `orr w0, wzr, #1; b epilogue` per `return true` path
// and places the epilogue right after the first `return false`; ours shares one `orr` and puts the epilogue last.
// 0x71008ac6b8
bool EventDelegate::canStartEventEvenInAir(const ksys::evt::BaseProcLinkForEvent& link) {
    const sead::SafeString event = link.mMetadata.getEventName().cstr();
    if (event.isEmpty())
        return false;
    const sead::SafeString entry = link.mMetadata.getEntryPointName().cstr();

    if (event == "SDemo_E-6" && entry == "FirstTouchdown") {
        auto* info = ksys::act::PlayerInfo::instance();
        if (!info)
            return false;
        auto* player = info->getPlayer();
        if (!player)
            return false;
        return player->_cfc.isOnBit(0);
    }

    if (event == "Demo018_0" && entry == "Demo018_0") {
        if (ksys::gdt::getBoolByKey("Wind_Relic_Rescued", false))
            return false;
    }

    return true;
}

// 0x71008ac878
bool EventDelegate::m6(sead::Matrix34f* out, const sead::SafeString& stage, const sead::SafeString& pos_name) {
    SceneMgr::instance()->setStageName(stage);
    sead::Vector3f result[2];
    const bool found = SceneMgr::instance()->getMapPosition(pos_name, result, SceneMgr::instance()->mStageName, nullptr);
    if (found) {
        const sead::Vector3f rotation = result[1] * (1.0f / 180.0f) * sead::Mathf::pi();
        out->makeRT(rotation, result[0]);
    }
    return found;
}

// 0x71008acb88
void EventDelegate::m8(s32 value, s32 count) {
    if (auto* rumble = Rumble::instance()) {
        if (value >= 0)
            rumble->sub_7100897FE4(value, count);
        else
            rumble->sub_710089878C();
    }
}

}  // namespace uking
