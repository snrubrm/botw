#include "Game/AI/Action/actionSceneSoundNotifyTalkAction.h"
#include "KingSystem/Sound/sndMgr.h"

namespace uking::action {

SceneSoundNotifyTalkAction::SceneSoundNotifyTalkAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundNotifyTalkAction::~SceneSoundNotifyTalkAction() = default;

bool SceneSoundNotifyTalkAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundNotifyTalkAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

bool SceneSoundNotifyTalkAction::oneShot_() {
    if (mCtrlType_d == "BeginTalk") {
        ksys::snd::Unk_710104e5b4::instance()->sub_710104F8E0();
        return true;
    }
    if (mCtrlType_d == "EndTalk") {
        ksys::snd::Unk_710104e5b4::instance()->sub_710104F904();
        return true;
    }
    if (mCtrlType_d == "SkipNotify") {
        ksys::snd::Unk_710104e5b4::instance()->sub_710104F920(true);
        return true;
    }
    return false;
}

}  // namespace uking::action
