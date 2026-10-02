#include "Game/AI/Action/actionWaterFloatElectricParalysis.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::action {

WaterFloatElectricParalysis::WaterFloatElectricParalysis(const InitArg& arg)
    : OneTimeWaterFloatStopASPlay(arg) {}

WaterFloatElectricParalysis::~WaterFloatElectricParalysis() = default;

void WaterFloatElectricParalysis::loadParams_() {
    OneTimeWaterFloatStopASPlay::loadParams_();
}

void WaterFloatElectricParalysis::calc_() {
    OneTimeWaterFloatStopASPlay::calc_();
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (actor && !actor->m151(4))
        setFinished();
}

}  // namespace uking::action
