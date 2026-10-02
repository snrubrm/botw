#include "Game/AI/Action/actionStorePlayerPosAndRotate.h"
#include <cmath>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

StorePlayerPosAndRotate::StorePlayerPosAndRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StorePlayerPosAndRotate::~StorePlayerPosAndRotate() = default;

bool StorePlayerPosAndRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StorePlayerPosAndRotate::loadParams_() {
    getDynamicParam(&mGameDataVec3fPlayerPos_d, "GameDataVec3fPlayerPos");
    getDynamicParam(&mGameDataFloatPlayerDirectionY_d, "GameDataFloatPlayerDirectionY");
}

// NON_MATCHING: the original calls atan2 before loading the gdt::Manager instance; regalloc
bool StorePlayerPosAndRotate::oneShot_() {
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    bool ok = false;
    if (player.hasProc()) {
        sead::Vector3f pos;
        player.getActorMtx().getTranslation(pos);
        ok = ksys::gdt::Manager::instance()->setVec3f(pos, mGameDataVec3fPlayerPos_d);
        const auto& mtx = player.getActorMtx();
        ok &= ksys::gdt::Manager::instance()->setF32(std::atan2(mtx(0, 2), mtx(2, 2)),
                                                      mGameDataFloatPlayerDirectionY_d);
    }
    return ok;
}

}  // namespace uking::action
