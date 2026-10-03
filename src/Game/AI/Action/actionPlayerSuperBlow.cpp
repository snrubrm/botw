#include "Game/AI/Action/actionPlayerSuperBlow.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/gameRumble.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"

namespace uking::action {

PlayerSuperBlow::PlayerSuperBlow(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: stack slot order only (the original allocates `dir` / the x_5() result / the two angle temporaries
// in a different order; same as PlayerLadderToClimb::enter_).
void PlayerSuperBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(31);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(1);
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(13);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 time = *mNoRagdollTime_s;
    player->_1844 = ksys::Timer(time, time);
    static_cast<ksys::act::Player*>(mActor)->_20c8 = *mInitSpeed_s;
    const f32& speed = *mInitSpeed_s;
    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = speed;
    player->_20bc.prev_value = speed;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mJumpHeight_s);
    }
    auto* manager = sub_710072BA90(mActor);
    sead::Vector3f dir{0, 0, 0};
    if (manager)
        manager->m30(&dir);
    const u32 angle = sead::Mathf::atan2Idx(dir.x, dir.z);
    player = static_cast<ksys::act::Player*>(mActor);
    const ksys::util::Unk_7101EC6BAC current = player->x_5();
    static_cast<ksys::act::Player*>(mActor)->_d1c = static_cast<ksys::act::Player*>(mActor)->sub_7100869814(
        ksys::util::angleDiff(angle, current),
        ksys::util::Unk_7101EC6BAC(ksys::util::sUnk_7101EC6BA0 & 0x20000000));
    static_cast<ksys::act::Player*>(mActor)->_1c68 = ksys::util::Unk_7101EC6BAC(angle);
    mActor->getASList()->x_6(9, 0,
                             ksys::util::sub_71011EE4B8(ksys::util::angleDiff(angle, current)) *
                                 ksys::util::sUnk_7101EC6BA4);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("DamageL", true, -1.0f);
    uking::Rumble::instance()->sub_7100897FE4(1, 1);
}

void PlayerSuperBlow::leave_() {}

void PlayerSuperBlow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
    getStaticParam(&mDecSpeed_s, "DecSpeed");
    getStaticParam(&mNoRagdollTime_s, "NoRagdollTime");
}

void PlayerSuperBlow::calc_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_1844.value <= sead::Mathf::epsilon())
        setFinished();
    else
        player->_1844.update();
    static_cast<ksys::act::Player*>(mActor)->_20bc.chase(0.0f, *mDecSpeed_s);
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerSuperBlow::isChangeable() const {
    return false;
}

}  // namespace uking::action
