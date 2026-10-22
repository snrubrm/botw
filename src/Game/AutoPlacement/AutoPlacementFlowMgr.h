#pragma once

#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <evfl/Flowchart.h>
#include <evfl/Query.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"
#include "Game/AutoPlacement/AutoPlacement.h"

namespace uking {

class AutoPlacement;

// evfl::AllocateArg callbacks used by AutoPlacementFlowRes::start; userdata is its heap.
void* autoPlacementBfevflAlloc(size_t size, size_t alignment, void* userdata);
void autoPlacementBfevflFree(void* ptr, void* userdata);

struct AutoPlacementFlowRes {
    bool load(int idx, sead::Heap* heap);
    // 0x71006516f4 (CSV autoPlacementFlowStuff) is the real start: it stores the placement, the unit name
    // and the u16 the caller points at, then starts the flowchart when the context's object and
    // entry-point indices are set (both are private in our evfl, so the body stays undecompiled for now).
    void start(AutoPlacement* placement, const char* unit_name,
               sead::TypedBitFlag<ActorSpawnInfo::SpawnLocation>* a3);

    ksys::res::Handle handle;
    sead::SafeString evfl_name;
    evfl::FlowchartContext flowchart_ctx;
    AutoPlacement* placement;
    sead::SafeString unit_name;
    u8 idx;
    s8 placement_type;
    u16 _10a;
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

// 0x7100653788 (CSV apQueryPlayerRideHorse): AutoPlacement query handler; declared here for the
// flow's query registration.
s32 apQueryPlayerRideHorse();

// The AutoPlacement flow query handlers (0x7100653290 .. 0x7100654290). Their argument's
// actor_user_data is the AutoPlacementFlowRes whose flow runs the query.
s32 apQueryGroundNorm(const evfl::QueryArg& arg);
s32 apQueryTreeRate(const evfl::QueryArg& arg);
s32 apQueryPosHeight(const evfl::QueryArg& arg);
s32 apQueryWaterDepth(const evfl::QueryArg& arg);
s32 apQueryRouteDistance(const evfl::QueryArg& arg);
s32 apQueryGrassHeight(const evfl::QueryArg& arg);
s32 apQueryWaterSurface(const evfl::QueryArg& arg);
s32 apQueryWaterDistance(const evfl::QueryArg& arg);
s32 apQueryUnknown(const evfl::QueryArg& arg);
s32 apQueryGroundMat(const evfl::QueryArg& arg);
s32 apQueryWaterSubMat(const evfl::QueryArg& arg);
s32 apQueryCheckGameData(const evfl::QueryArg& arg);
s32 apQueryCheckPouchItemCount(const evfl::QueryArg& arg);
s32 apQueryCheckPouchItemCountFromActor(const evfl::QueryArg& arg);
s32 apQueryCheckTimeType(const evfl::QueryArg& arg);
s32 apQueryNavMeshFace(const evfl::QueryArg& arg);
s32 apQueryEcoAreaActorName(const evfl::QueryArg& arg);
s32 apQueryRailDistance(const evfl::QueryArg& arg);

}  // namespace uking
