#include "Game/AI/Action/actionAppearGameOver.h"
#include "Game/UI/euiScreen.h"
#include "Game/UI/uiScreens.h"
#include "Game/gameScene.h"
#include "KingSystem/System/Timer.h"
namespace uking::ui {
// uiScreenFacade / uiMiscFacade (the GameOver screen helpers)
bool sub_7100A967F8();
bool gameOverScreenStuff();
bool sub_7100A96614();
}  // namespace uking::ui

namespace uking::action {

AppearGameOver::AppearGameOver(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearGameOver::~AppearGameOver() = default;

bool AppearGameOver::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    _28 = *mDelay_d;
    _2c = false;
}

void AppearGameOver::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearGameOver::loadParams_() {
    getDynamicParam(&mDelay_d, "Delay");
}

void AppearGameOver::calc_() {
    if (isFinished() || isFailed())
        return;

    if (auto* mgr = eui::ScreenMgr::instance()) {
        if (auto* screen = mgr->getScreen(ui::ScreenId::GameOver)) {
            if (screen->isOpened() && ui::sub_7100A967F8()) {
                setFinished();
                mFlags.set(Flag::Changeable);
            }
            if (!_2c && ui::gameOverScreenStuff()) {
                sub_71007BEB20();
                _2c = true;
            }
            return;
        }
    }

    if (_28 > 0.0f)
        ksys::Timer::update(&_28, -1.0f);
    else
        ui::sub_7100A96614();
}

}  // namespace uking::action
