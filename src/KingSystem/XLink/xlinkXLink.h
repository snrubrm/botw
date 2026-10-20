#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <container/seadListImpl.h>
#include <prim/seadEnum.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

// Property-definition collection; existing CSV name, opaque here.
class XLinkPropDefinitions;

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

// The footstep reaction speed thresholds (0x7102516320, directly before the bone-name array in .rodata).
// Defined in xlinkXLink.cpp; xlinkUnk_710123830c.cpp reads it directly, so it has hidden visibility.
KSYS_VISIBILITY_HIDDEN extern const f32 sUnk_7102516320[2];

// Placeholder name (result of 0x710123830c, created from the actor's footstep proc type name in
// ActorEffects::init; the XLink member at +0xa0 points to it): footstep settings. The FootstepSilencer
// behavior sets / clears bit 4 of the flags.
struct Unk_710123830c {
    // Whole factory 123830C allocates E8; ctor 1234E78 and D1/D0 1234F40/1235020
    // establish the complete two-slot table at 25162C8. Lifetime remains declaration only.
    Unk_710123830c();
    virtual ~Unk_710123830c();
    // 0x71012372ec: clears bit 0 of the flags (FootstepChanger::m9). Other methods of the TU
    // 0x7101236190-0x710123830c (not decompiled): 0x1236520 (FootstepReactionChanger::m8), 0x12370a8 (m9),
    // 0x12381a8 (FootstepChanger::m8).
    void sub_71012372EC();
    void sub_7101235444();
    void sub_7101236520(s32 reaction, s32 scale, s32 duration);
    void sub_71012370A8();
    void sub_71012381A8(const char* key, s32 duration);
    void sub_710123827C(bool value);
    // 0x7101237dd0: turns the footstep reaction state on (bit 0) once the actor moves faster than
    // 0.25, or queues it with the reaction receiver (bit 1) faster than 0.6; skipped while riding.
    void sub_7101237DD0();

    // 123690C / 1237DD0 read the owning actor here (XLink::CreateArg supplies it).
    /* 0x8 */ act::Actor* mActor;
    u8 _10[0x12 - 0x10];
    // Setter 12381A8 and independent emission 12367FC decrement this halfword counter.
    u16 mOverrideDuration;
    u8 _14[2];
    // Initializer1235044 copies the halfword at argument+58;1236520/70A8 manipulate its flags.
    /* 0x16 */ sead::BitFlag16 _16;
    // 1237DD0 writes this as one halfword: bit 0 (reaction started) / bit 1 (reaction queued).
    /* 0x18 */ u16 _18;
    // 123632C clears one bit per foot index here.
    /* 0x1a */ u16 _1a;
    /* 0x1c */ sead::BitFlag16 _1c;
    u8 _1e[0x34 - 0x1e];
    // Initializer 1235044 supplies the signed reaction kind; updates restore it after an override.
    s32 mDefaultReaction;
    u8 _38[0x50 - 0x38];
    s32 mReaction;
    f32 mReactionScale;
    // Ctor installs its buffer at 6C with capacity 32; 1235830 independently copies event names.
    sead::FixedSafeString<32> mOverrideKey;
    // Initializer 1235044 supplies the bone-name array; 1237654 indexes it for Model::searchBone.
    const char* const* mBoneNames;
    u8 _98[0xc8 - 0x98];
    // 1237DD0 turns the reaction state on when these exceed 0.6 / 0.25.
    /* 0xc8 */ f32 _c8;
    /* 0xcc */ f32 _cc;
    u8 _d0[0xe8 - 0xd0];
};
KSYS_CHECK_SIZE_NX150(Unk_710123830c, 0xe8);

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
        const sead::Vector3f* _38 = nullptr;
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
    f32 sub_71012342A0();
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
    // 0x7101230198: resets both user instances and clears their asset state.
    void sub_7101230198();
    // 0x71012311e4 (CSV ActorEffects::prepareAIChangeMaybe; declared only): called by Actor::onAiEnter.
    void prepareAIChangeMaybe(const char* name, const char* context);
    void sleepELink();
    void resetELinkEvents();
    // 12303EC sets up the user instances; map entry D4D998 supplies the construction heap.
    void initAfterActorConstruct(sead::Heap* heap);
    // 1230B18 releases owned user instances and resources; D4DAB8 calls it before deleting XLink.
    void sub_7101230B18();
    void sub_71012313DC(u32 property, s32 value, bool force);
    void sub_7101231468(u32 property, f32 value, bool force);
    // 0x7101232fb4 (declared only): called by eft::sub_710105DF6C.
    void sub_7101232FB4(const char* name, bool a, bool b, bool c);
    void sub_7101234334(const char* name, bool a, bool pending, bool b);
    void sub_710123445C(const char* name, bool a, bool b);
    // 0x71012345b4 (CSV unnamed; declared only): called by evt::S7EventFlow::x with an event xlink entry name.
    void sub_71012345B4(const char* name, bool a);
    // 0x7101230e18 (declared only, lane5 s6): emits the "Disappear_Ancient" SLink asset and sets a flag (Vanish::enter_ when the die type is 3).
    void sub_7101230E18();
    // 0x7101230e68 (unnamed in the CSV; declaration only): sets (true) / clears mask bit 2 of _73,
    // sleeping through the xlink manager or waking both user instances. The LOD debug helpers call it
    // with the actor's mXLink.
    void sub_7101230E68(bool enable);
    // 0x710123051c (placeholder name): sets the asset info reader of the SLink user instance (if any).
    void sub_710123051C(aal::IAssetInfoReadable* reader);
    void prepareDelete();
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
    /* 0x60 */ u8 _60[8];
    // 1233198 selects this collection from Manager's property table during initialization.
    /* 0x68 */ XLinkPropDefinitions* mPropertyDefinitions;
    // Initializer122EDB0 allocates the corresponding slot arrays using signed byte counts.
    /* 0x70 */ s8 _70;
    /* 0x71 */ s8 _71;
    /* 0x72 */ s8 _72;
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
static_assert(offsetof(XLink, mPropertyDefinitions) == 0x68);

}  // namespace ksys::xlink
