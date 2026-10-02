#include "Game/AI/Action/actionPlayerUnbindSheikPad.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerUnbindSheikPad::PlayerUnbindSheikPad(const InitArg& arg) : PlayerAction(arg) {}

PlayerUnbindSheikPad::~PlayerUnbindSheikPad() = default;

bool PlayerUnbindSheikPad::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUnbindSheikPad::loadParams_() {}

bool PlayerUnbindSheikPad::oneShot_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x8000);
    return true;
}

}  // namespace uking::action
