#include "Game/AI/Action/actionPlayerNavMeshMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerNavMeshMove::PlayerNavMeshMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

// Out of line in the original (single caller, so it needs noinline here).
[[gnu::noinline]] void PlayerNavMeshMove::sub_71007E8C34(ksys::act::ai::InlineParamPack* params) {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const sead::Vector3f prev = player->_1810;
    if (m33(&player->_1810)) {
        player = static_cast<ksys::act::Player*>(mActor);
        _4c = player->_1810 - player->_1770;
        if (prev.x != player->_1810.x || prev.y != player->_1810.y || prev.z != player->_1810.z) {
            const f32 value = _4c.length() / 0.05f + 150.0f;
            player->_185c = ksys::Timer(value, value);
        }
    }
}

void PlayerNavMeshMove::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71007E8C34(params);
    PlayerGuidedMove::enter_(params);
}

void PlayerNavMeshMove::leave_() {}

void PlayerNavMeshMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
}

void PlayerNavMeshMove::calc_() {
    PlayerGuidedMove::calc_();
}

bool PlayerNavMeshMove::isChangeable() const {
    return false;
}

}  // namespace uking::action
