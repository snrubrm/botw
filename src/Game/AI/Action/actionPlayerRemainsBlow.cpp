#include "Game/AI/Action/actionPlayerRemainsBlow.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "Game/gameRumble.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/MathUtil.h"
#include <math/seadMathCalcCommon.h>

namespace uking::action {

PlayerRemainsBlow::PlayerRemainsBlow(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: stack slot order only (same as PlayerSuperBlow::enter_: the original allocates the x_5() result first)
void PlayerRemainsBlow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    auto* manager = sub_710072BA90(mActor);
    f32 scale = 1.0f;
    if (manager) {
        sead::Vector3f impulse;
        if (manager->m32(&impulse))
            scale = impulse.length();
    }
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(31);
    static_cast<ksys::act::Player*>(mActor)->_cec.setBit(1);
    static_cast<ksys::act::Player*>(mActor)->_cf4.setBit(25);
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(13);
    static_cast<ksys::act::Player*>(mActor)->_20c8 = scale * *mInitSpeed_s;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const f32 speed = scale * *mInitSpeed_s;
    player->_20bc.value = speed;
    player->_20bc.prev_value = speed;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(scale * *mJumpHeight_s);
    }
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
    static_cast<ksys::act::Player*>(mActor)->_cfc.resetBit(0);
}

void PlayerRemainsBlow::leave_() {}

void PlayerRemainsBlow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mJumpHeight_s, "JumpHeight");
}

void PlayerRemainsBlow::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround())
        setFinished();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerRemainsBlow::isChangeable() const {
    return false;
}

}  // namespace uking::action
