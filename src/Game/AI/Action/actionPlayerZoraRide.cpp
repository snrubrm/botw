#include "Game/AI/Action/actionPlayerZoraRide.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerZoraRide::PlayerZoraRide(const InitArg& arg) : PlayerAction(arg) {
    _44.reset(0.0f);
}

PlayerZoraRide::~PlayerZoraRide() = default;

void PlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerZoraRide::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_14c0 = false;
    static_cast<ksys::act::Player*>(mActor)->_c48.resetBit(8);
    sub_71005D79AC(mActor, static_cast<ksys::act::Player*>(mActor)->playerWeapons_return0(), act::Unk_71002edaec(1));
}

void PlayerZoraRide::loadParams_() {
    getStaticParam(&mLowerAngleWaitTime_s, "LowerAngleWaitTime");
    getStaticParam(&mAimAngleAddApplyAngle_s, "AimAngleAddApplyAngle");
    getStaticParam(&mAimAngleAdd_s, "AimAngleAdd");
    getStaticParam(&mAimAngleAddApplySpeed_s, "AimAngleAddApplySpeed");
}

void PlayerZoraRide::calc_() {
    PlayerAction::calc_();
}

bool PlayerZoraRide::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
