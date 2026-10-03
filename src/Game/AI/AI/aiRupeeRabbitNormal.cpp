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

// NON_MATCHING: regalloc (the original keeps &filter in x19 and the result in x20, recomputing &filter in each branch)
ksys::act::Unk_7100d78e50* RupeeRabbitNormal::m43(s32 idx, bool skip_own_target) {
    if (!_d8)
        return nullptr;

    Unk_7102410738 filter;
    if (skip_own_target)
        return sub_7100501B84(idx, &filter);

    if (!_d8->_260[idx])
        return nullptr;
    return ksys::act::sub_7100D7EEE8(&_d8->_260[idx]->_8, &filter);
}

}  // namespace uking::ai
