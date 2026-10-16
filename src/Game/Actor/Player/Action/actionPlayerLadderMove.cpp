#include "Game/Actor/Player/Action/actionPlayerLadderMove.h"
#include "Game/Actor/aiUnk_7101e7c5d0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <cmath>
#include "KingSystem/System/VFR.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

PlayerLadderMove::PlayerLadderMove(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: register allocation (the original loads _d1c into w10, ours into w9)
void PlayerLadderMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_181c = player->_1810;
    player = static_cast<ksys::act::Player*>(mActor);
    const f32 offset = sUnk_7101e7c5d0;
    if (player->_d1c) {
        player->_1810.y = player->_1810.y - offset;
        _28 = true;
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderDown", true, -1.0f);
    } else {
        player->_1810.y = offset + player->_1810.y;
        _28 = false;
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderUp", true, -1.0f);
    }
}

void PlayerLadderMove::leave_() {}

void PlayerLadderMove::loadParams_() {
    getStaticParam(&mDownMoveSpeed_s, "DownMoveSpeed");
}

// NON_MATCHING: scheduling (the original duplicates the -DownMoveSpeed store per branch, keeps the normalized front
// in integer registers and multiplies all three move components before the stores).
void PlayerLadderMove::calc_() {
    sead::Vector3f move{0, 0, 0};
    if (_28) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        if (player->_d1c == 1 && player->_209c > 0.05f) {
            move.y = -*mDownMoveSpeed_s;
        } else {
            const f32 target = player->_22f4.y;
            const f32 current = player->_181c.y;
            const f32 step = sUnk_7101e7c5d0;
            f32 remaining;
            if (target > current) {
                f32 diff = target - current;
                while (diff > step)
                    diff -= step;
                remaining = step - diff;
            } else {
                remaining = current - target;
                while (remaining > step)
                    remaining -= step;
            }
            const f32 speed = *mDownMoveSpeed_s;
            if (remaining > speed) {
                move.y = -speed;
            } else {
                move.y = -remaining;
                _28 = false;
                static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderLand", true,
                                                                                   -1.0f);
                auto* p = static_cast<ksys::act::Player*>(mActor);
                p->_1810.y = p->_181c.y - remaining - step;
            }
        }
    } else if (!(mActor->getASList()->x_1(0, 0) == "LadderWait")) {
        if (mActor->getASList()->x_4(0, 0)) {
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("LadderWait", true,
                                                                               -1.0f);
            auto* player = static_cast<ksys::act::Player*>(mActor);
            player->_181c = player->_1810;
        } else {
            auto* player = static_cast<ksys::act::Player*>(mActor);
            sead::Vector3f front = player->_1b18.getBase(2);
            front.normalize();
            const f32 angle = std::atan2(front.x, front.z);
            move = mActor->getASList()->sub_710115D2D4();
            ksys::util::sub_71011EF010(&move, angle);
        }
    }
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 delta = ksys::VFR::instance()->getDeltaFrame();
    player->_181c.x = delta * move.x + player->_181c.x;
    player->_181c.y = delta * move.y + player->_181c.y;
    player->_181c.z = delta * move.z + player->_181c.z;
    static_cast<ksys::act::Player*>(mActor)->sub_7100892100(static_cast<ksys::act::Player*>(mActor)->_181c);
}

bool PlayerLadderMove::isFinished() const {
    if (mActor->getASList()->x_1(0, 0) == "LadderWait")
        return true;
    if (mActor->getASList()->x_1(0, 0) == "LadderUp")
        return mActor->getASList()->x_4(0, 0);
    return false;
}

bool PlayerLadderMove::isChangeable() const {
    return true;
}

}  // namespace uking::action
