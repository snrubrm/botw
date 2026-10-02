#include "KingSystem/ActorSystem/actActorChemicals.h"

namespace ksys::act {

ActorChemicals::ActorChemicals() = default;

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
