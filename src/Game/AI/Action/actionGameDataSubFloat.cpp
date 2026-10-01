#include "Game/AI/Action/actionGameDataSubFloat.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataSubFloat::GameDataSubFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataSubFloat::~GameDataSubFloat() = default;

bool GameDataSubFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataSubFloat::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return false;
    }
    f32 src = 0;
    f32 dst = 0;
    if (gdm->getParam().get().getF32(&src, mGameDataFloatSrcName_d)) {
        if (gdm->getParam().get().getF32(&dst, mGameDataFloatDstName_d))
            src -= dst;
        gdm->setF32(src, mGameDataFloatToName_d);
    }
    return true;
}

void GameDataSubFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

}  // namespace uking::action
