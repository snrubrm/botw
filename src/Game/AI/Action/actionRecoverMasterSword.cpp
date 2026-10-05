#include "Game/AI/Action/actionRecoverMasterSword.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMasterSword.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

RecoverMasterSword::RecoverMasterSword(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RecoverMasterSword::~RecoverMasterSword() = default;

bool RecoverMasterSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RecoverMasterSword::loadParams_() {}

bool RecoverMasterSword::oneShot_() {
    ui::recoverMasterSword(false, false);
    ksys::act::acc::PlayerOrEnemy player;
    ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &player);
    sendMessage(*player.getMessageTransceiverId(), ksys::MessageType(0x8000023), nullptr);
    ksys::act::ActorConstDataAccess weapon;
    player.getWeapon(&weapon, 0);
    if (weapon.hasProc() && weapon.getGParamList()->getMasterSword()->mIsMasterSword.ref())
        sendMessage(*weapon.getMessageTransceiverId(), ksys::MessageType(0x8000022), nullptr);
    return true;
}

}  // namespace uking::action
