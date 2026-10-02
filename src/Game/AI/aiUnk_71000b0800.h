#pragma once

#include <heap/seadHeap.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "Game/AI/aiUnk_71025afb58.h"

// Placeholder name (the out-of-line acquire is 0x71000b0800; the original's holder is a pointer to the
// AI tree variable slot): a reference to a shared `T` created on first use.
template <class T>
struct Unk_71000b0800 {
    ~Unk_71000b0800() { release(); }

    // Fills this with `var` and takes a reference to *var, creating the object if the slot is empty.
    bool acquire(sead::Heap* heap, Unk_71025afb58** var) {
        _0 = nullptr;
        if (!var)
            return false;
        if (auto* obj = *var) {
            auto* checker = sead::DynamicCast<T>(obj);
            if (!checker)
                return false;
            ++checker->mRefCount;
        } else {
            auto* checker = new (heap, 8) T;
            if (!checker)
                return false;
            checker->mRefCount = 1;
            *var = checker;
        }
        _0 = var;
        return true;
    }

    void release() {
        if (_0) {
            if (auto* checker = sead::DynamicCast<T>(*_0)) {
                if (checker->mRefCount > 0 && --checker->mRefCount <= 0) {
                    *_0 = nullptr;
                    delete checker;
                }
            }
            _0 = nullptr;
        }
    }

    Unk_71025afb58** _0 = nullptr;
};
