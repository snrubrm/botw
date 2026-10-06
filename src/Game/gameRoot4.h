#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadEnum.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// Name from the CSV. createInstance (0x71008bccd4) allocates 0x40 bytes and
// installs sInstance at 0x71025d16c0. This is separate from MaskController.
class Root4 : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(Root4)
    Root4() = default;

public:
    virtual ~Root4() = default;

    // SEAD_ENUM copies/conversions are visible in the flag helpers. Names are unknown.
    SEAD_ENUM(FlagIdx, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9)
    // 0x71008bce34: tests the effective flag.
    bool checkFlag(FlagIdx idx) const;
    // 0x71008bcf44: overrides the selected flag.
    void sub_71008BCF44(FlagIdx idx, bool on);
    // 0x71008bcfa0: removes the override and recomputes it from the records.
    void sub_71008BCFA0(FlagIdx idx);

    struct Record {
        s32 _0;
        u32 _4;
    };
    sead::BitFlag32 _28{0xffffffff};
    sead::BitFlag32 _2c;
    sead::Buffer<Record> _30;
};
KSYS_CHECK_SIZE_NX150(Root4, 0x40);

}  // namespace uking
