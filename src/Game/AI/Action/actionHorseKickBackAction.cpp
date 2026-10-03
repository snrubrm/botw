#include "Game/AI/Action/actionHorseKickBackAction.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actRideable.h"

namespace uking::action {

HorseKickBackAction::HorseKickBackAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseKickBackAction::~HorseKickBackAction() = default;

bool HorseKickBackAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original ORs the old flags with the mask (`old | mask`) and sinks the byte store
// below the call arguments (scheduling)
void HorseKickBackAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 1.0f);
    _38.set(sead::BitFlag8::makeMask(Bit(Bit::_0)));
    const bool succeeded = rideable->_18.sub_7100E76E74(mASName_s, false);
    _38.changeBit(Bit(Bit::_1), succeeded);
}

void HorseKickBackAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseKickBackAction::loadParams_() {
    getStaticParam(&mSucceedGear_s, "SucceedGear");
    getStaticParam(&mASName_s, "ASName");
}

void HorseKickBackAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
