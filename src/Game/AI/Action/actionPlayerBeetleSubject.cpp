#include "Game/AI/Action/actionPlayerBeetleSubject.h"
#include <math/seadMathCalcCommon.h>
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerBeetleSubject::PlayerBeetleSubject(const InitArg& arg) : PlayerAction(arg) {}

void PlayerBeetleSubject::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(20);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(0);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(28);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(27);
    static_cast<ksys::act::Player*>(mActor)->_cf0.setBit(2);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->x_23("HookshotWait", false, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->sub_71008911F0();
    static_cast<ksys::act::Player*>(mActor)->_17f0 = false;
}

void PlayerBeetleSubject::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x800);
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
