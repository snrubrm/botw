#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::eft {

// A model loaded for effects (placeholder layout; only the fields used so far). Its name is logged
// as "res", the reference count as "ref" (EffectModelMgr debug strings 0x7101e15731 / 0x7101e1578b).
class EffectModelData {
public:
    // 0x7100d9fcfc / 0x7100d9fde4 (CSV names; declarations only). The first drops a reference and
    // asks gsys::EffectModelDrawMgr to delete the model when it reaches 0.
    void addEffectModel();
    void finalize();

    bool _0;
    bool _1;
    sead::FixedSafeString<64> mName;
    s32 mRefCount;
    u8 _64[0x368 - 0x64];
    u32 mDrawModelId;
    u8 _36c[0x3a8 - 0x36c];
    void* mRes;
};
static_assert(offsetof(EffectModelData, mRefCount) == 0x60);
static_assert(offsetof(EffectModelData, mRes) == 0x3a8);

// eft::Effect + 0xa628 (from ClusteredRenderer::sub_710124474C).
class EffectModelMgr {
public:
    // 0x7100da0370 / 0x7100da0448. `actor` may be null (ClusteredRenderer passes null; logged as
    // "clusterdRenderer"). Both return false only when `data` is null.
    bool requestDeleteModel(act::Actor* actor, EffectModelData* data);
    bool release(act::Actor* actor, EffectModelData* data);

private:
    bool mDebugLog;
    sead::CriticalSection mCS;
};

}  // namespace ksys::eft
