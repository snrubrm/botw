#include "Game/AI/Action/actionSceneSoundSetStartProcAction.h"
#include "KingSystem/Sound/sndMgr.h"

namespace uking::action {

SceneSoundSetStartProcAction::SceneSoundSetStartProcAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundSetStartProcAction::~SceneSoundSetStartProcAction() = default;

bool SceneSoundSetStartProcAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundSetStartProcAction::loadParams_() {
    getDynamicParam(&mBgmCtrlType_d, "BgmCtrlType");
    getDynamicParam(&mSeCtrlType_d, "SeCtrlType");
}

// NON_MATCHING: same instructions and control flow; the original materialises each match value (`orr w20, wzr, #N`)
// before the string compare loop, ours in the loop-exit edge blocks.
bool SceneSoundSetStartProcAction::oneShot_() {
    int bgm_type;
    if (mBgmCtrlType_d == "Mute")
        bgm_type = 8;
    else if (mBgmCtrlType_d == "StopWithFade")
        bgm_type = 4;
    else if (mBgmCtrlType_d == "StopWithShortFade")
        bgm_type = 5;
    else if (mBgmCtrlType_d == "Stop")
        bgm_type = 3;
    else if (mBgmCtrlType_d == "None")
        bgm_type = 0;
    else
        bgm_type = 6;

    int se_type;
    if (mSeCtrlType_d == "WorldMute")
        se_type = 1;
    else if (mSeCtrlType_d == "None")
        se_type = 0;
    else
        se_type = 3;

    auto* ctrl = ksys::snd::SoundMgr::instance()->_98;
    if (ctrl->_5cc)
        ctrl->sub_710103CFE8(bgm_type, se_type);
    else
        ctrl->sub_710103BB00(bgm_type, se_type);
    return true;
}

}  // namespace uking::action
