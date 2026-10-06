#include "Game/AI/Action/actionSceneSoundSetEndProcAction.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

SceneSoundSetEndProcAction::SceneSoundSetEndProcAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SceneSoundSetEndProcAction::~SceneSoundSetEndProcAction() = default;

bool SceneSoundSetEndProcAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SceneSoundSetEndProcAction::loadParams_() {
    getDynamicParam(&mCtrlType_d, "CtrlType");
}

bool SceneSoundSetEndProcAction::oneShot_() {
    if (mCtrlType_d == "SkipAll") {
        ksys::snd::SoundMgr::instance()->_98->_5d8 = true;
        return true;
    }
    return false;
}

}  // namespace uking::action
