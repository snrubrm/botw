#include "Game/AI/Action/actionGameDataSubInt.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataSubInt::GameDataSubInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataSubInt::~GameDataSubInt() = default;

bool GameDataSubInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataSubInt::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return false;
    }
    s32 src = 0;
    s32 dst = 0;
    if (gdm->getParam().get().getS32(&src, mGameDataIntSrcName_d)) {
        if (gdm->getParam().get().getS32(&dst, mGameDataIntDstName_d))
            src -= dst;
        gdm->setS32(src, mGameDataIntToName_d);
    }
    return true;
}

void GameDataSubInt::loadParams_() {
    getDynamicParam(&mGameDataIntSrcName_d, "GameDataIntSrcName");
    getDynamicParam(&mGameDataIntDstName_d, "GameDataIntDstName");
    getDynamicParam(&mGameDataIntToName_d, "GameDataIntToName");
}

}  // namespace uking::action
