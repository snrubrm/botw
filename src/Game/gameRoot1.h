#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <prim/seadEnum.h>
#include "KingSystem/Utils/Types.h"

namespace uking {

// CSV name. The singleton constructor allocates 0x38 bytes; this class has no base.
class Root1 {
    SEAD_SINGLETON_DISPOSER(Root1)
    Root1();

public:
    virtual ~Root1();
    // The index conversion is materialized in the original setter. Names are unknown.
    SEAD_ENUM(FlagIdx, _0, _1)
    void sub_7100899CA4(FlagIdx idx, s32 value);
    bool sub_7100899CC8();

    sead::SafeArray<s32, 2> _28;
    bool _30 = true;
    bool _31 = true;
};
KSYS_CHECK_SIZE_NX150(Root1, 0x38);

}  // namespace uking
