#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class BaseProc;
}  // namespace ksys::act

namespace uking::act {

// Sub-object of Enemy (at 0xd70) and of NPC (at 0xe90). Placeholder name after its method
// 0x71002dccbc (bool (u16 mask): no linked actor in calc state has a matching flag).
class Unk_71002dccbc {
public:
    struct Entry {
        ksys::act::BaseProcLink link;
        u16 flags = 0;
        u8 _12 = 0;
    };

    // Methods (other TU, 0x71002dc32c-0x71002dcedc); placeholder names, the flags are matched
    // against Entry::flags.
    void sub_71002DC32C();
    bool sub_71002DC3A8(ksys::act::BaseProc* proc, u16 flags);
    bool sub_71002DC628(const ksys::act::BaseProcLink& link, u16 flags);
    bool sub_71002DC8A0(const ksys::act::BaseProcLink& link, u16 flags);
    bool sub_71002DC9E8(const ksys::act::BaseProcLink& link, u16 flags, bool a3);
    void sub_71002DCBDC(u16 flags);
    bool sub_71002DCCBC(u16 flags);
    ksys::act::BaseProcLink* sub_71002DCEDC(u16 flags, f32* a2);

    /* 0x00 */ ksys::act::Actor* mActor;
    /* 0x08 */ sead::SafeArray<Entry, 6> mEntries;
};
KSYS_CHECK_SIZE_NX150(Unk_71002dccbc, 0x98);

}  // namespace uking::act
