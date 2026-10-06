#include "Game/AI/Action/actionSceneSoundStopDuckingAction.h"

#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SceneSoundStopDuckingAction::SceneSoundStopDuckingAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundStopDuckingAction::~SceneSoundStopDuckingAction() = default;

bool SceneSoundStopDuckingAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundStopDuckingAction::loadParams_() {
    getDynamicParam(&mDuckerType_d, "DuckerType");
}

bool SceneSoundStopDuckingAction::oneShot_() {
    ksys::snd::SoundMgr::instance()->mDuckingMgr->sub_7101042DB4(mDuckerType_d, false);
    return true;
}

}  // namespace uking::action
