#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <container/seadListImpl.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace gsys {
class Model;
class ModelAnimation;
}

namespace aal {
class IAssetInfoReadable;
}

namespace xlink2 {
class UserInstanceELink;
class UserInstanceSLink;
}  // namespace xlink2

namespace ksys::act {
class Actor;
namespace ai { class RootAi; }
}

namespace ksys::as {
class ASList;
}

namespace ksys::snd {
class Unk_710251b6f0;
}

namespace ksys::xlink {
class Unk_71025168a0;

// Placeholder name (result of 0x710123830c, created from the actor's footstep proc type name in
// ActorEffects::init; the XLink member at +0xa0 points to it): footstep settings. The FootstepSilencer
// behavior sets / clears bit 4 of the flags.
struct Unk_710123830c {
    // 0x71012372ec: clears bit 0 of the flags (FootstepChanger::m9). Other methods of the TU
    // 0x7101236190-0x710123830c (not decompiled): 0x1236520 (FootstepReactionChanger::m8), 0x12370a8 (m9),
    // 0x12381a8 (FootstepChanger::m8).
    void sub_71012372EC();
    void sub_7101235444();
    void sub_7101236520(s32 reaction, s32 scale, s32 duration);
    void sub_71012370A8();
    void sub_71012381A8(const char* key, s32 duration);

    /* 0x00 */ u8 _0[0x1c];
    /* 0x1c */ sead::BitFlag16 _1c;
};

// The per-actor xlink object (Actor::mXLink; name from the existing forward declaration in
// actActor.h). The CSV calls its functions ActorEffects::* (ctor 0x710122fce0, init 0x710122edb0;
// created by ActorXLinkInstanceBuilder::build with new(0x110)) and uses "XLink::" for the xlink
// manager singleton (0x710123de44 createInstance).
// TODO: incomplete. Only the user instances read by the actor xlink helpers are declared.
class XLink {
public:
    // Producer11C9AA0 supplies each field;122ECC8 creates the 0x110-byte XLink from this record.
    struct CreateArg {
        CreateArg();
        XLink* build(sead::Heap* heap);
        act::Actor* actor = nullptr;
        sead::SafeString actorName;
        sead::SafeString uniqueName;
        const sead::Matrix34f* rootMtx = nullptr;
        sead::Vector3f* scale = nullptr;
        sead::Vector3f* _38 = nullptr;
        gsys::Model* model = nullptr;
        u32 flags = 0;
    };
    KSYS_CHECK_SIZE_NX150(CreateArg, 0x50);

    // Camera7963AC constructs this record;1230100 forwards each pointer to UserInstance.
    struct RebuildArg {
        RebuildArg();
        const sead::Matrix34f* rootMtx = nullptr;
        sead::Vector3f* rootPos = nullptr;
        sead::Vector3f* _10 = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(RebuildArg, 0x18);
    void sub_7101230100(const RebuildArg& arg);

    // Placeholder (values unknown): the bit index argument of toggle / sleep / setMask (bit `1 << value` of _73).
    // An enum wrapper: the three functions spill it to the stack and reload it for each use, like SEAD_ENUM
    // parameters.
    SEAD_ENUM(MaskBit, _0, _1, _2, _3, _4, _5, _6, _7)

    // 0x71012302d0 (CSV ActorEffects::toggle; declaration only, lane2 s21): PriestBossAfterImageRoot::enter_
    // calls it with true.
    // Clears `bit` of _73 and reactivates the user instances when the last bit goes (the wake-up counterpart of
    // setMask / sleep).
    void toggle(MaskBit bit);
    // 0x7101230c88 (declared only): sets `bit` of _73; on the first bit sleeps (scene status 4) or hands the
    // object to the xlink manager (0x7101240570).
    void sleep(MaskBit bit);
    // 0x7101232e88 / 0x7101232f2c: actor-job effect activity queries.
    bool x_1();
    bool x_2();
    void x_5();
    void setExtraLabels(const char* const* labels, s32 count);
    void silenceFootsteps();
    void unsilenceFootsteps();
    bool sub_7101233168();
    void sub_71012342D8(bool value);
    bool sub_71012342F8();
    act::ai::RootAi* getRootAi() const;
    gsys::ModelAnimation* getModelAnimation() const;
    void x_4(bool paused);
    // 0x7101230fc8: pauses selected sound groups.
    void sub_7101230FC8(bool paused, bool skip_environment);
    // 0x71012311d8 (placeholder name): `sub_7101230FC8(paused, false)`.
    void sub_71012311D8(bool paused);
    // 0x7101230dac (CSV ActorEffects::setMask; declaration only, lane2 s21): PriestBossAfterImageRoot::calc_
    // calls it with 1 while `_73` is 0.
    void setMask(MaskBit bit);
    // 0x7101230d20 (CSV ActorEffects::sleep_; 140 B, declared only): called by setMask when the first mask bit is set.
    void sleep_();
    // 0x7101231500 (CSV ActorEffects::x_3; declared only): called by Actor::m75.
    void sub_7101231500();
    // 0x71012311e4 (CSV ActorEffects::prepareAIChangeMaybe; declared only): called by Actor::onAiEnter.
    void prepareAIChangeMaybe(const char* name, const char* context);
    void sleepELink();
    void resetELinkEvents();
    void sub_71012313DC(u32 property, s32 value, bool force);
    void sub_7101231468(u32 property, f32 value, bool force);
    // 0x7101232fb4 (declared only): called by eft::sub_710105DF6C.
    void sub_7101232FB4(const char* name, bool a, bool b, bool c);
    void sub_7101234334(const char* name, bool a, bool pending, bool b);
    void sub_710123445C(const char* name, bool a, bool b);
    // 0x7101230e18 (declared only, lane5 s6): emits the "Disappear_Ancient" SLink asset and sets a flag (Vanish::enter_ when the die type is 3).
    void sub_7101230E18();
    // 0x710123051c (placeholder name): sets the asset info reader of the SLink user instance (if any).
    void sub_710123051C(aal::IAssetInfoReadable* reader);
    void sub_71012305AC();
    void sub_7101230968();
    // 0x7101230714 (placeholder name): fades the looping effects and post-calcs the ELink user instance while it has
    // events (false); true otherwise.
    bool sub_7101230714();

    // 0x7101232318: the linked actor's AS list, or null.
    as::ASList* getASList() const;

    // Producer11C9AA0 supplies Actor.mModel in CreateArg+40; ctor122FCE0 stores it here.
    /* 0x00 */ gsys::Model* mModel;
    // 0x710122fce0 stores the Actor from its creation argument at +0x8.
    /* 0x08 */ act::Actor* mActor;
    /* 0x10 */ u8 _10[0x48 - 0x10];
    /* 0x48 */ xlink2::UserInstanceELink* _48;
    /* 0x50 */ xlink2::UserInstanceSLink* _50;
    /* 0x58 */ Unk_71025168a0* mUser;
    /* 0x60 */ u8 _60[0x73 - 0x60];
    /* 0x73 */ sead::BitFlag8 _73;
    /* 0x74 */ u8 _74[0xa0 - 0x74];
    /* 0xa0 */ Unk_710123830c* _a0;
    /* 0xa8 */ snd::Unk_710251b6f0* mMiiSound;
    /* 0xb0 */ u8 _b0[0xbc - 0xb0];
    /* 0xbc */ u32 _bc;
    /* 0xc0 */ u8 _c0[0xcc - 0xc0];
    // Flags (ctor 0x710122fce0 sets 0x800c0000, then 0x200 / 0x10000 / 0x4000000 depending on the
    // actor; AI code sets 0x200 (IbutsuWaterFallRoot::enter_) and clears 0x80000
    // (AppearFromTargetFrontAfterChase::m37) directly).
    /* 0xcc */ sead::BitFlag32 _cc;
    /* 0xd0 */ u8 _d0[0x100 - 0xd0];
    /* 0x100 */ sead::ListNode mSleepNode;
};
KSYS_CHECK_SIZE_NX150(XLink, 0x110);

}  // namespace ksys::xlink
