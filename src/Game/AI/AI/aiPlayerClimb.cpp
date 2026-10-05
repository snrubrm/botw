#include "Game/AI/AI/aiPlayerClimb.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::ai {

PlayerClimb::PlayerClimb(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerClimb::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the two animation-value stores reload the actor separately.
void PlayerClimb::enter_(ksys::act::ai::InlineParamPack* params) {
    using Player = ksys::act::Player;
    static_cast<Player*>(mActor)->_c40.reset(2);
    static_cast<Player*>(mActor)->_c40.reset(0x400000);
    static_cast<Player*>(mActor)->x_8(false, false);
    static_cast<Player*>(mActor)->_20bc.value = 0.0f;
    static_cast<Player*>(mActor)->_20bc.prev_value = 0.0f;
    if (hasPendingChildChange())
        changeChild(mPendingChildIdx, nullptr);
    else
        sub_7100829AA0();
}

void PlayerClimb::leave_() {
    using Player = ksys::act::Player;
    static_cast<Player*>(mActor)->_c40.reset(2);
    static_cast<Player*>(mActor)->_2158 = static_cast<Player*>(mActor)->_1770.y;
    if (static_cast<Player*>(mActor)->_20bc.value == 0.0f)
        static_cast<Player*>(mActor)->_1c68 = static_cast<Player*>(mActor)->x_5();
    static_cast<Player*>(mActor)->_1dd0 = ksys::Timer(*mNoClimbTime_s, *mNoClimbTime_s);
    if (static_cast<Player*>(mActor)->_c48.isOnBit(19))
        static_cast<Player*>(mActor)->switchToAnimSequenceMaybe("Fall", true, -1.0f);
}

void PlayerClimb::loadParams_() {
    getStaticParam(&mNoClimbTime_s, "NoClimbTime");
}

bool PlayerClimb::isFailed() const {
    if (getCurrentChild()->isFailed()) {
        if (isCurrentChild("壁登り"))
            return true;
    }
    return false;
}

bool PlayerClimb::isFinished() const {
    if (getCurrentChild()->isFinished()) {
        if (isCurrentChild("壁登り"))
            return true;
    }
    return false;
}

}  // namespace uking::ai
