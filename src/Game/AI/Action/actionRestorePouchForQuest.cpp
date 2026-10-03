#include "Game/AI/Action/actionRestorePouchForQuest.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

RestorePouchForQuest::RestorePouchForQuest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RestorePouchForQuest::~RestorePouchForQuest() = default;

bool RestorePouchForQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool RestorePouchForQuest::oneShot_() {
    ui::sub_7100A9F4E0();
    return ksys::act::ai::Action::oneShot_();
}

void RestorePouchForQuest::loadParams_() {}

}  // namespace uking::action
