#include "Game/AI/Action/actionGameDataCopyInt.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataCopyInt::GameDataCopyInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataCopyInt::~GameDataCopyInt() = default;

bool GameDataCopyInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataCopyInt::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm) {
        s32 value = 0;
        if (gdm->getParam().get().getS32(&value, mGameDataIntSrcName_d) &&
            gdm->setS32(value, mGameDataIntDstName_d)) {
            return true;
        }
    }
    setFailed();
    mFlags.set(Flag::Changeable);
    return false;
}

void GameDataCopyInt::loadParams_() {
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
}

}  // namespace uking::action
