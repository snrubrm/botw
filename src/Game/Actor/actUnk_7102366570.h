#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

class Unk_7102366570;

// 2026-10-07: original list helpers 0x71006cee58..0x71006cef48 prove this prefix.
// The first word's complete owning class remains unresolved; no instance is constructed here.
class Unk_71006cee58 {
public:
    void clear();
    void erase(Unk_7102366570* callback);
    void append(Unk_7102366570* callback);
    void dispatch();

    u8 _0[8];
    ksys::act::Actor* mActor;
    Unk_7102366570* mHead;
};
KSYS_CHECK_SIZE_NX150(Unk_71006cee58, 0x18);

// 2026-10-07: root RTTI0x71025b0238, vtable0x7102366570; intrusive callback, not DamageCallback.
class Unk_7102366570 {
    SEAD_RTTI_BASE(Unk_7102366570)
public:
    // Original own D1/D0 are 0x710009c848 / 0x710009c870 and remain out of line.
    virtual ~Unk_7102366570();
    virtual void call(ksys::act::Actor* actor) = 0;

    Unk_7102366570* mPrev = nullptr;
    Unk_7102366570* mNext = nullptr;
    Unk_71006cee58* mOwner = nullptr;
};
KSYS_CHECK_SIZE_NX150(Unk_7102366570, 0x20);
