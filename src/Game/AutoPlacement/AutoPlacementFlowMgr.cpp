#include "Game/AutoPlacement/AutoPlacementFlowMgr.h"
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>
#include <evfl/ResActor.h>
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Terrain/teraSystem.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"

namespace uking {

void* autoPlacementBfevflAlloc(size_t size, size_t alignment, void* userdata) {
    return static_cast<sead::Heap*>(userdata)->alloc(size, alignment);
}

void autoPlacementBfevflFree(void* ptr, void* userdata) {
    static_cast<sead::Heap*>(userdata)->free(ptr);
}

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
        ksys::res::LoadRequest req;
        req.mRequester = "AutoPlacementFlow";

        flow.handle.requestLoad(path, &req);
    }

    for (int i = 0; i < mFlowNearArray.size(); i++) {
        auto& flow = mFlowNearArray[i];
        flow.evfl_name = sFlowResNames[i];
        flow.idx = 0xFF;

        sead::FixedSafeString<128> path;
        path.format("EventFlow/%s", flow.evfl_name.cstr());
        ksys::res::LoadRequest req;
        req.mRequester = "AutoPlacementFlow";

        flow.handle.requestLoad(path, &req);
    }
}

bool AutoPlacementFlowMgr::resAreReady() {
    for (int i = 0; i < mFlowArray.size(); ++i) {
        if (!mFlowArray[i].load(i, mHeap))
            return false;
    }
    for (int i = 0; i < mFlowNearArray.size(); ++i) {
        if (!mFlowNearArray[i].load(i, mHeap))
            return false;
    }
    return true;
}

AutoPlacementFlowRes* AutoPlacementFlowMgr::getResource1(int idx) {
    if (idx >= mFlowArray.size())
        return nullptr;
    return &mFlowArray[idx];
}

AutoPlacementFlowRes* AutoPlacementFlowMgr::getResource2(int idx) {
    if (idx >= mFlowNearArray.size())
        return nullptr;
    return &mFlowNearArray[idx];
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

void AutoPlacementFlowRes::start(AutoPlacement* placement, const char* unit_name,
                                 sead::TypedBitFlag<ActorSpawnInfo::SpawnLocation>* a3) {
    this->unit_name = unit_name;
    _10a = a3->getDirect();
    this->placement = placement;
    if (flowchart_ctx.GetObjIdx() != -1 && flowchart_ctx.GetActiveEntryPointIdx() != -1)
        flowchart_ctx.Start(nullptr);
}


// 0x7100653788 (CSV apQueryPlayerRideHorse): the AutoPlacement flow query handler that asks whether
// the player is riding a horse. -1 without a player; otherwise 1 when riding, else bit 17 of the
// player's _cec (the fallback state of isRidingHorse).
// NON_MATCHING: lib's BitFlag::isOnBit does `mBits & makeMask(bit)` (a word load + ubfx 17); the
// original narrows to `ldrb [0xcee]` + `ubfx 1`, i.e. its isOnBit is a shift-based test.
s32 apQueryPlayerRideHorse() {
    act::PlayerInfo* info = act::PlayerInfo::instance();
    if (!info)
        return -1;
    act::PlayerBase* player = info->getPlayer();
    if (!player)
        return -1;
    if (player->isRidingHorse())
        return 1;
    return player->_cec.isOnBit(17);
}

namespace {

PlacementThing* getPlacementThing(const evfl::QueryArg& arg) {
    auto* flow = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data);
    return flow->placement->getCurrentThingMaybe();
}

}  // namespace

// The angle is in degrees; the original multiplies by pi / 180 before the sine.
s32 apQueryGroundNorm(const evfl::QueryArg& arg) {
    f32 angle;
    if (!arg.param_accessor.FindFloat(&angle, "Angle"))
        return -1;
    return getPlacementThing(arg)->getFloorNormalYMaybe() >
           sead::Mathf::sin(angle * 0.017453292f);
}

// NON_MATCHING: the manager load is scheduled before the placement lookup (one instruction order).
s32 apQueryTreeRate(const evfl::QueryArg& arg) {
    f32 rate;
    if (!arg.param_accessor.FindFloat(&rate, "Rate"))
        return -1;
    const sead::Vector3f& pos = getPlacementThing(arg)->getQueryPositionMaybe();
    return rate <=
           sub_7100659298(pos, AutoPlacementMgr::instance()->getTreeRateStatsMaybe());
}

s32 apQueryPosHeight(const evfl::QueryArg& arg) {
    f32 height;
    if (!arg.param_accessor.FindFloat(&height, "Height"))
        return -1;
    return height <= getPlacementThing(arg)->getQueryPositionMaybe().y;
}

// NON_MATCHING: the original keeps the placement in a callee-saved register and reloads mX after the call.
s32 apQueryWaterDepth(const evfl::QueryArg& arg) {
    f32 depth;
    if (!arg.param_accessor.FindFloat(&depth, "Depth"))
        return -1;
    PlacementThing* thing = getPlacementThing(arg);
    const f32 ground = AutoPlacementMgr::instance()->sub_7100659230(thing->getQueryPositionMaybe());
    const bool below_ground = depth < ground;
    const bool below_water = depth < thing->getWaterHeightMaybe();
    return below_ground || below_water ? (below_ground && below_water ? 1 : -1) : 0;
}

// NON_MATCHING: the manager load is scheduled before the placement lookup (one instruction order).
s32 apQueryRouteDistance(const evfl::QueryArg& arg) {
    f32 distance;
    if (!arg.param_accessor.FindFloat(&distance, "Distance"))
        return -1;
    const sead::Vector3f& pos = getPlacementThing(arg)->getQueryPositionMaybe();
    return distance <=
           sub_7100659298(pos, AutoPlacementMgr::instance()->getRouteDistanceStatsMaybe());
}

s32 apQueryGrassHeight(const evfl::QueryArg& arg) {
    f32 height;
    if (!arg.param_accessor.FindFloat(&height, "Height"))
        return -1;
    ksys::tera::Terrain* terrain = ksys::tera::Terrain::instance();
    if (!terrain)
        return -1;
    const sead::Vector3f& pos = getPlacementThing(arg)->getQueryPositionMaybe();
    const sead::Vector2f xz(pos.x, pos.z);
    f32 grass;
    if (terrain->sub_710114DE58()->sub_71011516D0(&grass, &xz) != 2)
        return -1;
    return height <= grass;
}

// NON_MATCHING: the original computes the test flag once and reuses it for the return value.
s32 apQueryWaterSurface(const evfl::QueryArg& arg) {
    PlacementThing* thing = getPlacementThing(arg);
    const bool water = thing->getWaterHeightMaybe() > 0.0f;
    if (water)
        thing->setUnderwaterMaybe();
    return water;
}

// NON_MATCHING: the original loads the placement before the manager (argument evaluation order).
s32 apQueryWaterDistance(const evfl::QueryArg& arg) {
    f32 distance;
    if (!arg.param_accessor.FindFloat(&distance, "Distance"))
        return -1;
    const sead::Vector3f& pos = getPlacementThing(arg)->getQueryPositionMaybe();
    return distance <= AutoPlacementMgr::instance()->sub_71006592E8(pos);
}

s32 apQueryUnknown(const evfl::QueryArg& arg) {
    return 0;
}

}  // namespace uking
