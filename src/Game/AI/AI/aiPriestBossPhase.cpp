#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "Game/AI/AI/aiPriestBossPhase.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

// NON_MATCHING: native string-comparison and loop cleanup scheduling differ.
// 0x7100528c48
bool PriestBossPhase::sub_7100528C48() {
    if (!mActor || !mActor->getAwareness())
        return false;
    auto& entries = mActor->getAwareness()->_8;
    const s32 count = entries.size();
    if (count < 1)
        return false;
    for (s32 i = 0; i < count; ++i) {
        auto* entry = i < entries.size() ? ksys::act::sub_7100D78E30(&entries, i) : nullptr;
        auto& link = entry->_0.mLink;
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.getName() != "Item_Fruit_H" && accessor.getName() != "Item_Roast_11")
            continue;
        if (accessor.sub_7100D10E6C(30) || accessor.checkFlag25())
            continue;
        auto* unit = sub_7100525A88();
        if (link.hasProc())
            unit->_28 = link;
        return true;
    }
    return false;
}

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
