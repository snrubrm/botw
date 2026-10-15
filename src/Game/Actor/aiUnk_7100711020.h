#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "Game/Actor/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::act {
class Actor;
class BaseProc;
class ActorLinkConstDataAccess;
}

// Unnamed helper (no vtable; placeholder name = constructor address) embedded in CreationNestOnTree
// (_d0). It owns a linked actor (_10) and three message senders; also used by the NPC avoid /
// runaway / confront AIs. Methods 0x7100711298-0x7100711f60 (the TU continues with unrelated
// message-text helpers from 0x7100711fac).
class Unk_7100711020 {
public:
    explicit Unk_7100711020(ksys::act::Actor* actor);
    ~Unk_7100711020();

    // Placeholder names.
    bool sub_7100711298(sead::Heap* heap, const sead::SafeString& name, bool has_map_object);
    void sub_7100711450();
    void sub_71007114DC();
    void sub_71007116E0();
    void sub_7100711B14(bool update_pos);
    void sub_7100711BDC();
    void sub_7100711C5C();
    void sub_7100711E0C(const ksys::act::BaseProcLink& target, s32 a, s32 b,
                        const sead::Vector3f* pos, const sead::Matrix34f* mtx);

    ksys::act::Actor* mActor;
    f32 _8 = 0;
    bool _c = true;
    bool _d = false;
    ksys::act::BaseProcLink _10;
    u32 _20 = 0;
    Unk_71023724e8 _28;
    Unk_7102450c80 _80;
    Unk_7102372510 _d0;
    ksys::Timer _100;
    ksys::Timer _10c;
    ksys::Timer _118;
};
KSYS_CHECK_SIZE_NX150(Unk_7100711020, 0x128);

// 0x7100712448: true if `name` contains /Root/Timeline/<prefix>/<node> for one of nine timeline nodes
// (the turn node only when `skip_turn` is false).
bool sub_7100712448(const sead::SafeString& name, const sead::SafeString& prefix, bool skip_turn);
// 0x710071277c: like sub_7100712448 for four other nodes; sets `is_shelter` for the rain shelter node.
bool sub_710071277C(const sead::SafeString& name, const sead::SafeString& prefix, bool* is_shelter);

// 0x7100712ad8: true for an NPC whose slot 0 animation contains Walk or Run, or is Escape or Move_End.
bool sub_7100712AD8(ksys::act::Actor* actor);

// 0x7100712cb0: true for an NPC whose slot 0 animation contains Run or is Escape.
bool sub_7100712CB0(ksys::act::Actor* actor);

// 0x7100712e00: for an NPC holding a Weapon in slot 0, plays AS slot 44 from the weapon's NPCWeaponType
// (or its profile when empty).
bool sub_7100712E00(ksys::act::Actor* actor);

// 0x7100712388: the actor message-text helper following this controller family.
bool sub_7100712388(ksys::act::BaseProc* proc, const ksys::act::ActorLinkConstDataAccess& accessor,
                    const sead::SafeString& key);
