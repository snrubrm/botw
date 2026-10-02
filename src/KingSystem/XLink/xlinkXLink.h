#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace xlink2 {
class UserInstanceELink;
class UserInstanceSLink;
}  // namespace xlink2

namespace ksys::xlink {

// The per-actor xlink object (Actor::mXLink; name from the existing forward declaration in
// actActor.h). The CSV calls its functions ActorEffects::* (ctor 0x710122fce0, init 0x710122edb0;
// created by ActorXLinkInstanceBuilder::build with new(0x110)) and uses "XLink::" for the xlink
// manager singleton (0x710123de44 createInstance).
// TODO: incomplete. Only the user instances read by the actor xlink helpers are declared.
class XLink {
public:
    /* 0x00 */ u8 _0[0x48];
    /* 0x48 */ xlink2::UserInstanceELink* _48;
    /* 0x50 */ xlink2::UserInstanceSLink* _50;
    /* 0x58 */ u8 _58[0xcc - 0x58];
    // Flags (ctor 0x710122fce0 sets 0x800c0000, then 0x200 / 0x10000 / 0x4000000 depending on the
    // actor; AI code sets 0x200 (IbutsuWaterFallRoot::enter_) and clears 0x80000
    // (AppearFromTargetFrontAfterChase::m37) directly).
    /* 0xcc */ sead::BitFlag32 _cc;
    /* 0xd0 */ u8 _d0[0x110 - 0xd0];
};
KSYS_CHECK_SIZE_NX150(XLink, 0x110);

}  // namespace ksys::xlink
