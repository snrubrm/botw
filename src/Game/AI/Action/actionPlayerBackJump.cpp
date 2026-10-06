#include "Game/AI/Action/actionPlayerBackJump.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

bool sub_71007D86B4(ksys::act::Player* player) {
    return player->getASList()->x_1(1, 1) == "HorseCall" || player->getASList()->x_1(1, 1) == "CallComeon" ||
           player->getASList()->x_1(1, 1) == "CallStay";
}

namespace uking::action {

PlayerBackJump::PlayerBackJump(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: register allocation only (the original keeps the speed pointer in x9 and mActor in x8 and hoists a
// `mov w2, wzr`).
void PlayerBackJump::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x100000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x1000000);
    static_cast<ksys::act::Player*>(mActor)->_c50.setBit(4);
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x100);
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x200);
    if (static_cast<ksys::act::Player*>(mActor)->sub_7100892098())
        static_cast<ksys::act::Player*>(mActor)->_c44.set(0x1000000);
    static_cast<ksys::act::Player*>(mActor)->_d1c = 1;
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EF08(true);
        controller->sub_7100F62B70(*mBJHeight_s *
                                   static_cast<ksys::act::Player*>(mActor)->getStatusEffectSpeed());
    }
    const f32* speed = mBJSpeedF_s;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = *speed;
    player->_20bc.prev_value = *speed;
    mActor->getASList()->x_6(9, 0, 180.0f);
    static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("BackJump", true, -1.0f);
    // C++14 evaluation order: the original evaluates the destination first
    static_cast<ksys::act::Player*>(mActor)->_1844.operator=(ksys::Timer(*mJustAvoidTime_s, *mJustAvoidTime_s));
    static_cast<ksys::act::Player*>(mActor)->_1850.operator=(ksys::Timer(*mForceSlowTime_s, *mForceSlowTime_s));
    static_cast<ksys::act::Player*>(mActor)->_185c.operator=(ksys::Timer(*mMySlowStartFrame_s, *mMySlowStartFrame_s));
    static_cast<ksys::act::Player*>(mActor)->_1d10.operator=(ksys::Timer(*mNoDamageTime_s, *mNoDamageTime_s));
    player = static_cast<ksys::act::Player*>(mActor);
    const u32 reversed = player->x_5().value ^ 0x80000000u;
    static_cast<ksys::act::Player*>(mActor)->_1c68.value = ksys::util::sUnk_7101EC6BA0 & reversed;
    static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    static_cast<ksys::act::Player*>(mActor)->sub_7100888278();
    if (sub_71007D86B4(static_cast<ksys::act::Player*>(mActor)))
        static_cast<ksys::act::Player*>(mActor)->x_18(true);
    static_cast<ksys::act::Player*>(mActor)->sub_71008692F8();
    static_cast<ksys::act::Player*>(mActor)->_1ec0 = ksys::Timer(4.0f, 4.0f, -1.0f);
}

void PlayerBackJump::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x10000);
    static_cast<ksys::act::Player*>(mActor)->_c4c.reset(0x100);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x1000000);
    static_cast<ksys::act::Player*>(mActor)->_1d70 = ksys::Timer(0, 0);
    if (auto* manager = sead::DynamicCast<uking::dmg::DamageManager>(mActor->getDamageMgr()))
        manager->_210 &= ~0x24c;
    static_cast<ksys::act::Player*>(mActor)->sub_710086952C();
}

void PlayerBackJump::loadParams_() {
    getStaticParam(&mBJSpeedF_s, "BJSpeedF");
    getStaticParam(&mBJHeight_s, "BJHeight");
    getStaticParam(&mNoDamageTime_s, "NoDamageTime");
    getStaticParam(&mJustAvoidTime_s, "JustAvoidTime");
    getStaticParam(&mForceSlowTime_s, "ForceSlowTime");
    getStaticParam(&mMySlowStartFrame_s, "MySlowStartFrame");
    getDynamicParam(&mEnableSwordInput_d, "EnableSwordInput");
}

void PlayerBackJump::calc_() {
    PlayerAction::calc_();
}

bool PlayerBackJump::isChangeable() const {
    return true;
}

bool PlayerBackJump::isFinished() const {
    if (!static_cast<const ksys::act::Player*>(mActor)->isSurfingOnGround())
        return false;
    return sub_71007D8358();
}

bool PlayerBackJump::sub_71007D8358() const {
    if (mActor->getASList()->x_4(0, 0))
        return true;
    if (mActor->getASList()->x(2, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true))
        return true;
    return mActor->getASList()->x_1(0, 0) != "BackJump";
}

}  // namespace uking::action
