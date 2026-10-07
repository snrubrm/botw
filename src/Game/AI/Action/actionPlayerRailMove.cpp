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

// NON_MATCHING: endpoint branch order and position evaluation scheduling differ.
void PlayerRailMove::calc_() {
    if (!_68.sub_7100EEBB74())
        return;
    if (!_68.m3()) {
        const auto& pos = _68._30.sub_7100EEB370();
        const auto& player_pos = static_cast<ksys::act::Player*>(mActor)->_1770;
        const f32 x = pos.x - player_pos.x;
        const f32 z = pos.z - player_pos.z;
        if (sead::Mathf::sqrt(x * x + z * z) < static_cast<ksys::act::Player*>(mActor)->_20f0) {
            _68.x(static_cast<ksys::act::Player*>(mActor)->_20f0 * 0.5f);
            _44 = 0;
        }
    }
    _4c = _68._30.sub_7100EEB370() - static_cast<ksys::act::Player*>(mActor)->_1770;
    if (_68.m3()) {
        const auto diff = _68._30.sub_7100EEB370() - _68._8.sub_7100EEB370();
        if (diff.dot(_4c) < 0) {
            sub_71007E8D28();
            static_cast<ksys::act::Player*>(mActor)->actionCommon();
            return;
        }
    }
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
