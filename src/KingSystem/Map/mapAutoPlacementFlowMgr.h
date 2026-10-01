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

struct AutoPlacementFlowRes {
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
    res::Handle* getResource1(int idx);
    res::Handle* getResource2(int idx);

    AutoPlacementFlowRes* getFlow(const sead::SafeString& actor_name, bool near_flow);

private:
    sead::Heap* mHeap;
    sead::SafeArray<AutoPlacementFlowRes, 10> mFlowArray;
    sead::SafeArray<AutoPlacementFlowRes, 7> mFlowNearArray;
};
KSYS_CHECK_SIZE_NX150(AutoPlacementFlowMgr, 0x4758);

}  // namespace ksys::map
