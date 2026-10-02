#include "Game/AI/Action/actionFishOnGround.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FishOnGround::FishOnGround(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

FishOnGround::~FishOnGround() = default;

bool FishOnGround::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void FishOnGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void FishOnGround::leave_() {
    ActionWithPosAngReduce::leave_();
    if (auto* controller = mActor->getCharacterController())
        controller->sub_7100F5F458(_40);
}

void FishOnGround::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASKey_s, "ASKey");
}

void FishOnGround::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
