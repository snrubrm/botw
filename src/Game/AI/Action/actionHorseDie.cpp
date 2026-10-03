#include "Game/AI/Action/actionHorseDie.h"
#include "Game/Actor/actHorse.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

HorseDie::HorseDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseDie::~HorseDie() = default;

bool HorseDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

// NON_MATCHING: only the two SEAD_ENUM stack temporaries are in swapped slots (+8 / +0xc)
void HorseDie::leave_() {
    if (auto* horse = sead::DynamicCast<act::Horse>(mActor)) {
        horse->_f50.sub_71006EDCB8();
        horse->_a98._58 &= ~(1 << int(act::ExtendedEntity::Flag(act::ExtendedEntity::Flag::_3)));
        horse->_a98._2c = 0.1f;
        horse->_a98._58 |= 1 << int(act::ExtendedEntity::Flag(act::ExtendedEntity::Flag::_4));
    }
    sub_71007A3540(mActor);
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5EC30();
    ksys::act::enableAllAttClients(mActor);
    if (auto* options = mActor->getHorseOptionsMaybe())
        options->Unk_7100e8b2b8::_8 &= ~0x200u;
}

void HorseDie::loadParams_() {
    getStaticParam(&mDyingFrames_s, "DyingFrames");
    getStaticParam(&mCheckIfStable_s, "CheckIfStable");
    getStaticParam(&mASName_s, "ASName");
}

void HorseDie::calc_() {
    ksys::act::ai::Action::calc_();
}

bool HorseDie::handleMessage_(const ksys::Message* message) {
    if (message->getType() != ksys::MessageType(0x380001c))
        return false;
    auto* info = mActor->m135();
    if (info) {
        if (info->_0)
            mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
        else
            mActor->deleteAndEmit(0);
    } else {
        mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
    }
    return true;
}

}  // namespace uking::action
