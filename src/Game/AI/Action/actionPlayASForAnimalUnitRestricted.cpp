#include "Game/AI/Action/actionPlayASForAnimalUnitRestricted.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

PlayASForAnimalUnitRestricted::PlayASForAnimalUnitRestricted(const InitArg& arg)
    : PlayASForAnimalUnit(arg) {}

PlayASForAnimalUnitRestricted::~PlayASForAnimalUnitRestricted() = default;

bool PlayASForAnimalUnitRestricted::init_(sead::Heap* heap) {
    return PlayASForAnimalUnit::init_(heap);
}

void PlayASForAnimalUnitRestricted::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayASForAnimalUnit::enter_(params);
}

void PlayASForAnimalUnitRestricted::leave_() {
    PlayASForAnimalUnit::leave_();
}

void PlayASForAnimalUnitRestricted::loadParams_() {
    PlayASForAnimalUnit::loadParams_();
}

void PlayASForAnimalUnitRestricted::calc_() {
    PlayASForAnimalUnit::calc_();
}

void PlayASForAnimalUnitRestricted::m32() {
    if (mActor->getASList()->x(0x16, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011638DC, true)) {
        mFlags.reset(Flag::Changeable);
        return;
    }
    ForkAnimalASPlay::m32();
}

}  // namespace uking::action
