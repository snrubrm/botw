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

void HorseKickBackAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 1.0f);
    _38 |= 1 << int(Bit(Bit::_0));
    const sead::SafeString& name = mASName_s;
    const bool succeeded = rideable->_18.sub_7100E76E74(name, false);
    const int mask = 1 << int(Bit(Bit::_1));
    if (succeeded)
        _38 |= mask;
    else
        _38 &= ~mask;
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
