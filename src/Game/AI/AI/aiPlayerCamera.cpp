#include "Game/AI/AI/aiPlayerCamera.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameRuneMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::ai {

PlayerCamera::PlayerCamera(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerCamera::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx);
    else
        changeChild("通常");
}

void PlayerCamera::calc_() {
    if (handlePendingChildChange())
        return;

    if (isCurrentChild("通常")) {
        if (ui::sub_7100A9C15C()) {
            changeChild("自撮り");
            return;
        }
    }
    if (isCurrentChild("自撮り")) {
        if (!ui::sub_7100A9C15C()) {
            static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
            changeChild("通常");
        }
    }
}

bool PlayerCamera::isFinished() const {
    if (!static_cast<ksys::act::Player*>(mActor)->runeMgrCheckIsCameraSelected() && !ui::return0())
        return true;
    if (static_cast<ksys::act::Player*>(mActor)->sub_710084A6B8() ||
        static_cast<ksys::act::Player*>(mActor)->x_21()) {
        return true;
    }
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

void PlayerCamera::leave_() {
    RuneMgr::instance()->setHandled();
}

}  // namespace uking::ai
