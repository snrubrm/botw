#include "Game/AI/Action/actionWarpPlayer.h"
#include "Game/gameSceneMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"

namespace uking::action {

WarpPlayer::WarpPlayer(const InitArg& arg) : WarpPlayerBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
WarpPlayer::~WarpPlayer() {
    ;
}

bool WarpPlayer::init_(sead::Heap* heap) {
    return WarpPlayerBase::init_(heap);
}

void WarpPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    WarpPlayerBase::enter_(params);
}

void WarpPlayer::leave_() {
    WarpPlayerBase::leave_();
}

void WarpPlayer::loadParams_() {
    WarpPlayerBase::loadParams_();
    getDynamicParam(&mWarpDestMapName_d, "WarpDestMapName");
    getDynamicParam(&mWarpDestPosName_d, "WarpDestPosName");
}

void WarpPlayer::calc_() {
    WarpPlayerBase::calc_();
}

bool WarpPlayer::m33() {
    return true;
}

// NON_MATCHING: only the order of the two address computations for the getMapPosition arguments (x3 / x4) differs.
void WarpPlayer::m32() {
    auto* mgr = SceneMgr::instance();
    if (!mgr)
        return;
    sead::Vector3f dest[2];
    if (!mgr->getMapPosition(mWarpDestPosName_d, dest, mgr->getStageName(), mWarpDestMapName_d))
        return;
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    if (!player.hasProc())
        return;
    const sead::Vector3f rotation(0, sead::Mathf::deg2rad(dest[1].y), 0);
    const f32 scale = player.getField418().x;
    sead::Matrix34f mtx;
    mtx.makeSRT(sead::Vector3f(scale, scale, scale), rotation, dest[0]);
    _1c = mtx;
}

}  // namespace uking::action
