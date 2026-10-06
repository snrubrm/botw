#include "Game/AI/Action/actionPlayerNavMeshMove.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"

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

bool PlayerNavMeshMove::m33(sead::Vector3f* pos) {
    auto* actor = mActor;
    const sead::Vector3f actor_pos = actor->getMtx().getTranslation();
    auto* nav = actor->m45();
    if (!nav)
        return false;
    {
        auto lock = sead::makeScopedLock(nav->_1e0);
        pos->set(nav->_23c);
    }
    const f32 distance = (nav->_194 - actor_pos).length();
    if (pos->length() > distance) {
        const f32 length = pos->length();
        if (length > 0.0f)
            *pos *= distance / length;
    }
    *pos += actor->getMtx().getTranslation();
    return true;
}

}  // namespace uking::action
