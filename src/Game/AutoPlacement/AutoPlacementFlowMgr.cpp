#include "Game/AutoPlacement/AutoPlacementFlowMgr.h"
#include <container/seadBuffer.h>
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>
#include <evfl/ResActor.h>
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/System/UIGlue.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/World/worldManager.h"
#include <evfl/ResFlowchart.h>
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

// NON_MATCHING: one load is scheduled before the manager lookup (placement load order).
s32 apQueryTreeRate(const evfl::QueryArg& arg) {
    f32 rate;
    if (!arg.param_accessor.FindFloat(&rate, "Rate"))
        return -1;
    AutoPlacement* placement = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data)->placement;
    const sead::Vector3f& pos = placement->getCurrentThingMaybe()->getQueryPositionMaybe();
    void* const* stats = AutoPlacementMgr::instance()->getTreeRateStatsMaybe();
    return rate <= sub_7100659298(pos, stats);
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

// NON_MATCHING: one load is scheduled before the manager lookup (placement load order).
s32 apQueryRouteDistance(const evfl::QueryArg& arg) {
    f32 distance;
    if (!arg.param_accessor.FindFloat(&distance, "Distance"))
        return -1;
    AutoPlacement* placement = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data)->placement;
    const sead::Vector3f& pos = placement->getCurrentThingMaybe()->getQueryPositionMaybe();
    void* const* stats = AutoPlacementMgr::instance()->getRouteDistanceStatsMaybe();
    return distance <= sub_7100659298(pos, stats);
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

s32 apQueryWaterSurface(const evfl::QueryArg& arg) {
    PlacementThing* thing = getPlacementThing(arg);
    const s32 water = thing->getWaterHeightMaybe() > 0.0f;
    if (water)
        thing->setUnderwaterMaybe();
    return water;
}

s32 apQueryWaterDistance(const evfl::QueryArg& arg) {
    f32 distance;
    if (!arg.param_accessor.FindFloat(&distance, "Distance"))
        return -1;
    AutoPlacement* placement = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data)->placement;
    return distance <=
           AutoPlacementMgr::instance()->sub_71006592E8(
               placement->getCurrentThingMaybe()->getQueryPositionMaybe());
}

s32 apQueryUnknown(const evfl::QueryArg& arg) {
    return 0;
}

// The ground materials the flow queries know about; apQueryGroundMat returns their table index.
// NON_MATCHING: the original compares through sead::SafeString objects whose virtual
// assureTermination calls our sead inlines away (library difference).
static const char* sGroundMatNames[] = {
    "Soil",      "Stone", "Rock",  "Sand", "Metal",      "Grass", "Ivy",  "Wood",
    "Water",     "Snow",  "Ice",   "Lava", "HeavySand",  "Bog",   "HeavySnow",
};

// Returns the index of the current ground material in sGroundMatNames, or -1 if it is unknown.
s32 apQueryGroundMat(const evfl::QueryArg& arg) {
    const char* mat = getPlacementThing(arg)->getCurrentGroundMat();
    for (s32 i = 0; i < 15; ++i) {
        if (sead::SafeString(mat) == sGroundMatNames[i])
            return i;
    }
    return -1;
}

// Returns the kind of the current water sub-material (0 Water, 1 Water_Ice, 2 Water_Hot,
// 3 Water_Poison), or -1 for anything else.
// NON_MATCHING: the original's sead::SafeString comparison calls assureTermination virtually;
// our sead inlines the empty base implementation away (library difference).
s32 apQueryWaterSubMat(const evfl::QueryArg& arg) {
    const char* mat = getPlacementThing(arg)->getCurrentWaterSubMat();
    if (sead::SafeString(mat) == "Water")
        return 0;
    if (sead::SafeString(mat) == "Water_Ice")
        return 1;
    if (sead::SafeString(mat) == "Water_Hot")
        return 2;
    if (sead::SafeString(mat) == "Water_Poison")
        return 3;
    return -1;
}

// Whether the "Label" game-data bool flag is set.
// NON_MATCHING: only the stack slot of the "Label" key temporary differs (the original frame is
// 16 bytes larger).
s32 apQueryCheckGameData(const evfl::QueryArg& arg) {
    ksys::gdt::Manager* mgr = ksys::gdt::Manager::instance();
    if (!mgr)
        return -1;

    ore::StringView label;
    if (!arg.param_accessor.FindString(&label, "Label"))
        return -1;

    bool value = false;
    ksys::gdt::getBoolByNameNoBool2(mgr, &value, label.data());
    return value;
}

// Whether the pouch holds at least "Count" items of the pouch item type "Type".
s32 apQueryCheckPouchItemCount(const evfl::QueryArg& arg) {
    int type;
    int count;
    ore::StringView type_key("Type");
    ore::StringView count_key("Count");
    if (!arg.param_accessor.FindInt(&type, type_key) ||
        !arg.param_accessor.FindInt(&count, count_key))
        return -1;

    u32 value = 0;
    switch (type) {
    case 0:
        value = ui::PauseMenuDataMgr::instance()->_44504;
        break;
    case 1:
        value = ui::PauseMenuDataMgr::instance()->_44508;
        break;
    case 2:
        value = ui::PauseMenuDataMgr::instance()->_4450c;
        break;
    case 3:
        value = ui::PauseMenuDataMgr::instance()->_44514;
        break;
    case 4:
        value = ui::PauseMenuDataMgr::instance()->_44510;
        break;
    default:
        return -1;
    }
    return s32(value) >= count;
}

// Whether the pouch holds at least "Count" items with the name "Actor".
// NON_MATCHING: only the stack slots of the string views and the SafeString temporaries differ
// (the original frame is 16 bytes larger).
s32 apQueryCheckPouchItemCountFromActor(const evfl::QueryArg& arg) {
    ore::StringView actor;
    if (!arg.param_accessor.FindString(&actor, "Actor"))
        return -1;

    int count;
    if (!arg.param_accessor.FindInt(&count, "Count"))
        return -1;

    sead::SafeString name;
    name = actor.data();

    return ksys::ui::getItemValue(name) >= count;
}

// Stores the time types allowed by the running switch event in the placement, then returns the
// current time type.
// NON_MATCHING: the original loads the world manager first and unrolls the mask loop by four;
// ours loads it after the mask and keeps a plain loop.
s32 apQueryCheckTimeType(const evfl::QueryArg& arg) {
    auto* flow = static_cast<AutoPlacementFlowRes*>(arg.actor_user_data);
    AutoPlacement* placement = flow->placement;

    if (placement->mX != &placement->mThing2) {
        const evfl::ResEvent* event = arg.main_event;
        u32 mask = 0;
        for (int i = 0; i < event->num_cases; ++i)
            mask |= 1 << event->cases.Get()[i].value;
        placement->_10 = mask;
    }

    ksys::world::Manager* mgr = ksys::world::Manager::instance();
    if (!mgr)
        return -1;
    return mgr->getTimeMgr()->getTimeType();
}

}  // namespace uking
