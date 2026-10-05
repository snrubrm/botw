#include "Game/AI/Action/actionAirOctaFloatBase.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

AirOctaFloatBase::AirOctaFloatBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaFloatBase::~AirOctaFloatBase() = default;

bool AirOctaFloatBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaFloatBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::pi();
    _44 = 0.0f;
    _1c0 &= ~1;
    _70.setName("Neck");
    _118.setName("Head_2");
    mActor->boneHandleStuff(&_70, false);
    mActor->boneHandleStuff(&_118, false);
}

void AirOctaFloatBase::leave_() {
    mActor->sub_71011DA868(&_70);
    mActor->sub_71011DA868(&_118);
}

void AirOctaFloatBase::loadParams_() {
    getStaticParam(&mAmplitude_s, "Amplitude");
    getStaticParam(&mGoalDistance_s, "GoalDistance");
    getStaticParam(&mGoalInSuccessEnd_s, "GoalInSuccessEnd");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

void AirOctaFloatBase::calc_() {
    m32();
    sub_7100088400();
    sub_71000885B0();
    sub_71000886B8();
    _40 += ksys::VFR::instance()->getDeltaTime();
}

}  // namespace uking::action
