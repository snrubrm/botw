#include "KingSystem/Map/mapAutoPlacementFlowMgr.h"
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <evfl/ResActor.h>
#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys::map {

const char* sFlowResNamesData[] = {
    "AutoPlacement_Animal.bfevfl",
    "AutoPlacement_Bird.bfevfl",
    "AutoPlacement_Enemy_Golem_Little.bfevfl",
    "AutoPlacement_Enemy_Keese.bfevfl",
    "AutoPlacement_Enemy_Lizalfos.bfevfl",
    "AutoPlacement_Enemy_Octarock.bfevfl",
    "AutoPlacement_Enemy_Wizzrobe.bfevfl",
    "AutoPlacement_Enemy_Fish.bfevfl",
    "AutoPlacement_Enemy_Insect.bfevfl",
    "AutoPlacement_Enemy_Material.bfevfl",
};
sead::Buffer<const char*> sFlowResNames{sFlowResNamesData};

const char* sFlowNearResNamesData[] = {
    "AutoPlacementNear_Enemy_Assassin_Middle.bfevfl",
    "AutoPlacementNear_Enemy_Assassin_Shooter_Junior.bfevfl",
    "AutoPlacementNear_Enemy_Chuchu.bfevfl",
    "AutoPlacementNear_Enemy_Dragon.bfevfl",
    "AutoPlacementNear_Enemy_Lizalfos.bfevfl",
    "AutoPlacementNear_Enemy_Octarock.bfevfl",
    "AutoPlacementNear_Enemy_Stal.bfevfl",
};
sead::Buffer<const char*> sFlowNearResNames{sFlowNearResNamesData};

SEAD_SINGLETON_DISPOSER_IMPL(AutoPlacementFlowMgr)

void AutoPlacementFlowMgr::init(sead::Heap* heap) {
    mHeap = sead::ExpHeap::create(0xc000, "AutoPlacementFlowMgr", heap, sizeof(void*),
                                  sead::Heap::cHeapDirection_Forward, false);
}

void AutoPlacementFlowMgr::loadEventFlows() {
    for (int i = 0; i < mFlowArray.size(); i++) {
        auto& flow = mFlowArray[i];
        flow.evfl_name = sFlowResNames[i];
        flow.idx = 0xFF;

        sead::FixedSafeString<128> path;
        path.format("EventFlow/%s", flow.evfl_name.cstr());
        res::LoadRequest req;
        req.mRequester = "AutoPlacementFlow";

        flow.handle.requestLoad(path, &req);
    }

    for (int i = 0; i < mFlowNearArray.size(); i++) {
        auto& flow = mFlowNearArray[i];
        flow.evfl_name = sFlowResNames[i];
        flow.idx = 0xFF;

        sead::FixedSafeString<128> path;
        path.format("EventFlow/%s", flow.evfl_name.cstr());
        res::LoadRequest req;
        req.mRequester = "AutoPlacementFlow";

        flow.handle.requestLoad(path, &req);
    }
}

res::Handle* AutoPlacementFlowMgr::getResource1(int idx) {
    if (idx >= mFlowArray.size())
        return nullptr;
    return &mFlowArray[idx].handle;
}

res::Handle* AutoPlacementFlowMgr::getResource2(int idx) {
    if (idx >= mFlowNearArray.size())
        return nullptr;
    return &mFlowNearArray[idx].handle;
}

// NON_MATCHING: the original compares the flow index with != and schedules the 0x430 stride earlier
AutoPlacementFlowRes* AutoPlacementFlowMgr::getFlow(const sead::SafeString& actor_name,
                                                    bool near_flow) {
    AutoPlacementFlowRes* flows =
        near_flow ? mFlowNearArray.getBufferPtr() : mFlowArray.getBufferPtr();
    const int num_flows = near_flow ? mFlowNearArray.size() : mFlowArray.size();

    for (int i = 0; i < num_flows; ++i) {
        for (auto& name : flows[i].actor_names) {
            if (name == actor_name)
                return &flows[i];
        }
    }
    return nullptr;
}

}  // namespace ksys::map
