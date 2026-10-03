#include "Game/AI/AI/aiInTerritorySelector.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

InTerritorySelector::InTerritorySelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InTerritorySelector::~InTerritorySelector() = default;

bool InTerritorySelector::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool InTerritorySelector::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

void InTerritorySelector::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_710044B9F0()) {
        changeChild("範囲内", params);
        return;
    }

    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(home_pos, "TargetPos", -1);
    changeChild("範囲外", &pack);
}

// NON_MATCHING: same instructions; the original lays the failure paths out before the success block
bool InTerritorySelector::sub_710044B9F0() {
    sead::Vector3f home_pos;
    mActor->getHomePos(&home_pos);
    const f32 area_sq = *mTerritoryArea_s * *mTerritoryArea_s;
    const auto& pos = mActor->getMtx().getTranslation();
    const f32 dx = home_pos.x - pos.x;
    const f32 dz = home_pos.z - pos.z;
    if (dx * dx + dz * dz <= area_sq) {
        ksys::act::acc::PlayerBase player;
        player.getPlayerFromPlayerInfo();
        if (player.hasProc()) {
            const auto& player_pos = player.getActorMtx().getTranslation();
            const f32 pdx = home_pos.x - player_pos.x;
            const f32 pdz = home_pos.z - player_pos.z;
            if (pdx * pdx + pdz * pdz > area_sq)
                return false;
        }
        return true;
    }
    return false;
}

void InTerritorySelector::calc_() {}

void InTerritorySelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InTerritorySelector::loadParams_() {
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
}

}  // namespace uking::ai
