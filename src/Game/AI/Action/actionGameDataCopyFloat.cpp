#include "Game/AI/Action/actionGameDataCopyFloat.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataCopyFloat::GameDataCopyFloat(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataCopyFloat::~GameDataCopyFloat() = default;

bool GameDataCopyFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataCopyFloat::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm) {
        f32 value = 0;
        if (gdm->getParam().get().getF32(&value, mGameDataFloatSrcName_d) &&
            gdm->setF32(value, mGameDataFloatDstName_d)) {
            return true;
        }
    }
    setFailed();
    mFlags.set(Flag::Changeable);
    return false;
}

void GameDataCopyFloat::loadParams_() {
    getDynamicParam(&mGameDataFloatSrcName_d, "GameDataFloatSrcName");
    getDynamicParam(&mGameDataFloatDstName_d, "GameDataFloatDstName");
}

}  // namespace uking::action
