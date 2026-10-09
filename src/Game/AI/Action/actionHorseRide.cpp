#include "Game/AI/Action/actionHorseRide.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRide::HorseRide(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseRide::~HorseRide() = default;

bool HorseRide::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseRide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseRide::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseRide::loadParams_() {
    getStaticParam(&mUpperBodyASSlot_s, "UpperBodyASSlot");
    getStaticParam(&mLowerBodyASSlot_s, "LowerBodyASSlot");
}

void HorseRide::calc_() {
    ksys::act::ai::Action::calc_();
}

bool HorseRide::sub_71001ADA78() const {
    if (auto* as_list = mActor->getASList())
        return as_list->x_4(*mUpperBodyASSlot_s, 0);
    return true;
}

void HorseRide::sub_71001AD8A0(const char* name, bool a2) {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    if (a2 && as_list->x_1(*mUpperBodyASSlot_s, 0) == name)
        return;
    as_list->startAnimationMaybe(-1.0f, -1.0f, name, *mUpperBodyASSlot_s, 0, true);
    if (as_list->x_1(*mLowerBodyASSlot_s, 0) == name)
        as_list->sub_710115F158(as_list, *mUpperBodyASSlot_s, *mLowerBodyASSlot_s, 0, 0);
}

void HorseRide::sub_71001ADAA0(const sead::Vector3f& target) {
    sub_71005D73F8(mActor, target);
}

void HorseRide::sub_71001ADAA8() {
    sub_71005D74B8(mActor);
    sub_71005DB3EC(mActor);
}

}  // namespace uking::action
