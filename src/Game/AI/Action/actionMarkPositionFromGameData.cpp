#include "Game/AI/Action/actionMarkPositionFromGameData.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

MarkPositionFromGameData::MarkPositionFromGameData(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

MarkPositionFromGameData::~MarkPositionFromGameData() = default;

bool MarkPositionFromGameData::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MarkPositionFromGameData::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
    getDynamicParam(&mGameDataVec3_d, "GameDataVec3");
}

bool MarkPositionFromGameData::oneShot_() {
    auto* gdm = ksys::gdt::Manager::instance();
    sead::Vector3f pos;
    gdm->getParam().get().getVec3f(&pos, mGameDataVec3_d);
    ui::UiSubsys1::instance()->sub_71009645D0(&pos);
    return true;
}

}  // namespace uking::action
