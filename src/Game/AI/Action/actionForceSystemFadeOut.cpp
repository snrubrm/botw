#include "Game/AI/Action/actionForceSystemFadeOut.h"
#include "Game/UI/uiScreens.h"

namespace uking::action {

ForceSystemFadeOut::ForceSystemFadeOut(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceSystemFadeOut::~ForceSystemFadeOut() = default;

bool ForceSystemFadeOut::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceSystemFadeOut::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* screen = sead::DynamicCast<ui::Fade>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
    if (!screen)
        return;
    if (screen->isOpened() || screen->isOpening()) {
        screen->close(-1);
        _1c = true;
    } else {
        _1c = false;
        setFinished();
    }
}

void ForceSystemFadeOut::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceSystemFadeOut::loadParams_() {}

void ForceSystemFadeOut::calc_() {
    if (!_1c) {
        setFinished();
        return;
    }
    auto* screen = sead::DynamicCast<ui::Fade>(
        eui::ScreenMgr::instance()->getScreen(ui::ScreenId::Fade));
    if (screen && screen->isClosed())
        setFinished();
}

}  // namespace uking::action
