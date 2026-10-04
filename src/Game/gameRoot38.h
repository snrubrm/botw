#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>

namespace uking {

// Name from the CSV (Root38::createInstance 0x71090bf38 ... Root38::testFlag 0x71090c504; the unnamed
// "Root38" of the original's singleton list). Scene pause / freeze flags: setFlag() / testFlag() work on
// an Atomic bit set that lives in an unnamed global (0x71025d1a10: {u32, u32, u32 flags}), the object
// itself (size 0x38, vtable 0x7102473788) only has a few state bytes at 0x28 - 0x30.
// Only what the callers use is declared so far.
class Root38 {
    SEAD_SINGLETON_DISPOSER(Root38)
    Root38();

public:
    virtual ~Root38();

    // 0x71090c504 (declared only): whether bit `flag` of the global flag word is set (the actors use flag 2).
    bool testFlag(int flag) const;
};

}  // namespace uking
