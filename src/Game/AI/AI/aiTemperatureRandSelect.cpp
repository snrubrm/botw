#include "Game/AI/AI/aiTemperatureRandSelect.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemical.h"

namespace uking::ai {

TemperatureRandSelect::TemperatureRandSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TemperatureRandSelect::~TemperatureRandSelect() = default;

bool TemperatureRandSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TemperatureRandSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* chemical = mActor->getChemicalStuff()) {
        const f32 diff = chemical->sub_7100D91958() - *mBaseTemperature_s;
        f32 base = 0.0f;
        if (diff < 0.0f ? *museBaseRatioTiming_s == -1 : (diff > 0.0f && *museBaseRatioTiming_s == 1))
            base = *mBaseChangeRatio_s;
        const f32 ratio = sead::Mathf::clamp(base + diff * *mTemperatureChangeRatio_s, 0.0f, 100.0f);
        if (!(sead::GlobalRandom::instance()->getF32() * 100.0f < ratio)) {
            changeChild("行動Ｂ", params);
            return;
        }
    }
    changeChild("行動Ａ", params);
}

void TemperatureRandSelect::calc_() {}

void TemperatureRandSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TemperatureRandSelect::loadParams_() {
    getStaticParam(&mBaseChangeRatio_s, "BaseChangeRatio");
    getStaticParam(&museBaseRatioTiming_s, "useBaseRatioTiming");
    getStaticParam(&mTemperatureChangeRatio_s, "TemperatureChangeRatio");
    getStaticParam(&mBaseTemperature_s, "BaseTemperature");
}

}  // namespace uking::ai
