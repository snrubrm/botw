#include "Game/AI/Action/actionPlayerUpdateEquip.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/Actor/actPlayerCreateMgr.h"

namespace uking::action {

PlayerUpdateEquip::PlayerUpdateEquip(const InitArg& arg) : PlayerAction(arg) {}

PlayerUpdateEquip::~PlayerUpdateEquip() = default;

bool PlayerUpdateEquip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUpdateEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
}

void PlayerUpdateEquip::leave_() {}

void PlayerUpdateEquip::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (auto* mgr = act::CreatePlayerEquipActorMgr::instance()) {
        if (mgr->areAllWeaponActorsReady()) {
            static_cast<ksys::act::Player*>(mActor)->m362();
            setFinished();
        }
    }
}

bool PlayerUpdateEquip::isChangeable() const {
    return false;
}

}  // namespace uking::action
