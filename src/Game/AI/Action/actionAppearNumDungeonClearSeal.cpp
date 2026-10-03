#include "Game/AI/Action/actionAppearNumDungeonClearSeal.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

AppearNumDungeonClearSeal::AppearNumDungeonClearSeal(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AppearNumDungeonClearSeal::~AppearNumDungeonClearSeal() = default;

bool AppearNumDungeonClearSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool AppearNumDungeonClearSeal::oneShot_() {
    return ui::sub_7100A97250(false);
}

void AppearNumDungeonClearSeal::loadParams_() {}

}  // namespace uking::action
