#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace uking::act {
class Unk_7102357908;
}

// 2026-10-07: root RTTI0x71025b0238, vtable0x7102366570; intrusive callback, not DamageCallback.
class Unk_7102366570 {
    SEAD_RTTI_BASE(Unk_7102366570)
public:
    // Original own D1/D0 are 0x710009c848 / 0x710009c870 and remain out of line.
    virtual ~Unk_7102366570();
    virtual void call(ksys::act::Actor* actor) = 0;

    Unk_7102366570* mPrev = nullptr;
    Unk_7102366570* mNext = nullptr;
    uking::act::Unk_7102357908* mOwner = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_7102366570, 0x20);
