#include "Game/AI/AI/aiPriestBossPhase.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_7102450fa8.h"

namespace uking::ai {

PriestBossPhase::PriestBossPhase(const InitArg& arg) : PriestBossMeta(arg) {}

PriestBossPhase::~PriestBossPhase() = default;

bool PriestBossPhase::init_(sead::Heap* heap) {
    return PriestBossMeta::init_(heap);
}

// NON_MATCHING: the original builds the two flag temporaries in the opposite stack slots and orrs the
// masks as (4, 3) (BitFlag16::setBit gives `orr mask, bits`), keeps m38()'s result in a register (no stack
// slot for a named Flag local) and stores _3c / _40 before the `_38 == 4` branch
void PriestBossPhase::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMeta::enter_(params);
    _60.makeAllZero();
    _60.setBit(Flag(Flag::_4));
    _60.setBit(Flag(Flag::_3));
    const Flag phase = m38();
    auto* unit = sub_7100525A88();
    if (unit->_38 == Flag::_4)
        unit->_38 = phase;
    unit->_3c = phase;
    unit->_40 = *mPercentLifePrevious_s;
    _70.value = _70.previous_value = 5.0f;
}

void PriestBossPhase::leave_() {
    PriestBossMeta::leave_();
    _60.resetBit(Flag(Flag::_4));
}

void PriestBossPhase::loadParams_() {
    PriestBossMeta::loadParams_();
    getStaticParam(&mPercentLifeTransition_s, "PercentLifeTransition");
    getStaticParam(&mPercentLifePrevious_s, "PercentLifePrevious");
}

void PriestBossPhase::m40() {
    _64.update();
    if (_64.value <= sead::Mathf::epsilon()) {
        _64.value = 30.0f;
        _64.previous_value = 30.0f;
        sub_7100525A88()->_2b0.copy(sUnk_7102450f80[sead::GlobalRandom::instance()->getU32(3)]);
    }
}

bool PriestBossPhase::m36() {
    return *mMetaAILife_a <= int(float(*mMetaAIMaxLife_a) * *mPercentLifeTransition_s);
}

}  // namespace uking::ai
