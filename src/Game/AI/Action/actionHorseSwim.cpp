#include "Game/AI/Action/actionHorseSwim.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseSwim::HorseSwim(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseSwim::~HorseSwim() = default;

bool HorseSwim::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseSwim::leave_() {
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (!rideable)
        return;
    {
        const uking::act::Unk_7100e8b2b8::Unk8 type = rideable->Unk_7100e8b2b8::_8 & 0xff;
        if (int(type) != uking::act::Unk_7100e8b2b8::Unk8::_3) {
            rideable->sub_7100E8BD80();
            rideable->Unk_7100e8b2b8::_8 &= ~0x200u;
        }
    }
    rideable->_18.sub_7100E770C4(false);
}

void HorseSwim::loadParams_() {}

void HorseSwim::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
