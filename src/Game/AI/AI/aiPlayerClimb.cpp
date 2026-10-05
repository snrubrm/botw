#include "Game/AI/AI/aiPlayerClimb.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/Utils/MathUtil.h"
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

// NON_MATCHING: string and angle temporaries use different stack slots and store ordering.
void PlayerClimb::calc_() {
    using Player = ksys::act::Player;
    sub_7100829E68();
    if (handlePendingChildChange())
        return;
    sub_7100829F70();
    if (isCurrentChild("壁登り")) {
        if (sub_710082A058())
            return;
        if (static_cast<Player*>(mActor)->get17d0()->controllerCheckPressedMaybe(32))
            static_cast<Player*>(mActor)->sub_71008921A8();
    }
    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && isCurrentChild("武器ペグ")) {
        sub_7100829AA0();
        return;
    }
    if (static_cast<Player*>(mActor)->get17d0()->playerCheckController(2)) {
        auto* player = static_cast<Player*>(mActor);
        if (player->_209c > 0.05f &&
            player->sub_7100869814(
                ksys::util::angleDiff(player->_1c74, player->x_5()),
                ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & 0x20000000)) == 1) {
            static_cast<Player*>(mActor)->_c44.set(0x2000000);
            return;
        }
    }
    static_cast<Player*>(mActor)->_c44.reset(0x2000000);
}

}  // namespace uking::ai
