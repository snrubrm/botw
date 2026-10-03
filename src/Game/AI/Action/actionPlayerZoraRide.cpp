#include "Game/AI/Action/actionPlayerZoraRide.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/Attention/actAttentionSingleton.h"
#include "Game/Actor/actWeapon.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerZoraRide::PlayerZoraRide(const InitArg& arg) : PlayerAction(arg) {
    _44.reset(0.0f);
}

PlayerZoraRide::~PlayerZoraRide() = default;

// NON_MATCHING: the original has an extra 8-byte stack slot below the accessor and loads the target
// position before the actor's
void PlayerZoraRide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x10000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    if (testRootAiFlag(ksys::act::ai::RootAiFlag::_7)) {
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("RunZoraRide", true, -1.0f);
        return;
    }
    ksys::act::ActorLinkConstDataAccess accessor;
    f32 angle = 0.0f;
    if (ksys::act::Attention::instance()->sub_7100D7482C(&accessor)) {
        const sead::Matrix34f& target_dir = accessor.getActorMtx();
        const f32 target_angle =
            sead::Mathf::rad2deg(sead::Mathf::atan2(target_dir.m[0][2], target_dir.m[2][2]));
        const sead::Matrix34f& target_pos = accessor.getActorMtx();
        const sead::Matrix34f& mtx = mActor->getMtx();
        const f32 current_angle = sead::Mathf::rad2deg(
            sead::Mathf::atan2(mtx.m[0][3] - target_pos.m[0][3], mtx.m[2][3] - target_pos.m[2][3]));
        angle = current_angle - target_angle;
    }
    mActor->getASList()->x_6(9, 0, angle);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("RideonWaitZora", true, -1.0f);
    static_cast<ksys::act::Player*>(mActor)->m308();
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
