#include "Game/AI/Action/actionAnimalEatAction.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

AnimalEatAction::AnimalEatAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalEatAction::~AnimalEatAction() = default;

bool AnimalEatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalEatAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    auto* as_list = mActor->getASList();
    if (!rideable || !as_list) {
        setFailed();
        return;
    }
    rideable->_130 = 0;
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 0.0f);
    rideable->_18.sub_7100E76E74(act::sUnk_71026032d0, false);
    _30.setDirect(sead::BitFlag8::makeMask(Bit(Bit::_0)));
    const f32 frames = *mMinFramesPlayWaitAS_s;
    _34.value = frames;
    _34.previous_value = frames;
}

void AnimalEatAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalEatAction::loadParams_() {
    getStaticParam(&mMinFramesPlayWaitAS_s, "MinFramesPlayWaitAS");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void AnimalEatAction::calc_() {
    ksys::act::ai::Action::calc_();
}

int AnimalEatAction::m32() {
    return 1;
}

}  // namespace uking::action
