#include "Game/AI/AI/aiAirOctaBoardBurn.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AirOctaBoardBurn::AirOctaBoardBurn(const InitArg& arg) : SeqTwoAction(arg) {}

AirOctaBoardBurn::~AirOctaBoardBurn() = default;

bool AirOctaBoardBurn::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void AirOctaBoardBurn::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void AirOctaBoardBurn::leave_() {
    SeqTwoAction::leave_();
}

void AirOctaBoardBurn::loadParams_() {
    SeqTwoAction::loadParams_();
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaBoardBurn::calc_() {
    SeqTwoAction::calc_();
    if (isCurrentChild("先行動"))
        mActor->m93(4, 0.0f);
    else
        mActor->m93(0, 0.0f);
}

}  // namespace uking::ai
