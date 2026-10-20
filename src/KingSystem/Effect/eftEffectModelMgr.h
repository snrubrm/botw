#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"

namespace ksys::act {
class Actor;
}

namespace ksys::res {
class BfRes;
}

namespace ksys::eft {

// A model loaded for effects (placeholder layout; only the fields used so far). Its name is logged
// as "res", the reference count as "ref" (EffectModelMgr debug strings 0x7101e15731 / 0x7101e1578b).
class EffectModelData {
public:
    // 0x7100d9fcfc / 0x7100d9fde4 (CSV names; declarations only). The first drops a reference and
    // asks gsys::EffectModelDrawMgr to delete the model when it reaches 0.
    bool addEffectModel_0(sead::Heap* heap, const char* name, res::BfRes* resource);
    s32 decRefCnt();
    bool finalize();

    bool _0;
    bool _1;
    sead::FixedSafeString<64> mName;
    s32 mRefCount;
    u32 mModelCount;
    sead::FixedSafeString<64> mModelNames[8];
    const char* mModelNamePtrs[8];
    u32 mDrawModelId;
    u8 _36c[4];
    res::Unk_71024f9958 mTextureLinks;
    res::BfRes* mRes;
};
static_assert(offsetof(EffectModelData, mRefCount) == 0x60);
static_assert(offsetof(EffectModelData, mModelCount) == 0x64);
static_assert(offsetof(EffectModelData, mModelNames) == 0x68);
static_assert(offsetof(EffectModelData, mModelNamePtrs) == 0x328);
KSYS_CHECK_SIZE_NX150(EffectModelData, 0x3b0);
static_assert(offsetof(EffectModelData, mRes) == 0x3a8);

// eft::Effect + 0xa628 (from ClusteredRenderer::sub_710124474C).
class EffectModelMgr {
public:
    // 0x7100da0370 / 0x7100da0448. `actor` may be null (ClusteredRenderer passes null; logged as
    // "clusterdRenderer"). Both return false only when `data` is null.
    EffectModelData* entry(sead::Heap* heap, act::Actor* actor, res::BfRes* resource,
                           const char* name);
    bool requestDeleteModel(act::Actor* actor, EffectModelData* data);
    bool release(act::Actor* actor, EffectModelData* data);

private:
    bool mDebugLog;
    sead::CriticalSection mCS;
    sead::CriticalSection mEntryCS;
    // 0x7100d9fea8 searches all 64 records at +0x88, each with stride 0x3b0.
    EffectModelData mEntries[64];
};

}  // namespace ksys::eft
