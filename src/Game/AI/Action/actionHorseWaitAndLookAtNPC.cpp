#include "Game/AI/Action/actionHorseWaitAndLookAtNPC.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseWaitAndLookAtNPC::HorseWaitAndLookAtNPC(const InitArg& arg) : HorseWaitAction(arg) {}

HorseWaitAndLookAtNPC::~HorseWaitAndLookAtNPC() = default;

bool HorseWaitAndLookAtNPC::init_(sead::Heap* heap) {
    return HorseWaitAction::init_(heap);
}

void HorseWaitAndLookAtNPC::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseWaitAction::enter_(params);
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->RideableBase::_8 |= 0x200000;
}

void HorseWaitAndLookAtNPC::leave_() {
    HorseWaitAction::leave_();
    if (auto* rideable = mActor->getHorseOptionsMaybe())
        rideable->RideableBase::_8 &= ~0x200000;
}

void HorseWaitAndLookAtNPC::loadParams_() {
    HorseWaitAction::loadParams_();
}

void HorseWaitAndLookAtNPC::calc_() {
    HorseWaitAction::calc_();
}

}  // namespace uking::action
