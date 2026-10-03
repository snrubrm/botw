#include "Game/AI/Action/actionHorseWaitThrowOffAction.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

HorseWaitThrowOffAction::HorseWaitThrowOffAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitThrowOffAction::~HorseWaitThrowOffAction() = default;

bool HorseWaitThrowOffAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseWaitThrowOffAction::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mSetRideAttentionInvalid_s) {
        if (auto* rideable = mActor->getHorseOptionsMaybe()) {
            rideable->sub_7100E8BE10();
            rideable->Unk_7100e8b2b8::_8 = 0x200;
        }
    }
    if (mActor->getASList()->x_1(0, 0) == act::sUnk_7102603110)
        setFinished();
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
    auto* as_list = mActor->getASList();
    auto* rideable = mActor->m132();
    as_list->x_6(1, 0, 0.0f);
    as_list->x_6(2, 0, 0.0f);
    as_list->x_6(9, 0, 0.0f);
    if (as_list->x_4(0, 0)) {
        if (rideable && *mSucceedGear_s >= 0) {
            rideable->sub_7100E63224(0, u32(*mSucceedGear_s));
            as_list->x_6(10, 0, f32(*mSucceedGear_s));
        }
        as_list->sub_710115B01C(0, 0, true);
        setFinished();
    }
    if (auto* controller = mActor->getCharacterController())
        act::sub_7100E7F698(rideable, as_list, controller);
}

}  // namespace uking::action
