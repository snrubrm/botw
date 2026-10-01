#include "Game/AI/Action/actionCalcVecLengthToGameData.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

CalcVecLengthToGameData::CalcVecLengthToGameData(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CalcVecLengthToGameData::~CalcVecLengthToGameData() = default;

bool CalcVecLengthToGameData::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool CalcVecLengthToGameData::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return false;
    }

    auto vec = sead::Vector3f::zero;
    if (gdm->getParam().get().getVec3f(&vec, mGameDataVec3fSrcName_d)) {
        if (!mCalcY_d)
            vec.y = 0.0f;
        gdm->setF32(vec.length(), mGameDataFloatToName_d);
    }
    return true;
}

void CalcVecLengthToGameData::loadParams_() {
    getDynamicParam(&mCalcY_d, "CalcY");
    getDynamicParam(&mGameDataVec3fSrcName_d, "GameDataVec3fSrcName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

}  // namespace uking::action
