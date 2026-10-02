#include "Game/AI/AI/aiRupeeRabbitNormal.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ai {

RupeeRabbitNormal::RupeeRabbitNormal(const InitArg& arg) : PreyNormal(arg) {}

RupeeRabbitNormal::~RupeeRabbitNormal() = default;

bool RupeeRabbitNormal::init_(sead::Heap* heap) {
    return PreyNormal::init_(heap);
}

void RupeeRabbitNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    PreyNormal::enter_(params);
    const f32 time = sead::GlobalRandom::instance()->getF32Range(0.0f, 45.0f);
    _348 = ksys::Timer(time, time);
    mActor->getLodState()->mFlags10.reset(0x40);
}

void RupeeRabbitNormal::calc_() {
    PreyNormal::calc_();
    if (isCurrentChild("逃走") || isCurrentChild("ダメージ逃走")) {
        auto* lod_state = mActor->getLodState();
        if (!lod_state->mFlags10.isOn(0x40))
            lod_state->mFlags10.set(0x40);
    }
}

void RupeeRabbitNormal::leave_() {
    PreyNormal::leave_();
}

void RupeeRabbitNormal::loadParams_() {
    PreyNormal::loadParams_();
    getMapUnitParam(&mDeleteEndNushiTime_m, "DeleteEndNushiTime");
}

bool RupeeRabbitNormal::m42() {
    if (*mDeleteEndNushiTime_m && !ksys::gdt::getFlag_AnimalMaster_Appearance(false)) {
        _348.update();
        if (_348.value <= sead::Mathf::epsilon())
            return true;
    }
    return false;
}

}  // namespace uking::ai
