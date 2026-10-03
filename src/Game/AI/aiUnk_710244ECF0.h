#pragma once

#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActorBind.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Types.h"

// Placeholder name = vtable address (0x710244ecf0, RTTI static from GOT 0x7102578cd0; constructor
// 0x71006e7ddc, m4 0x71006e7e48): an ActorBind variant that binds the owner's actor to a node of the
// bound actor (name in `_68`; m4 is not decompiled yet). Embedded in ChemicalElectricWaterBall (+0xc0),
// RodMagicPhysBall (+0xe8) and Stick (+0x48). D1 / D0 / m5 are inline (emitted in the users' TUs).
class Unk_710244ecf0 : public ksys::act::ActorBind {
    SEAD_RTTI_OVERRIDE(Unk_710244ecf0, ksys::act::ActorBind)
public:
    Unk_710244ecf0();
    ~Unk_710244ecf0() override = default;

    bool m4(ksys::act::BaseProc* proc) override;

    /* 0x28 */ sead::Matrix34f _28 = sead::Matrix34f::ident;
    /* 0x58 */ ksys::act::BaseProcLink _58;
    /* 0x68 */ sead::SafeString _68 = sead::SafeString::cEmptyString;
};
KSYS_CHECK_SIZE_NX150(Unk_710244ecf0, 0x78);
