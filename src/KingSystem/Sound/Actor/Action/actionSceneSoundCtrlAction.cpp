#include "KingSystem/Sound/Actor/Action/actionSceneSoundCtrlAction.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SceneSoundCtrlAction::SceneSoundCtrlAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SceneSoundCtrlAction::~SceneSoundCtrlAction() = default;

bool SceneSoundCtrlAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundCtrlAction::loadParams_() {
    getDynamicParam(&mBgmCtrlType_d, "BgmCtrlType");
    getDynamicParam(&mSeCtrlType_d, "SeCtrlType");
}

}  // namespace ksys::snd
