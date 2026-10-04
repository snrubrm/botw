#pragma once

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

// Partial declaration: CSV abbreviates the name as evt::EventSystem.
// Namespace inferred from the existing Manager/ActorFactory convention.
// No instance layout or construction is modeled here.
class EventSystem {
public:
    // Original instance pointer 0x71025d0c50 (GOT 0x710257b878).
    static EventSystem* instance() { return sInstance; }
    static EventSystem* sInstance;

    // 0x71008abf48: declaration-only speaker assignment.
    bool setSpeaker(act::Actor* actor);
};

}  // namespace ksys::evt
