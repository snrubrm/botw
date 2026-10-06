#include "Game/AI/Action/actionPlayerRideJump.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/System/Timer.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerRideJump::PlayerRideJump(const InitArg& arg) : PlayerAction(arg) {}

void PlayerRideJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerRideJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(2);
    if (auto* cc = mActor->getCharacterController()) {
        cc->disableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        cc->sub_7100F5F458(ksys::act::MotionType::_1);
    }
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getHorseLink(), &accessor)) {
        const auto& mtx = accessor.getActorMtx();
        sead::Vector3f dir;
        mtx.getBase(dir, 2);
        dir.normalize();
        static_cast<ksys::act::Player*>(mActor)->sub_7100868220(sead::Mathf::atan2(dir.x, dir.z));
    }
}

void PlayerRideJump::loadParams_() {
    getStaticParam(&mRideOffsetPosY_s, "RideOffsetPosY");
    getStaticParam(&mRideOffsetPosXZ_s, "RideOffsetPosXZ");
    getStaticParam(&mRideJumpTime_s, "RideJumpTime");
}

void PlayerRideJump::sub_710080D120() {
    sead::Vector3f velocity = sead::Vector3f::zero;
    ksys::act::ActorConstDataAccess accessor;
    if (ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getHorseLink(), &accessor))
        velocity = accessor.getVelocity();
    const sead::Vector3f displacement = static_cast<ksys::act::Player*>(mActor)->_181c;
    if (auto* cc = mActor->getCharacterController())
        cc->sub_7100F5F6FC((velocity + displacement) * 30.0f);
}

void PlayerRideJump::calc_() {
    sub_710080D120();
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    if (timer.value <= sead::Mathf::epsilon()) {
        setFinished();
        return;
    }
    timer.update();
}

bool PlayerRideJump::isChangeable() const {
    return false;
}

}  // namespace uking::action
