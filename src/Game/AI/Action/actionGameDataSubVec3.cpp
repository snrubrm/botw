#include "Game/AI/Action/actionGameDataSubVec3.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

GameDataSubVec3::GameDataSubVec3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GameDataSubVec3::~GameDataSubVec3() = default;

bool GameDataSubVec3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool GameDataSubVec3::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return false;
    }

    auto src = sead::Vector3f::zero;
    auto dst = sead::Vector3f::zero;
    if (gdm->getParam().get().getVec3f(&src, mGameDataVec3fSrcName_d)) {
        if (gdm->getParam().get().getVec3f(&dst, mGameDataVec3fDstName_d)) {
            src.x = src.x - dst.x;
            src.y = src.y - dst.y;
            src.z = src.z - dst.z;
        }
        gdm->setVec3f(src, mGameDataVec3fToName_d);
    }

    return true;
}

void GameDataSubVec3::loadParams_() {
    getDynamicParam(&mGameDataVec3fSrcName_d, "GameDataVec3fSrcName");
    getDynamicParam(&mGameDataVec3fDstName_d, "GameDataVec3fDstName");
    getDynamicParam(&mGameDataVec3fToName_d, "GameDataVec3fToName");
}

}  // namespace uking::action
