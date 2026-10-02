#pragma once

#include <basis/seadNew.h>
#include <heap/seadHeap.h>
#include <prim/seadRuntimeTypeInfo.h>

// Unnamed polymorphic root class of objects that AI trees share through `void*` AI tree
// variables (AirOctaDataMgr, the PriestBossMetaAIUnit object Unk_7102450fa8, ...). It has no
// vtable or constructor of its own in the executable (its destructor is trivial and always
// inlined); placeholder name from its RTTI typeInfo static at 0x71025afb58.
class Unk_71025afb58 {
    SEAD_RTTI_BASE(Unk_71025afb58)
public:
    virtual ~Unk_71025afb58() = default;
};

// Handle to a reference-counted T object (T derives from Unk_71025afb58 and has an `s32 mRefCount`)
// that AI trees share through a `void*` AI tree variable slot (the slot's `*holder` is the object).
// Not a class with a name in the executable: the acquire code (create the object when the slot is
// empty, else check its type and bump the count) exists as an out-of-line function in some
// instantiations (0x71000b0800 for Unk_71023698d0, called by BackFlip::init_ and
// NavMoveTarget::init_) and inline in others (NavMoveTarget::init_ for Unk_71023ea3f8); the release
// code is inlined in the destructors of the owning AI classes (e.g. NavMoveTarget D1, 0x4b7548).
template <typename T>
class Unk_71025afb58Ref {
public:
    ~Unk_71025afb58Ref() { release(); }

    bool acquire(sead::Heap* heap, Unk_71025afb58** holder) {
        mHolder = nullptr;
        if (!holder)
            return false;
        if (auto* existing = *holder) {
            auto* obj = sead::DynamicCast<T>(existing);
            if (!obj)
                return false;
            ++obj->mRefCount;
        } else {
            auto* obj = new (heap) T;
            if (!obj)
                return false;
            obj->mRefCount = 1;
            *holder = obj;
        }
        mHolder = holder;
        return true;
    }

    void release() {
        if (!mHolder)
            return;
        auto* obj = sead::DynamicCast<T>(*mHolder);
        if (obj && obj->mRefCount > 0 && obj->mRefCount-- == 1) {
            *mHolder = nullptr;
            delete obj;
        }
        mHolder = nullptr;
    }

    // The T::Data base of the object behind the slot (null if the object is not a T).
    template <typename U = T>
    typename U::Data* getData() const {
        auto* obj = *mHolder;
        if (sead::IsDerivedFrom<T>(obj))
            return static_cast<T*>(obj);
        return nullptr;
    }

    Unk_71025afb58** mHolder = nullptr;
};
