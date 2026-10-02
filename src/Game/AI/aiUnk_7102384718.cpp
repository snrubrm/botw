#include "Game/AI/aiUnk_7102384718.h"
#include <heap/seadHeap.h>

// NON_MATCHING: the original keeps the two zero stores of _b4 / mRefCount unmerged (stp wzr, wzr) and
// stores _b0 before the derived vtable address load (scheduling)
bool Unk_7102384718Ref::sub_7100137A28(sead::Heap* heap, Unk_71025afb58** slot) {
    mSlot = nullptr;
    if (!slot)
        return false;

    Unk_7102384718* unit;
    if (*slot) {
        unit = sead::DynamicCast<Unk_7102384718>(*slot);
        if (!unit)
            return false;
        ++unit->mRefCount;
    } else {
        unit = new (heap) Unk_7102384718;
        if (!unit)
            return false;
        unit->mRefCount = 1;
        *slot = unit;
    }
    mSlot = slot;
    return true;
}
