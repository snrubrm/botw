#include "Game/AI/Action/actionSceneSoundKillDuckingAction.h"

#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SceneSoundKillDuckingAction::SceneSoundKillDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundKillDuckingAction::~SceneSoundKillDuckingAction() = default;

bool SceneSoundKillDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundKillDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

bool SceneSoundKillDuckingAction::oneShot_() {
    ksys::snd::SoundMgr::instance()->mDuckingMgr->sub_7101042DB4(mDuckerType_d, true);
    return true;
}

}  // namespace uking::action
