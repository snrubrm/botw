#include "KingSystem/ActorSystem/actActorChemicals.h"

namespace ksys::act {

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

}  // namespace ksys::act
