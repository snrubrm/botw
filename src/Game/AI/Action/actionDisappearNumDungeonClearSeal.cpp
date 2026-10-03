#include "Game/AI/Action/actionDisappearNumDungeonClearSeal.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

DisappearNumDungeonClearSeal::DisappearNumDungeonClearSeal(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DisappearNumDungeonClearSeal::~DisappearNumDungeonClearSeal() = default;

bool DisappearNumDungeonClearSeal::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DisappearNumDungeonClearSeal::oneShot_() {
    return ui::sub_7100A97498();
}

void DisappearNumDungeonClearSeal::loadParams_() {}

}  // namespace uking::action
