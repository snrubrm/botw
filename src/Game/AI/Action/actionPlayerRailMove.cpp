#include "Game/AI/Action/actionPlayerRailMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Map/mapPlacement18.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::action {

PlayerRailMove::PlayerRailMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

PlayerRailMove::~PlayerRailMove() = default;

void PlayerRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rail = ksys::map::PlacementMgr::instance()->mPlacement18->sub_7100D48744(mRailName_d);
    if (!rail) {
        setFailed();
        return;
    }
    _68.sub_7100EEBAE0(rail, 0.0f);
    _68.x(static_cast<ksys::act::Player*>(mActor)->_20f0 * 0.5f);
    _4c = _68._30.sub_7100EEB370() - static_cast<ksys::act::Player*>(mActor)->_1770;
    PlayerGuidedMove::enter_(params);
}

void PlayerRailMove::leave_() {}

void PlayerRailMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
    getDynamicParam(&mRailName_d, "RailName");
}

void PlayerRailMove::calc_() {
    PlayerGuidedMove::calc_();
}

bool PlayerRailMove::isChangeable() const {
    return false;
}

bool PlayerRailMove::m33(sead::Vector3f* pos) {
    pos->set(_68._30.sub_7100EEB370());
    return true;
}

}  // namespace uking::action
