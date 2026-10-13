#pragma once

#include "KingSystem/Physics/System/physUserTag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class ActorChemicals;
}

// Name from the CSV. The carried chemical records construct this tag at +0xc0 in 10C9274.
// The independent 10CE968 consumer returns its ActorChemicals pointer after a runtime cast.
class ChemicalUserTag : public ksys::phys::UserTag {
    SEAD_RTTI_OVERRIDE(ChemicalUserTag, ksys::phys::UserTag)
public:
    explicit ChemicalUserTag(ksys::act::ActorChemicals* chemicals) : mActorChemicals(chemicals) {}

    // The native table uses UserTag's destructor and all of its callback implementations.
    ksys::act::ActorChemicals* mActorChemicals;
};
KSYS_CHECK_SIZE_NX150(ChemicalUserTag, 0x10);
