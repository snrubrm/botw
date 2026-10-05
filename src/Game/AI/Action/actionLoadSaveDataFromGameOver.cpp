#include "Game/AI/Action/actionLoadSaveDataFromGameOver.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameScene.h"

namespace uking::action {

LoadSaveDataFromGameOver::LoadSaveDataFromGameOver(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

LoadSaveDataFromGameOver::~LoadSaveDataFromGameOver() = default;

bool LoadSaveDataFromGameOver::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LoadSaveDataFromGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 mode = ui::sub_7100A968B4();
    if (mode >= 0 && mode <= 5) {
        GameScene::resetStage(mode, false);
    } else {
        setFailed();
        mFlags.set(Flag::Changeable);
    }
}

void LoadSaveDataFromGameOver::leave_() {
    ksys::act::ai::Action::leave_();
}

void LoadSaveDataFromGameOver::loadParams_() {}

void LoadSaveDataFromGameOver::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
