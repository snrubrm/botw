#include "Game/AI/Action/actionPlayerParashawlGlide.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "Game/gameSceneSubsys14.h"
#include "Game/gameUnk_710246d058.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/Timer.h"

namespace uking::action {

PlayerParashawlGlide::PlayerParashawlGlide(const InitArg& arg) : PlayerGlide(arg) {}

void PlayerParashawlGlide::enter_(ksys::act::ai::InlineParamPack* params) {
    const u32 flags = static_cast<ksys::act::Player*>(mActor)->_cf0.getDirect();
    PlayerGlide::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x200);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20000);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x40000);
    static_cast<ksys::act::Player*>(mActor)->x_24(-1.0f);
    if (flags & 0x800000) {
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800000);
        static_cast<ksys::act::Player*>(mActor)->x_7();
        static_cast<ksys::act::Player*>(mActor)->_c40.reset(0x8);
    } else {
        static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
        static_cast<ksys::act::Player*>(mActor)->sub_710088A854();
    }
    if (mActor->getASList()->x_1(0, 0) != "ParashawlGlide")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("ParaEquipOn", true,
                                                                           -1.0f);
    _1c = true;

    auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
    const u32 had_flag = flags & 0x800000;
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
        actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
        sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x8000024), nullptr);
    }
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1844;
    timer = ksys::Timer(*mNoEnergyTime_s, *mNoEnergyTime_s);

    if (ksys::gdt::getFlag_ParasailStaminaRecover(false) ||
        GameSceneSubsys14::instance()->sub_7100904F34()) {
        static_cast<ksys::act::Player*>(mActor)->sub_710084AE78();
    } else if (static_cast<ksys::act::Player*>(mActor)->x_44()) {
        static_cast<ksys::act::Player*>(mActor)->_c44.set(0x8);
    }
    _a0 = false;
    if (!had_flag)
        static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->sub_7100EB56B4(false);
}

// NON_MATCHING: the original copies the velocity element-wise onto itself (x / z / y loads and stores back to
// the same stack slot) before the `y > 0` test; no source form found.
void PlayerParashawlGlide::leave_() {
    PlayerGlide::leave_();
    auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
        actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    if (static_cast<ksys::act::Player*>(mActor)->_cf0.isOnBit(23))
        static_cast<ksys::act::Player*>(mActor)->sub_710088A854();
    if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(14) ||
        static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround()) {
        static_cast<ksys::act::Player*>(mActor)->x_23("ParaEquipOff", false, -1.0f);
    }
    if (auto* life = static_cast<ksys::act::Player*>(mActor)->getLife()) {
        if (*life <= 0)
            static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Fall", true, -1.0f);
    }
    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        if (velocity.y > 0) {
            velocity.y = 0;
            controller->sub_7100F5F6FC(velocity);
        }
    }
    static_cast<ksys::act::Player*>(mActor)->getAttachedTargetActor2()->sub_7100EB56E8();
}

void PlayerParashawlGlide::loadParams_() {
    PlayerGlide::loadParams_();
    getStaticParam(&mEnergyGlide_s, "EnergyGlide");
    getStaticParam(&mNoEnergyTime_s, "NoEnergyTime");
}

void PlayerParashawlGlide::calc_() {
    PlayerGlide::calc_();
}

bool PlayerParashawlGlide::isChangeable() const {
    return _1c;
}

bool PlayerParashawlGlide::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround() || _a0;
}

}  // namespace uking::action
