#include "Game/AI/Action/actionInitPouchForQuest.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

InitPouchForQuest::InitPouchForQuest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InitPouchForQuest::~InitPouchForQuest() = default;

bool InitPouchForQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool InitPouchForQuest::oneShot_() {
    ui::sub_7100A9F4C8();
    return ksys::act::ai::Action::oneShot_();
}

void InitPouchForQuest::loadParams_() {}

}  // namespace uking::action
