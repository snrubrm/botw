#pragma once

#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

// Name from the CSV (ActorLink::rtti1 / rtti2 / m2 / m3 = checkDerivedRuntimeTypeInfo /
// getRuntimeTypeInfo / D2 / D0 at 0x71000dc058 / 0x71000dc124 / 0x71000db710 / 0x71000dc180).
// vtable 0x7102370ea0, RTTI static 0x71025b0c50 (parent Unk_71025afb58). An AI tree variable object
// holding a link to an actor (EquipStand, LimitedTimeredActorCreator, ...). Header-only: its
// functions are emitted in the TU of ChemicalElectricWaterBall.
class ActorLink : public Unk_71025afb58 {
    SEAD_RTTI_OVERRIDE(ActorLink, Unk_71025afb58)
public:
    ~ActorLink() override = default;

    /* 0x08 */ ksys::act::BaseProcLink mLink;
};
KSYS_CHECK_SIZE_NX150(ActorLink, 0x18);

// Placeholder name: vtable 0x7102370e70, RTTI static 0x71025b0c60 (parent ActorLink); no members of its
// own (its D1 is folded with ActorLink's). checkDerivedRuntimeTypeInfo 0x71000dbea8,
// getRuntimeTypeInfo 0x71000dbfc8, D0 0x71000dc024.
class Unk_7102370e70 : public ActorLink {
    SEAD_RTTI_OVERRIDE(Unk_7102370e70, ActorLink)
public:
    ~Unk_7102370e70() override = default;
};
KSYS_CHECK_SIZE_NX150(Unk_7102370e70, 0x18);
