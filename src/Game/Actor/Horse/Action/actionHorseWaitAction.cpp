#include "Game/Actor/Horse/Action/actionHorseWaitAction.h"
#include "Game/Actor/actHorseStrings.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseWaitAction::HorseWaitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitAction::~HorseWaitAction() = default;

bool HorseWaitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the native retains the masked finished flag in the early-return path.
bool HorseWaitAction::isFinished() const {
    if (act::sUnk_7102603110 == mActor->getASList()->x_1(0, 0) &&
        !ksys::act::ai::Action::isFinished())
        return isFinishedAS(0, 0);
    return ksys::act::ai::Action::isFinished();
}

void HorseWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseWaitAction::leave_() {
    if (auto* nav = mActor->m45())
        nav->sub_7100F76314();
}

void HorseWaitAction::loadParams_() {
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mSmoothStopFrames_s, "SmoothStopFrames");
    getStaticParam(&mSmoothStopFramesGear3_s, "SmoothStopFramesGear3");
    getStaticParam(&mMinFramesGear1_s, "MinFramesGear1");
    getStaticParam(&mIsCourbetteEnabled_s, "IsCourbetteEnabled");
    getStaticParam(&mIsLight_s, "IsLight");
}

void HorseWaitAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
