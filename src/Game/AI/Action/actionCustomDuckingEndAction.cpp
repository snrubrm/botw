#include "Game/AI/Action/actionCustomDuckingEndAction.h"

#include "KingSystem/Sound/sndMgr.h"

namespace uking::action {

CustomDuckingEndAction::CustomDuckingEndAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CustomDuckingEndAction::~CustomDuckingEndAction() = default;

bool CustomDuckingEndAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CustomDuckingEndAction::loadParams_() {}

bool CustomDuckingEndAction::oneShot_() {
    ksys::snd::SoundMgr::instance()->_98->sub_710103D094();
    return true;
}

}  // namespace uking::action
