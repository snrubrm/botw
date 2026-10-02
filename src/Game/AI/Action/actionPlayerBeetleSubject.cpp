#include "Game/AI/Action/actionPlayerBeetleSubject.h"
#include <math/seadMathCalcCommon.h>
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerBeetleSubject::PlayerBeetleSubject(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBeetleSubject::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBeetleSubject::leave_() {
    PlayerAction::leave_();
}

void PlayerBeetleSubject::loadParams_() {
    getStaticParam(&mAimRange_s, "AimRange");
}

void PlayerBeetleSubject::calc_() {
    if (!static_cast<ksys::act::Player*>(mActor)->_17f0) {
        sead::Vector3f dir;
        static_cast<ksys::act::Player*>(mActor)->_1b18.getBase(dir, 2);
        dir.normalize();
        const f32 angle = sead::Mathf::atan2(dir.x, dir.z);
        const f32 target_angle = sead::Mathf::atan2(static_cast<ksys::act::Player*>(mActor)->m244()->x,
                                                       static_cast<ksys::act::Player*>(mActor)->m244()->z);
        if (sead::Mathf::abs(target_angle - angle) < 0.02f) {
            auto* player = static_cast<ksys::act::Player*>(mActor);
            if (!player->_c40.isOnBit(28)) {
                player->_c40.setBit(28);
                mActor->resetConnectedCalcChild(false);
            }
            setFinished();
            return;
        }
        if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(9)) {
            static_cast<ksys::act::Player*>(mActor)->x_33();
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 1;
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerBeetleSubject::isChangeable() const {
    return false;
}

}  // namespace uking::action
