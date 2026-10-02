#include "Game/AI/Action/actionHorseWaitThrowOffAction.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseWaitThrowOffAction::HorseWaitThrowOffAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitThrowOffAction::~HorseWaitThrowOffAction() = default;

bool HorseWaitThrowOffAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseWaitThrowOffAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseWaitThrowOffAction::leave_() {
    if (*mSetRideAttentionInvalid_s) {
        if (auto* rideable = mActor->getHorseOptionsMaybe()) {
            rideable->sub_7100E8BD80();
            rideable->Unk_7100e8b2b8::_8 &= ~0x200u;
        }
    }
}

void HorseWaitThrowOffAction::loadParams_() {
    getStaticParam(&mSucceedGear_s, "SucceedGear");
    getStaticParam(&mSetRideAttentionInvalid_s, "SetRideAttentionInvalid");
}

void HorseWaitThrowOffAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
