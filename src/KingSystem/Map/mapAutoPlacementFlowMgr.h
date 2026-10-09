#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <evfl/Flowchart.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class AutoPlacement;

// evfl::AllocateArg callbacks used by AutoPlacementFlowRes::start; userdata is its heap.
void* autoPlacementBfevflAlloc(size_t size, size_t alignment, void* userdata);
void autoPlacementBfevflFree(void* ptr, void* userdata);

struct AutoPlacementFlowRes {
    bool load(int idx, sead::Heap* heap);
    void start(AutoPlacement* placement, const sead::SafeString& unit_name, int*);

    res::Handle handle;
    sead::SafeString evfl_name;
    evfl::FlowchartContext flowchart_ctx;
    AutoPlacement* placement;
    sead::SafeString unit_name;
    u8 idx;
    s8 placement_type;
    sead::PtrArray<sead::SafeString> actor_names;
    u8 _120[0x430 - 0x120];
};
KSYS_CHECK_SIZE_NX150(AutoPlacementFlowRes, 0x430);

class AutoPlacementFlowMgr {
    SEAD_SINGLETON_DISPOSER(AutoPlacementFlowMgr)
public:
    AutoPlacementFlowMgr();
    ~AutoPlacementFlowMgr();

    void init(sead::Heap* heap);
    void loadEventFlows();
    // 0x7100652780 loads each flow in order and returns false at the first failure.
    bool resAreReady();
    // (both return the flow's first member, `handle`: the pointer is the AutoPlacementFlowRes itself)
    AutoPlacementFlowRes* getResource1(int idx);
    AutoPlacementFlowRes* getResource2(int idx);

    AutoPlacementFlowRes* getFlow(const sead::SafeString& actor_name, bool near_flow);

private:
    sead::Heap* mHeap;
    sead::SafeArray<AutoPlacementFlowRes, 10> mFlowArray;
    sead::SafeArray<AutoPlacementFlowRes, 7> mFlowNearArray;
};
KSYS_CHECK_SIZE_NX150(AutoPlacementFlowMgr, 0x4758);

}  // namespace ksys::map
