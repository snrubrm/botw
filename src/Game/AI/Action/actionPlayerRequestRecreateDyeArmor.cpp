#include "Game/AI/Action/actionPlayerRequestRecreateDyeArmor.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actInfoData.h"

namespace uking::action {

PlayerRequestRecreateDyeArmor::PlayerRequestRecreateDyeArmor(const InitArg& arg)
    : PlayerAction(arg) {}

PlayerRequestRecreateDyeArmor::~PlayerRequestRecreateDyeArmor() = default;

bool PlayerRequestRecreateDyeArmor::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

bool PlayerRequestRecreateDyeArmor::oneShot_() {
    auto* mgr = act::CreatePlayerEquipActorMgr::instance();
    if (!mgr)
        return false;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (!player)
        return false;
    sead::FixedSafeString<64> name;
    for (u8 i = 0; i < 3; ++i) {
        player->getArmorPartName(i, &name);
        if (ksys::act::InfoData::instance()->hasTag(name.cstr(), 0x216a3a63))
            mgr->requestCreateArmor(name, player->m278(i), sead::SafeString::cEmptyString);
    }
    return true;
}

void PlayerRequestRecreateDyeArmor::loadParams_() {}

}  // namespace uking::action
