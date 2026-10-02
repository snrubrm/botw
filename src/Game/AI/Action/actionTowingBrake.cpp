#include "Game/AI/Action/actionTowingBrake.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

TowingBrake::TowingBrake(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TowingBrake::~TowingBrake() = default;

bool TowingBrake::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TowingBrake::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mActor->getASList()->sub_710115ED5C(66, 10))
        playAS("Swim", true, 0, 0, -1.0f);
    else
        playAS("Swim_Ground", false, 0, 0, -1.0f);
}

void TowingBrake::leave_() {
    ksys::act::ai::Action::leave_();
}

void TowingBrake::loadParams_() {}

void TowingBrake::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
