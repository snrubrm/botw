#include "Game/AI/aiUnk_7102384718.h"
#include <heap/seadHeap.h>

bool Unk_7102384718Ref::sub_7100137A28(sead::Heap* heap, Unk_71025afb58** slot) {
    mSlot = nullptr;
    if (!slot)
        return false;

    Unk_7102384718* unit;
    if (*slot) {
        unit = sead::DynamicCast<Unk_7102384718>(*slot);
        if (!unit)
            return false;
        ++unit->_8.mRefCount;
    } else {
        unit = new (heap) Unk_7102384718;
        if (!unit)
            return false;
        unit->_8.mRefCount = 1;
        *slot = unit;
    }
    mSlot = slot;
    return true;
}
