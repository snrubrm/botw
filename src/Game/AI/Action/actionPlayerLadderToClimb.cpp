#include "Game/AI/Action/actionPlayerLadderToClimb.h"
#include <cmath>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderToClimb::PlayerLadderToClimb(const InitArg& arg) : PlayerAction(arg) {}

void PlayerLadderToClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderToClimb::leave_() {}

void PlayerLadderToClimb::calc_() {
    const auto& mtx = static_cast<ksys::act::Player*>(mActor)->_1b18;
    sead::Vector3f dir;
    mtx.getBase(dir, 2);
    dir.normalize();
    const f32 angle = std::atan2(dir.x, dir.z);
    sead::Vector3f move = mActor->getASList()->sub_710115D2D4();
    ksys::util::sub_71011EF010(&move, angle);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(move * 30.0f);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c += move * ksys::VFR::instance()->getDeltaFrame();
    m32();
}

bool PlayerLadderToClimb::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
