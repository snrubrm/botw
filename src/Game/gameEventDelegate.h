#pragma once

#include "KingSystem/Event/evtManagerDelegate.h"

namespace uking {

// CSV ukingEventMgr (vtable 0x710246ca38, no RTTI, no destructor): the game's implementation of the event manager's
// delegate.
class EventDelegate final : public ksys::evt::ManagerDelegate {
public:
    // 0x71008ac51c (CSV ukingEventMgr::makeS5)
    ksys::evt::S5* makeS5(sead::Heap* heap) override;
    // 0x71008ac54c (CSV ukingEventMgr::makeS7): movie flows get the S7Movie handle
    ksys::evt::EventFlowHandle* makeS7(const ksys::evt::EventFlowCreateArg* arg, ksys::evt::EventFlowBase* flow) override;
    // 0x71008ac5cc / 0x71008ac620 / 0x71008ac66c (CSV ukingEventMgr::makeActor / makeAction / makeQuery)
    ksys::evt::Actor* makeActor(ksys::evt::ActorBinding* binding, ksys::evt::EventActorSet* set, sead::Heap* heap) override;
    ksys::evt::Action* makeAction(const evfl::ResAction* res, ksys::evt::ActorBase* actor, sead::Heap* heap) override;
    ksys::evt::Query* makeQuery(const evfl::ResQuery* res, ksys::evt::ActorBase* actor, sead::Heap* heap) override;
    // 0x71008ac6b8 (CSV ukingEventMgr::canStartEventEvenInAir)
    bool canStartEventEvenInAir(const ksys::evt::BaseProcLinkForEvent& link) override;
    // 0x71008ac878 (CSV ukingEventMgr::m6_stage_pos_stuff): sets the stage name, then looks the map position `pos_name`
    // up and builds the matrix of its position and rotation
    bool m6(sead::Matrix34f* out, const sead::SafeString& stage, const sead::SafeString& pos_name) override;
    // 0x71008ac9e4 (CSV ukingEventMgr::m7_fade_demo_stuff; not decompiled)
    void m7() override;
    // 0x71008acb88 (CSV ukingEventMgr::m8_rumble_stuff): starts the rumble pattern `value` (negative: stops the rumble)
    void m8(s32 value, s32 count) override;
};

}  // namespace uking
