#include "Game/AI/Action/actionCreateDragonChallengeXLink.h"
#include "Game/gameDragonChallengeMgr.h"

namespace uking::action {

CreateDragonChallengeXLink::CreateDragonChallengeXLink(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateDragonChallengeXLink::~CreateDragonChallengeXLink() = default;

bool CreateDragonChallengeXLink::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateDragonChallengeXLink::loadParams_() {
    getDynamicParam(&mXLinkHandleIndex_d, "XLinkHandleIndex");
}

bool CreateDragonChallengeXLink::oneShot_() {
    if (auto* manager = DragonChallengeMgr::instance()) {
        if (*mXLinkHandleIndex_d != 0)
            manager->x(0, true);
        else
            manager->x_0(0);
        if (*mXLinkHandleIndex_d == 1)
            manager->x_0(1);
        else
            manager->x(1, true);
        if (*mXLinkHandleIndex_d == 2)
            manager->x_0(2);
        else
            manager->x(2, true);
    }
    return true;
}

}  // namespace uking::action
