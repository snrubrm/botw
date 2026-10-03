#include "Game/AI/Action/actionPlayerFall.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerFall::PlayerFall(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: register allocation only (the original keeps the Player pointer of the raycast block in x0)
void PlayerFall::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool a = static_cast<ksys::act::Player*>(mActor)->m186();
    const bool b = static_cast<ksys::act::Player*>(mActor)->m187();
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x2);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000000);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x4);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x20000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x100000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x200000);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    if (mActor->getASList()->x_1(1, 1) == "ParaEquipOff")
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);

    if (a || b) {
        const bool tired = static_cast<ksys::act::Player*>(mActor)->x_44();
        auto& timer = static_cast<ksys::act::Player*>(mActor)->_1dd0;
        const f32 time = *(tired ? mNoClimbTimeTired_s : mNoClimbTime_s);
        timer = ksys::Timer(time, time);
    }

    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(3.0f, 3.0f);
    auto& timer = static_cast<ksys::act::Player*>(mActor)->_1850;
    timer = ksys::Timer(*mNoDispDisableAppTime_s, *mNoDispDisableAppTime_s);
    static_cast<ksys::act::Player*>(mActor)->_185c = ksys::Timer(3.0f, 3.0f);

    if (mActor->getASList()->x_1(0, 0) != "Fall")
        static_cast<ksys::act::Player*>(mActor)->switchToAnimSequenceMaybe("Fall", true, -1.0f);

    const sead::Vector3f& pos = static_cast<ksys::act::Player*>(mActor)->_1770;
    const sead::Vector3f start = pos + sead::Vector3f(0, 0.1f, 0);
    const sead::Vector3f end = pos + sead::Vector3f(0, -10, 0);
    bool no_ground = false;
    if (ksys::act::Player::sub_710086CA68() && !static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(3))
        no_ground = !static_cast<ksys::act::Player*>(mActor)->sub_710087F360(start, end, nullptr, nullptr);
    static_cast<ksys::act::Player*>(mActor)->_17f0 = no_ground;

    if (auto* controller = mActor->getCharacterController()) {
        if (controller->_116 & 4)
            static_cast<ksys::act::Player*>(mActor)->_c50.setBit(19);
    }
    static_cast<ksys::act::Player*>(mActor)->_c40.resetBit(24);

    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void PlayerFall::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x2000000);
    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        auto* player = static_cast<ksys::act::Player*>(mActor);
        auto* proc = player->_2c28.getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
}

void PlayerFall::loadParams_() {
    getStaticParam(&mNoClimbTime_s, "NoClimbTime");
    getStaticParam(&mNoClimbTimeTired_s, "NoClimbTimeTired");
    getStaticParam(&mNoDispDisableAppTime_s, "NoDispDisableAppTime");
}

void PlayerFall::calc_() {
    if (static_cast<ksys::act::Player*>(mActor)->m194()) {
        if (mActor->getASList()->x(84, nullptr, 1, 1, &ksys::as::ASList::Unk2::sub_71011637EC,
                                   true) ||
            mActor->getASList()->x_1(1, 1) != "ParaEquipOff") {
            static_cast<ksys::act::Player*>(mActor)->_cec.reset(0x8000);
            auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
            if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
                actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }

    if (static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(21)) {
        if (static_cast<ksys::act::Player*>(mActor)->_185c.value <= sead::Mathf::epsilon())
            static_cast<ksys::act::Player*>(mActor)->m228(false);
        else
            static_cast<ksys::act::Player*>(mActor)->_185c.update();
    }
    static_cast<ksys::act::Player*>(mActor)->sub_71008931C4();
    if (static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(8) &&
        !static_cast<ksys::act::Player*>(mActor)->_d11) {
        static_cast<ksys::act::Player*>(mActor)->x_37();
    }
    if (static_cast<ksys::act::Player*>(mActor)->_17f0 &&
        !static_cast<ksys::act::Player*>(mActor)->_c44.isOnBit(21) &&
        static_cast<ksys::act::Player*>(mActor)->_1d70.value <= sead::Mathf::epsilon() &&
        !static_cast<ksys::act::Player*>(mActor)->_c50.isOnBit(19)) {
        if (auto* controller = mActor->getCharacterController()) {
            if (!(controller->_116 & 0x10))
                static_cast<ksys::act::Player*>(mActor)->_1cb0 = 9;
        }
    }
    static_cast<ksys::act::Player*>(mActor)->_20bc.chase(0.0f, 0.001f);
    if (static_cast<ksys::act::Player*>(mActor)->_1850.value <= sead::Mathf::epsilon())
        static_cast<ksys::act::Player*>(mActor)->_cf4.reset(0x200000);
    else
        static_cast<ksys::act::Player*>(mActor)->_1850.update();
    if (static_cast<ksys::act::Player*>(mActor)->_d11 && mActor->getConnectedCalcChild()) {
        if (static_cast<ksys::act::Player*>(mActor)->_1770.y >
            static_cast<ksys::act::Player*>(mActor)->_178c) {
            static_cast<ksys::act::Player*>(mActor)->_1844.update();
            if (static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon())
                static_cast<ksys::act::Player*>(mActor)->m228(false);
        } else {
            static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(3.0f, 3.0f);
        }
    }
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerFall::isChangeable() const {
    return true;
}

bool PlayerFall::isFinished() const {
    return static_cast<ksys::act::Player*>(mActor)->isSurfingOnGround() || ActionBase::isFinished();
}

}  // namespace uking::action
