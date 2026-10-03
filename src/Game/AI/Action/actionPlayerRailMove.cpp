#include "Game/AI/Action/actionPlayerRailMove.h"

namespace uking::action {

PlayerRailMove::PlayerRailMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

PlayerRailMove::~PlayerRailMove() = default;

void PlayerRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
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
    // NON_MATCHING: the original copies the 12 bytes as z then xy (a trivially copyable struct, not
    // sead::Vector3f::operator=), so the out parameter type is probably a plain struct
    *pos = _68._30.sub_7100EEB370();
    return true;
}

}  // namespace uking::action
