#include "Game/AI/Action/actionPlayerUnequip.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerUnequip::PlayerUnequip(const InitArg& arg) : PlayerAction(arg) {}

PlayerUnequip::~PlayerUnequip() = default;

bool PlayerUnequip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUnequip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerUnequip::leave_() {
    PlayerAction::leave_();
}

void PlayerUnequip::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (!static_cast<ksys::act::Player*>(mActor)->x_35()) {
        if (static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(7)) {
            static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x80);
            static_cast<ksys::act::Player*>(mActor)->sub_71008550E4();
        }
        setFinished();
    }
    if (static_cast<ksys::act::Player*>(mActor)->isRidingHorse())
        static_cast<ksys::act::Player*>(mActor)->sub_710086FAAC();
}

bool PlayerUnequip::isChangeable() const {
    return false;
}

}  // namespace uking::action
