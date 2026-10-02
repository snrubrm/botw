#include "KingSystem/Event/evtEventMgrStruct1.h"

namespace ksys::evt {

EventMgrStruct1::EventMgrStruct1() {
    for (int i = 0; i < _0.size(); ++i)
        _0[i]._4 = i;
}

EventMgrStruct1::Clock* EventMgrStruct1::sub_71012731D8() {
    for (int i = 0; i < _0.size(); ++i) {
        auto& clock = _0[i];
        if (!clock._8) {
            clock._8 = true;
            clock._0 = 0;
            return &clock;
        }
    }
    return nullptr;
}

void EventMgrStruct1::sub_7101273334(Clock* clock, bool release) {
    for (int i = 0; i < _c0.size(); ++i) {
        if (_c0[i]._8 >= 0 && _c0[i]._8 == clock->_4)
            _c0[i]._8 = -1;
    }
    if (release)
        clock->_8 = false;
}

// NON_MATCHING: the original reads clock->_4 before the stores to the entry (as if the three values
// were passed to an inline setter)
int EventMgrStruct1::sub_7101273370(Clock* clock, const sead::Vector2f& value) {
    for (int i = 0; i < _c0.size(); ++i) {
        auto& entry = _c0[i];
        if (entry._8 < 0) {
            entry._0 = value.x;
            entry._4 = value.y;
            entry._8 = clock->_4;
            return i;
        }
    }
    return -1;
}

void EventMgrStruct1::sub_71012733D8(int idx) {
    auto& entry = _c0[idx];
    if (entry._8 >= 0)
        entry._8 = -1;
}

f32 EventMgrStruct1::sub_7101273400(int idx) const {
    const auto& entry = _c0[idx];
    if (entry._8 < 0)
        return -1.0f;
    return _0[entry._8]._0 - entry._0;
}

f32 EventMgrStruct1::sub_7101273448(int idx) const {
    if (_c0[idx]._8 >= 0)
        return _c0[idx]._4;
    return 0.0f;
}

}  // namespace ksys::evt
