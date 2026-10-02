#include "Game/AI/AI/aiPlayerDead.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::ai {

PlayerDead::PlayerDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerDead::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c48.reset(1);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_10);
    if (auto* controller = mActor->getCharacterController())
        controller->mFlags.set(8);
}

void PlayerDead::loadParams_() {
    getStaticParam(&mRumbleType_s, "RumbleType");
    getStaticParam(&mRumblePower_s, "RumblePower");
}

bool PlayerDead::isFinished() const {
    if (isCurrentChild("死亡デモ開始"))
        return false;
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

bool PlayerDead::isChangeable() const {
    if (isCurrentChild("死亡デモ開始"))
        return false;
    return getCurrentChild()->isChangeable();
}

void PlayerDead::calc_() {
    if (isCurrentChild("死亡デモ開始") && mActor->getASList()->x_1(0, 0) == "Dead") {
        static_cast<ksys::act::Player*>(mActor)->sub_7100877BD8();
        static_cast<ksys::act::Player*>(mActor)->actionCommon();
    }
    handlePendingChildChange();
}

}  // namespace uking::ai
