#include "Game/AI/Action/actionHorseWaitAndLookAtNPC.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseBase.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actHorseStrings.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
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

// NON_MATCHING: rideable null check is scheduled before the horse state branch.
void HorseWaitAndLookAtNPC::calc_() {
    HorseWaitAction::calc_();
    auto* horse = sead::DynamicCast<act::HorseBase>(mActor);
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!horse)
        return;
    auto* list = mActor->getASList();
    if (!horse->sub_7100E696D4() || !rideable)
        return;
    sead::Vector3f position;
    if (!rideable->sub_7100E8C068(&position))
        return;
    if (list->x_1(0, 0) != act::sUnk_7102603110 || act::sub_7100E81568(list))
        return;
    list->x_2(66, 3, horse->sub_7100E6BE40(), false);
    list->x_2(66, 12, false, false);
    rideable->sub_7100E636D4(&position, nullptr, false);
}

}  // namespace uking::action
