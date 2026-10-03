#pragma once

#include <prim/seadSafeString.h>

namespace ksys::act {
class Actor;
}

// Unnamed free helpers of the actor utility area at 0x7100728f14-0x71007292a0 (Swarm actors: they walk the
// per-member ASLists at Swarm+0x14d8). Placeholder names; declared only.

// 0x71007292a0: if `actor` is a Swarm (RTTI 0x7102 5b08b8), forwards to 0x7100728f14 (`as_name` is looked up
// in the members' AS lists; the four booleans are passed through; parameter meaning unknown).
void sub_71007292A0(ksys::act::Actor* actor, const sead::SafeString& as_name, bool a3, bool a4,
                    bool a5, bool a6);
