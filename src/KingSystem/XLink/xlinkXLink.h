#pragma once

#include <basis/seadTypes.h>
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
    /* 0x58 */ u8 _58[0x110 - 0x58];
};
KSYS_CHECK_SIZE_NX150(XLink, 0x110);

}  // namespace ksys::xlink
