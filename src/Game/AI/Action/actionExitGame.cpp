#include "Game/AI/Action/actionExitGame.h"
#include <cstdlib>
#include <prim/seadSafeString.h>
#include "Game/E3Mgr.h"
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

ExitGame::ExitGame(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExitGame::~ExitGame() = default;

bool ExitGame::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ExitGame::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* e3 = E3Mgr::instance()) {
        if (e3->isRidDemo())
            quick_exit(0);
    }

    bool a2 = true;
    switch (*mShowLogo_d) {
    case 0:
        break;
    case 1:
        a2 = false;
        break;
    default: {
        sead::FixedSafeString<128> flow;
        sead::FixedSafeString<128> entry;
        getActiveEventFlowPath_0(mActor, &flow, &entry);
        sead::FixedSafeString<128> path;
        getActiveEventFlowPath(mActor, &path);
        break;
    }
    }
    createTitleStageBinder(false, a2);
}

void ExitGame::leave_() {
    ksys::act::ai::Action::leave_();
}

void ExitGame::loadParams_() {
    getDynamicParam(&mShowLogo_d, "ShowLogo");
}

void ExitGame::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
