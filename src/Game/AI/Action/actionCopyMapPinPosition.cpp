#include "Game/AI/Action/actionCopyMapPinPosition.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

CopyMapPinPosition::CopyMapPinPosition(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CopyMapPinPosition::~CopyMapPinPosition() = default;

bool CopyMapPinPosition::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool CopyMapPinPosition::oneShot_() {
    auto* pin = ui::UiSubsys1::instance()->sub_71009644E8(*mPinColorIdx_d);
    ksys::gdt::Manager::instance()->setVec3f(pin->_28, mGameDataVec3_d);
    return true;
}

void CopyMapPinPosition::loadParams_() {
    getDynamicParam(&mPinColorIdx_d, "PinColorIdx");
    getDynamicParam(&mGameDataVec3_d, "GameDataVec3");
}

}  // namespace uking::action
