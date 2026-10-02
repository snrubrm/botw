#include "Game/AI/Action/actionPlayerBindSheikPad.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerBindSheikPad::PlayerBindSheikPad(const InitArg& arg) : PlayerAction(arg) {}

PlayerBindSheikPad::~PlayerBindSheikPad() = default;

bool PlayerBindSheikPad::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerBindSheikPad::loadParams_() {}

bool PlayerBindSheikPad::oneShot_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.set(0x8000);
    return true;
}

}  // namespace uking::action
