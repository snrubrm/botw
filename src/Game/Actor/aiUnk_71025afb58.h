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
