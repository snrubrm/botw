#include "Game/AI/Action/actionHorseEatAction.h"
#include "Game/Actor/actHorseStrings.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseEatAction::HorseEatAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseEatAction::~HorseEatAction() = default;

bool HorseEatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseEatAction::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* rideable = mActor->m132();
    if (!rideable) {
        setFailed();
        return;
    }
    mActor->getASList()->x_6(1, 0, 0.0f);
    mActor->getASList()->x_6(2, 0, 0.0f);
    rideable->_18.sub_7100E76E74(act::sUnk_71026032d0, false);
    _58.setDirect(sead::BitFlag8::makeMask(Bit(Bit::_0)));
    _60 = sead::SafeString::cEmptyString;
}

void HorseEatAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseEatAction::loadParams_() {
    getStaticParam(&mTargetDirToStickX_s, "TargetDirToStickX");
    getStaticParam(&mTargetDistOffset_s, "TargetDistOffset");
    getStaticParam(&mTargetDistToStickY_s, "TargetDistToStickY");
    getStaticParam(&mMaxStickXForEat_s, "MaxStickXForEat");
    getStaticParam(&mMaxStickYForEat_s, "MaxStickYForEat");
    getStaticParam(&mDelayFrames_s, "DelayFrames");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseEatAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
