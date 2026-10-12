#include "Game/AI/Action/actionHorseRideBase.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideBase::HorseRideBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseRideBase::~HorseRideBase() = default;

bool HorseRideBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseRideBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseRideBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseRideBase::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

void HorseRideBase::calc_() {
    ksys::act::ai::Action::calc_();
}

bool HorseRideBase::sub_71001ADA78() const {
    if (auto* as_list = mActor->getASList())
        return as_list->x_4(*mUpperBodyASSlot_s, 0);
    return true;
}

void HorseRideBase::sub_71001AD8A0(const char* name, bool a2) {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    if (a2 && as_list->x_1(*mUpperBodyASSlot_s, 0) == name)
        return;
    as_list->startAnimationMaybe(-1.0f, -1.0f, name, *mUpperBodyASSlot_s, 0, true);
    if (as_list->x_1(*mLowerBodyASSlot_s, 0) == name)
        as_list->sub_710115F158(as_list, *mUpperBodyASSlot_s, *mLowerBodyASSlot_s, 0, 0);
}

void HorseRideBase::sub_71001ADAA0(const sead::Vector3f& target) {
    sub_71005D73F8(mActor, target);
}

void HorseRideBase::sub_71001ADAA8() {
    sub_71005D74B8(mActor);
    sub_71005DB3EC(mActor);
}

}  // namespace uking::action
