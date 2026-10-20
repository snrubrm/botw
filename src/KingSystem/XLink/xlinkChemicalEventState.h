#pragma once

#include <container/seadSafeArray.h>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Chemical;
}

namespace ksys::xlink {

// Placeholder name: E3AA34 allocates 0x2b0 bytes and E3B298 constructs this chemical event state.
// 0x710122E6E8 transfers twenty-one ELink/SLink pairs and 0x710122E740 fades the same pairs.
class ChemicalEventState {
public:
    ChemicalEventState();
    void transferFrom(ChemicalEventState& other);
    void fade();
    // 0x710122DE90 chooses the actor or reaction fallback's XLink and forwards this state, the output
    // handle pair, chemical and effect kind to 0x710122E018. The two final inputs are bools there.
    void sub_710122DE90(act::Actor* actor, Unk_71012419b4* handles, act::Chemical* chemical,
                        u32 kind, bool a, bool force_fallback);

    /* 0x00 */ bool mFaded = false;
    /* 0x04 */ u32 mActiveMask = 0;
    /* 0x08 */ u32 mKind = 0;
    /* 0x10 */ sead::SafeArray<Unk_71012419b4, 21> mHandles;
};
KSYS_CHECK_SIZE_NX150(ChemicalEventState, 0x2b0);

}  // namespace ksys::xlink
