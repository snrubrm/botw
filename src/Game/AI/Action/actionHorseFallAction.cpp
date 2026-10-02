#include "Game/AI/Action/actionHorseFallAction.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseFallAction::HorseFallAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseFallAction::~HorseFallAction() = default;

bool HorseFallAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseFallAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
