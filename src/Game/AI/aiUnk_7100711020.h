#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
}

// Unnamed helper (no vtable; placeholder name = constructor address) embedded in CreationNestOnTree
// (_d0). It owns a linked actor (_10) and three message senders. Its other functions
// (0x7100711298..0x7100712388, also called by the NPC avoid / runaway / confront AIs) are not
// declared yet.
class Unk_7100711020 {
public:
    explicit Unk_7100711020(ksys::act::Actor* actor);
    ~Unk_7100711020();

    // Not decompiled yet (placeholder names).
    bool sub_7100711298(sead::Heap* heap, const sead::SafeString& name, bool has_map_object);
    void sub_7100711450();
    void sub_71007114DC();
    void sub_7100711BDC();

    ksys::act::Actor* mActor;
    f32 _8 = 0;
    bool _c = true;
    bool _d = false;
    ksys::act::BaseProcLink _10;
    s32 _20 = 0;
    Unk_71023724e8 _28;
    Unk_7102450c80 _80;
    Unk_7102372510 _d0;
    ksys::Timer _100;
    ksys::Timer _10c;
    ksys::Timer _118;
};
KSYS_CHECK_SIZE_NX150(Unk_7100711020, 0x128);
