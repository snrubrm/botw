#include "Game/AI/Action/actionBindOff.h"
#include "Game/AI/Action/actionEventBind.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BindOff::BindOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BindOff::~BindOff() = default;

bool BindOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BindOff::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* unit = sead::DynamicCast<ActorLinkForEventBindMaybe>(
        *static_cast<Unk_71025afb58**>(mEventBindUnit_a));
    if (unit && unit->_8) {
        mActor->sub_71011DA834(unit->_8);
        unit->_8 = nullptr;
    }
    setFinished();
}

void BindOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void BindOff::loadParams_() {
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

void BindOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
