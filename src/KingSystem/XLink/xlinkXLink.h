#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace xlink2 {
class UserInstanceELink;
class UserInstanceSLink;
}  // namespace xlink2

namespace ksys::xlink {

// Placeholder name (result of 0x710123830c, created from the actor's footstep proc type name in
// ActorEffects::init; the XLink member at +0xa0 points to it): footstep settings. The FootstepSilencer
// behavior sets / clears bit 4 of the flags.
struct Unk_710123830c {
    // 0x71012372ec: clears bit 0 of the flags (FootstepChanger::m9). Other methods of the TU
    // 0x7101236190-0x710123830c (not decompiled): 0x1236520 (FootstepReactionChanger::m8), 0x12370a8 (m9),
    // 0x12381a8 (FootstepChanger::m8).
    void sub_71012372EC();
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
    // 0x71012302d0 (CSV ActorEffects::toggle; declaration only, lane2 s21): PriestBossAfterImageRoot::enter_
    // calls it with true.
    void toggle(bool a1);
    void sleep(s32 reason);
    // 0x7101232e88 / 0x7101232f2c: actor-job effect activity queries.
    bool x_1();
    bool x_2();
    void x_4(bool paused);
    // 0x7101230fc8: pauses selected sound groups.
    void sub_7101230FC8(bool paused, bool include_music);
    // 0x71012311d8 (placeholder name): `sub_7101230FC8(paused, false)`.
    void sub_71012311D8(bool paused);
    // 0x7101230dac (CSV ActorEffects::setMask; declaration only, lane2 s21): PriestBossAfterImageRoot::calc_
    // calls it with 1 while `_73` is 0.
    void setMask(int a1);
    // 0x7101231500 (CSV ActorEffects::x_3; declared only): called by Actor::m75.
    void sub_7101231500();
    // 0x71012311e4 (CSV ActorEffects::prepareAIChangeMaybe; declared only): called by Actor::onAiEnter.
    void prepareAIChangeMaybe(const char* name, const char* context);
    void sleepELink();
    void resetELinkEvents();
    void sub_7101231468(u32 property, f32 value, bool force);
    // 0x7101232fb4 (declared only): called by eft::sub_710105DF6C.
    void sub_7101232FB4(const char* name, bool a, bool b, bool c);
    // 0x7101230e18 (declared only, lane5 s6): emits the "Disappear_Ancient" SLink asset and sets a flag (Vanish::enter_ when the die type is 3).
    void sub_7101230E18();

    /* 0x00 */ u8 _0[0x48];
    /* 0x48 */ xlink2::UserInstanceELink* _48;
    /* 0x50 */ xlink2::UserInstanceSLink* _50;
    /* 0x58 */ u8 _58[0x73 - 0x58];
    /* 0x73 */ u8 _73;
    /* 0x74 */ u8 _74[0xa0 - 0x74];
    /* 0xa0 */ Unk_710123830c* _a0;
    /* 0xa8 */ u8 _a8[0xbc - 0xa8];
    /* 0xbc */ u32 _bc;
    /* 0xc0 */ u8 _c0[0xcc - 0xc0];
    // Flags (ctor 0x710122fce0 sets 0x800c0000, then 0x200 / 0x10000 / 0x4000000 depending on the
    // actor; AI code sets 0x200 (IbutsuWaterFallRoot::enter_) and clears 0x80000
    // (AppearFromTargetFrontAfterChase::m37) directly).
    /* 0xcc */ sead::BitFlag32 _cc;
    /* 0xd0 */ u8 _d0[0x110 - 0xd0];
};
KSYS_CHECK_SIZE_NX150(XLink, 0x110);

}  // namespace ksys::xlink
