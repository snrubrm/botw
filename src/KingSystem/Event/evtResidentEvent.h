#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class BaseProc;
}  // namespace ksys::act

namespace ksys::evt {

class EventFlow;

// Name from the CSV (evt::ResidentEvent::ctor 0x7100701858, dtor, initWithName, unloadEvent,
// initWithEvent_, callEvent, sendMessageToEventMgrActor, loadEvent; TU 0x7100701858-0x7100701be4 in
// the game code). An event that stays loaded (LastBoss, SiteBoss and a few AIs embed it). No vtable:
// it contains a BaseProcLinkForEvent at offset 0.
class ResidentEvent {
public:
    ResidentEvent();
    ~ResidentEvent();

    void initWithName(act::BaseProc* proc, const sead::SafeString& event_name,
                      const sead::SafeString& entry_point);
    void unloadEvent();
    void initWithEvent_(act::BaseProc* proc, const Metadata* metadata);
    bool callEvent(bool a1);
    bool sendMessageToEventMgrActor(act::Actor* actor);
    bool loadEvent();

    BaseProcLinkForEvent mLink;
    EventFlow* mEventFlow = nullptr;
    act::BaseProc* mProc = nullptr;
};
KSYS_CHECK_SIZE_NX150(ResidentEvent, 0x1d0);

}  // namespace ksys::evt
