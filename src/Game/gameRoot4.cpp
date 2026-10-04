#include "Game/gameRoot4.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(Root4)

// NON_MATCHING: the original retains additional SEAD_ENUM argument copies.
void Root4::sub_71008BCF44(FlagIdx idx, bool on) {
    _2c |= 1u << idx;
    if (on)
        _28 |= 1u << idx;
    else
        _28 &= ~(1u << idx);
}

}  // namespace uking
