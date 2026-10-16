#include "Game/Actor/Player/Action/actionPlayerStopInAir.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

PlayerStopInAir::PlayerStopInAir(const InitArg& arg) : PlayerAction(arg) {}

// NON_MATCHING: register swap for the _17f0 store and the original loads the velocity before mActor.
void PlayerStopInAir::enter_(ksys::act::ai::InlineParamPack* params) {
    static_cast<ksys::act::Player*>(mActor)->_17f0 = static_cast<ksys::act::Player*>(mActor)->m194();
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_17f0 && player->_d11) {
        auto* child = sead::DynamicCast<ksys::act::Actor>(player->getConnectedCalcChild());
        if (child && ksys::act::hasTag(child, 0x9d19a4c4))
            static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
    }

    const u32 flags = static_cast<ksys::act::Player*>(mActor)->_cf0.getDirect();
    const u32 had_flag = flags & 0x800000;
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800);
    if (flags & 0x20000)
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x20000);
    if (had_flag) {
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x800000);
        if (static_cast<ksys::act::Player*>(mActor)->sub_7100888294() &&
            !static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(3)) {
            static_cast<ksys::act::Player*>(mActor)->x_7();
        }
    }

    if (auto* controller = mActor->getCharacterController()) {
        sead::Vector3f velocity;
        controller->sub_7100F5F598(&velocity);
        static_cast<ksys::act::Player*>(mActor)->_1810 = velocity;
        controller->sub_7100F5EEB8(0.0f);
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
        controller->sub_7100F5FB24(sead::Vector3f::zero);
        if (!*mNoFixed_d)
            controller->sub_7100F63388(true, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::Hover);
    }
    player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;

    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        static_cast<ksys::act::Player*>(mActor)->_cec.set(0x8000);
        auto* proc = static_cast<ksys::act::Player*>(mActor)->_2c28.getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc)) {
            actor->wakeUp(ksys::act::BaseProc::SleepWakeReason::_0);
            sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x8000024), nullptr);
        }
    }

    if (mActor->getASList()->x_7(2, 0, &ksys::as::ASList::Unk2::sub_710002E82C))
        mActor->getASList()->x_3(2, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    if (mActor->getASList()->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        mActor->getASList()->x_3(1, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    if (mActor->getASList()->x_7(0, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        mActor->getASList()->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    auto* actor = mActor;
    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
}

// NON_MATCHING: same instructions; the original keeps `this` in x19 and reloads mActor each time, this build
// folds `&mActor` into a pre-indexed load in x21 (same as PlayerAtnWait::leave_).
void PlayerStopInAir::leave_() {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EEB8(1.0f);
        if (!*mNoFixed_d)
            controller->sub_7100F63388(false, -1);
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
        controller->sub_7100F5F6FC(static_cast<ksys::act::Player*>(mActor)->_1810);
    }
    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        auto* proc = static_cast<ksys::act::Player*>(mActor)->mResidentActors[0].getProc(nullptr, nullptr);
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(proc))
            actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    }
    if (static_cast<ksys::act::Player*>(mActor)->_cf0.isOnBit(23) &&
        static_cast<ksys::act::Player*>(mActor)->_c40.isOnBit(3))
        static_cast<ksys::act::Player*>(mActor)->sub_710088A854();
    if (mActor->getASList()->x_7(2, 0, &ksys::as::ASList::Unk2::sub_710002E82C))
        mActor->getASList()->x_3(2, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (mActor->getASList()->x_7(1, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        mActor->getASList()->x_3(1, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    if (mActor->getASList()->x_7(0, 1, &ksys::as::ASList::Unk2::sub_710002E82C))
        mActor->getASList()->x_3(0, 1, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    auto* actor = mActor;
    actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
    actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 1.0f);
}

void PlayerStopInAir::loadParams_() {
    getDynamicParam(&mNoFixed_d, "NoFixed");
}

void PlayerStopInAir::calc_() {
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F6FC(sead::Vector3f::zero);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c98.isOnBit(23))
        player->_1810 = sead::Vector3f::zero;
    setFinished();
}

bool PlayerStopInAir::isChangeable() const {
    return true;
}

}  // namespace uking::action
