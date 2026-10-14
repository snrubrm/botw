#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking {

// Name from the CSV (Message3DText::set, 0x71007219e8). Embedded in HiddenKorokRoot (_a8) and
// NpcTebaTrainingRoot (_238). 0x7100721830 fills the actor and the message label prefix
// ("EventFlowMsg/" / "ShoutMsg/Shout_" / per-actor); `set` looks the message up and starts the
// display timer.
class Message3DText {
public:
    Message3DText();
    ~Message3DText();

    // 0x71007219e8 (CSV name): like sub_7100721B1C, but only while `_c9`.
    void set(f32 time, const sead::SafeString& label);

    // 0x7100721830: sets the actor and the message label prefix ("EventFlowMsg/" or
    // "ShoutMsg/Shout_" + the actor's same-group name; hidden Koroks share "Npc_HiddenKorok").
    void sub_7100721830(ksys::act::Actor* actor, bool shout);
    // 0x7100721c48: per-frame update (timer; starts the display once it ran out).
    void sub_7100721C48();
    // 0x7100721b1c: looks the message up and, if found, starts the display timer and remembers the
    // label (same as `set` without the `_c9` check).
    void sub_7100721B1C(f32 time, const sead::SafeString& label);

    ksys::act::Actor* mActor = nullptr;
    sead::FixedSafeString<80> _8;
    sead::FixedSafeString<64> _70;
    bool _c8 = true;
    bool _c9 = true;
    ksys::Timer _cc;
};
KSYS_CHECK_SIZE_NX150(Message3DText, 0xd8);

}  // namespace uking
