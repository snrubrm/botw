#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include "Game/AI/aiMessage3DText.h"
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

// Placeholder name (ctor 0x7100743798; methods 0x7100743814 (init with the actor, returns true),
// 0x7100744200 (sets the mode `_0` and restarts `_e0`), ... in TU 0x7100743740-0x71007444ac).
// Embedded in Unk_7102433970 at 0x8.
class Unk_7100743798 {
public:
    Unk_7100743798();

    bool sub_7100743814(ksys::act::Actor* actor);
    // Updates the message and mode timer; complete body and ZoraHeroRelicBattleRoot caller.
    void sub_7100743A40();
    void sub_7100743BD4(s32 mode, sead::BufferedSafeString* label);
    void sub_7100744200(s32 mode, bool force);

    /* 0x000 */ s32 _0;
    /* 0x008 */ uking::Message3DText _8;
    /* 0x0e0 */ ksys::Timer _e0;
    struct Permutation {
        s8 mCount = 9;
        s8 mIndex = 0;
        sead::SafeArray<s8, 9> mValues;
    };
    KSYS_CHECK_SIZE_NX150(Permutation, 0xb);
    /* 0x0ec */ sead::SafeArray<Permutation, 7> mPermutations;
    /* 0x13c */ s32 _13c;
    // Separate boolean writers in ZoraHeroRelicBattleRoot; independent update tests each byte.
    /* 0x140 */ bool _140;
    /* 0x141 */ bool _141;
};
KSYS_CHECK_SIZE_NX150(Unk_7100743798, 0x148);

// Placeholder name (vtable 0x7102433970; D2 0x71006145e0, D0 0x7100615194, RTTI 0x710061506c /
// 0x7100615138). AI tree variable object stored in "ZoraHeroShowMsgUnit" by
// ZoraHeroRelicBattleRoot (its member at 0x48).
class Unk_7102433970 : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(Unk_7102433970, Unk_71025afb58)
public:
    Unk_7102433970() = default;
    ~Unk_7102433970() override = default;

    Unk_7100743798 _8;
};
KSYS_CHECK_SIZE_NX150(Unk_7102433970, 0x150);

