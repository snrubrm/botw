#include "Game/AI/Action/actionListenerFixPositionAction.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

ListenerFixPositionAction::ListenerFixPositionAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ListenerFixPositionAction::~ListenerFixPositionAction() = default;

bool ListenerFixPositionAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ListenerFixPositionAction::oneShot_() {
    auto* poser = ksys::snd::SoundMgr::instance()->_58;
    if (mFixType_d == "Fix") {
        poser->_70 = false;
        poser->_74 = 0;
    } else {
        poser->sub_7101055538(0);
    }
    return true;
}

void ListenerFixPositionAction::loadParams_() {
    getDynamicParam(&mFixType_d, "FixType");
}

}  // namespace uking::action
