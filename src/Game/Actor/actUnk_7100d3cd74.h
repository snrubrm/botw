#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

namespace uking::act {

// Placeholder name (ctor 0x7100d3cd74, dtor 0x7100d3cd84). A list of heap-allocated nodes that each
// hold a BaseProcLink at +0x20; embedded in Enemy at 0x1128 and in NPC at 0xfa8 (their m101 returns
// it).
class Unk_7100d3cd74 {
public:
    explicit Unk_7100d3cd74(ksys::act::Actor* actor);
    ~Unk_7100d3cd74();

    /* 0x00 */ u8 _0[0x18];  // list head (prev, next) + count
    /* 0x18 */ ksys::act::Actor* mActor;
};
KSYS_CHECK_SIZE_NX150(Unk_7100d3cd74, 0x20);

}  // namespace uking::act
