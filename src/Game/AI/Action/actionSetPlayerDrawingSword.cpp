#include "Game/AI/Action/actionSetPlayerDrawingSword.h"

#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Sound/sndUnk_7102502138.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"

namespace uking::action {

SetPlayerDrawingSword::SetPlayerDrawingSword(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetPlayerDrawingSword::~SetPlayerDrawingSword() = default;

bool SetPlayerDrawingSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetPlayerDrawingSword::loadParams_() {}

bool SetPlayerDrawingSword::oneShot_() {
    if (auto* player = sead::DynamicCast<ksys::act::Player>(mActor)) {
        player->getWeapons()->mWeapons[0]._10 = false;
        ksys::snd::Unk_7102502138::instance()->sub_710103B41C(false);
    }
    return true;
}

}  // namespace uking::action
