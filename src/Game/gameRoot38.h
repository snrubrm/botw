#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

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

    // 0x710090c07c (declared only): sets / clears bit `flag` of the global flag word
    bool setFlag(int flag, bool on);
    // 0x71090c504 (declared only): whether bit `flag` of the global flag word is set (the actors use flag 2).
    bool testFlag(int flag) const;
    // 0x710090c300 (CSV Root38::hasAnyFlag; declared only): whether any bit of the global flag word is set.
    bool hasAnyFlag() const;
    // 0x71090c4e0 (declared only; CSV Root38::doNotFreezeScene).
    bool doNotFreezeScene() const;
    // 0x710090c4f8 (CSV Root38::setField2F): stores the flag byte at 0x2f.
    void setField2F(bool value);
    // 0x7100f41808 (CSV name): stores the scene's Root38 pointer in the framework block.
    static void setInstance2(Root38* value);

    u8 _28[0x2f - 0x28];
    // Checked by setFlag: no flag may change while it is set.
    bool _2f = false;
    u8 _30[0x38 - 0x30];
};
KSYS_CHECK_SIZE_NX150(Root38, 0x38);

// 0x7100f41834 (CSV unnamed; placeholder name; declared only): returns the address of an unknown global
// (0x710260b310); S7EventFlow::calc calls it and discards the result.
void* sub_7100F41834();

}  // namespace uking
