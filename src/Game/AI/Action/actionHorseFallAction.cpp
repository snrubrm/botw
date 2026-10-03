#include "Game/AI/Action/actionHorseFallAction.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

HorseFallAction::HorseFallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseFallAction::~HorseFallAction() = default;

bool HorseFallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseFallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    rideable->_18.sub_7100E76E74(act::sUnk_71026031f0, false);
    if (auto* horse = sead::DynamicCast<act::Rideable>(rideable)) {
        horse->sub_7100E8BE10();
        horse->Unk_7100e8b2b8::_8 = 0x200;
    }
}

void HorseFallAction::leave_() {
    mActor->getASList()->sub_710115B01C(0, 0, true);
    if (auto* rideable = mActor->getHorseOptionsMaybe()) {
        rideable->sub_7100E8BD80();
        rideable->Unk_7100e8b2b8::_8 &= ~0x200u;
    }
}

void HorseFallAction::loadParams_() {}

void HorseFallAction::calc_() {
    if (auto* cc = mActor->getCharacterController()) {
        if (cc->sub_7100F5F14C())
            setFinished();
    }
}

}  // namespace uking::action
