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
    if (auto* controller = mActor->getCharacterController()) {
        _40 = controller->sub_7100F5F0E4();
        controller->sub_7100F5F458(ksys::act::MotionType::_1);
    }
    mFlags.reset(Flag::Changeable);
    if (!mASKey_s.isEmpty())
        playAS(mASKey_s.cstr(), true, 0, 0, -1.0f);
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
