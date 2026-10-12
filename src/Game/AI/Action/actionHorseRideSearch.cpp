#include "Game/AI/Action/actionHorseRideSearch.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideSearch::HorseRideSearch(const InitArg& arg) : HorseRideBase(arg) {}

HorseRideSearch::~HorseRideSearch() = default;

bool HorseRideSearch::init_(sead::Heap* heap) {
    return HorseRideBase::init_(heap);
}

void HorseRideSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideBase::enter_(params);
    _30 = ksys::Timer(5.0f, 5.0f);
    sub_71001AD8A0("HorseSearch", true);
    mFlags.reset(Flag::Changeable);
    if (auto* actor = sub_71005D7348(mActor))
        _40.sub_710070DC38(actor, true);
}

void HorseRideSearch::leave_() {
    HorseRideBase::leave_();
}

void HorseRideSearch::loadParams_() {
    HorseRideBase::loadParams_();
}

void HorseRideSearch::calc_() {
    HorseRideBase::calc_();
    if (_30.value <= sead::Mathf::epsilon())
        mFlags.set(Flag::Changeable);
    else
        _30.update();
}

bool HorseRideSearch::isFinished() const {
    return sub_71001ADA78();
}

}  // namespace uking::action
