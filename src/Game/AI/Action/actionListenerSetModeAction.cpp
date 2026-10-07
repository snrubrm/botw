#include "Game/AI/Action/actionListenerSetModeAction.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

ListenerSetModeAction::ListenerSetModeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ListenerSetModeAction::~ListenerSetModeAction() = default;

bool ListenerSetModeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ListenerSetModeAction::oneShot_() {
    s32 mode;
    if (mMode_d == "Gyro")
        mode = 5;
    else if (mMode_d == "EvtBack")
        mode = 6;
    else if (mMode_d == "Normal")
        mode = 0;
    else
        return false;

    ksys::snd::SoundMgr::instance()->_58->_78 = mode;
    return true;
}

void ListenerSetModeAction::loadParams_() {
    getDynamicParam(&mMode_d, "Mode");
}

}  // namespace uking::action
