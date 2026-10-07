#include "Game/gameRoot4.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(Root4)

void Root4::init(sead::Heap* heap) {
    _30.tryAllocBuffer(10, heap);
    for (s32 i = 0; i < _30.size(); ++i) {
        _30[i]._0 = i;
        _30[i]._4.makeAllOne();
    }
}
// NON_MATCHING: enum copies, index argument materialization and loop scheduling differ.
void Root4::sub_71008BCE5C(FlagIdx idx, bool on, s32 record_index) {
    _30.get(record_index)->_4.changeBit(idx, on);
    if (!_2c.isOnBit(idx)) {
        for (const auto& record : _30) {
            if (!record._4.isOnBit(idx)) {
                _28.resetBit(idx);
                return;
            }
        }
        _28.setBit(idx);
    }
}
// NON_MATCHING: enum copies and loop scheduling differ.
void Root4::sub_71008BCFA0(FlagIdx idx) {
    _2c.resetBit(idx);
    for (const auto& record : _30) {
        if (!record._4.isOnBit(idx)) {
            _28.resetBit(idx);
            return;
        }
    }
    _28.setBit(idx);
}

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
