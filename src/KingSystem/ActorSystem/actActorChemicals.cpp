#include "KingSystem/ActorSystem/actActorChemicals.h"

namespace ksys::act {

// The body keeps the vtable store of the original, as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }
// (commit 96101229).
Unk_71024e6560::~Unk_71024e6560() {
    ;
}

ActorChemicals::ActorChemicals() = default;

Unk_71024e6428* ActorChemicals::sub_7100E3718C(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    if (_58.size() + _80 < 1)
        return nullptr;
    if (idx < _58.size())
        return &_58[idx];
    return &_70[idx - _58.size()];
}

// NON_MATCHING: the original's null path skips the conversion (branch target only)
Chemical* ActorChemicals::sub_7100E37788(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    auto* element = getElement_(idx);
    if (!element)
        return nullptr;
    return &element->mChemical;
}

// NON_MATCHING: the original's null path skips the conversion (branch target only)
Chemical* ActorChemicals::getStuff(int idx) {
    const auto lock = sead::makeScopedLock(mCS);
    auto* element = getElement_(idx);
    if (!element)
        return nullptr;
    return &element->mChemical;
}

// NON_MATCHING: same as getStuff (the original's null path of the inlined element lookup unlocks once and shares the
// outer unlock; the loop counters also use other registers)
void ActorChemicals::sub_7100E39614(bool on) {
    const auto lock = sead::makeScopedLock(mCS);
    for (s32 i = 0; i < _58.size() + _80; ++i) {
        if (auto* chemical = getStuff(i))
            chemical->sub_7100D91098(on);
    }
}

}  // namespace ksys::act
