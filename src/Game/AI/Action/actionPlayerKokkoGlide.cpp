#include "Game/AI/Action/actionPlayerKokkoGlide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/System/Timer.h"
#include "math/seadMathCalcCommon.h"

namespace uking::action {

PlayerKokkoGlide::PlayerKokkoGlide(const InitArg& arg) : PlayerGlide(arg) {}

void PlayerKokkoGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGlide::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->sub_7100855BB4("ParashawlGlide", false, -1.0f);
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    timer = ksys::Timer(*mNoEnergyTime_s, *mNoEnergyTime_s);
    _98 = false;
    static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->sub_7100EB56B4(true);
}

void PlayerKokkoGlide::leave_() {
    PlayerGlide::leave_();
    static_cast<ksys::act::Player*>(mActor)->x_19(-1.0f);
    static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->sub_7100EB56E8();
}

void PlayerKokkoGlide::loadParams_() {
    PlayerGlide::loadParams_();
    getStaticParam(&mEnergyGlide_s, "EnergyGlide");
    getStaticParam(&mNoEnergyTime_s, "NoEnergyTime");
}

void PlayerKokkoGlide::calc_() {
    PlayerGlide::calc_();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 eps = sead::Mathf::epsilon();
    if (!(player->_1844.value <= eps)) {
        player->_1844.update();
        static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    } else {
        player->x_34(*mEnergyGlide_s, false);
        static_cast<ksys::act::Player*>(mActor)->_cf4.reset(0x80);
    }
    player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1844.value <= eps && player->x_44()) {
        static_cast<ksys::act::Player*>(mActor)->m228(false);
        _98 = true;
    }
}

bool PlayerKokkoGlide::isChangeable() const {
    return true;
}

bool PlayerKokkoGlide::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround() || _98;
}

}  // namespace uking::action
