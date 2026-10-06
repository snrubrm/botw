#include "Game/gameRoot4.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(Root4)

bool Root4::checkFlag(FlagIdx idx) const {
    return _28.isOnBit(idx);
}

// NON_MATCHING: the original retains additional SEAD_ENUM argument copies (it stores the argument twice and re-reads it
// from the stack for every flag access).
void Root4::sub_71008BCF44(FlagIdx idx, bool on) {
    _2c.setBit(idx);
    _28.changeBit(idx, on);
}

}  // namespace uking
