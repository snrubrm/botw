#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace ksys::act {

void AwarenessInstance::sleep() {
    disable();
}

void AwarenessInstance::sub_7100D7EBE0(f32 value) {
    for (auto* sensor : _260) {
        if (sensor)
            sensor->_4c = value;
    }
    sub_7100D7C494();
}

void AwarenessInstance::sub_7100D7EC14(int idx, f32 value) {
    if (auto* sensor = _260[idx])
        sensor->_4c = value;
    sub_7100D7C494();
}

f32 AwarenessInstance::sub_7100D7EC34(int idx) const {
    if (auto* sensor = _260[idx])
        return sensor->_4c;
    return 0.0f;
}

// NON_MATCHING: register allocation in the search loop; the filter's _18 is addressed differently
void AwarenessInstance::sub_7100D7EA7C(Unk_71024dccf8* filter) {
    if (!_2e8)
        return;

    if (_2e8 == filter) {
        _2e8 = filter->_18;
        if (_2e8)
            _2e8->_10 = nullptr;
    } else {
        Unk_71024dccf8* prev = nullptr;
        Unk_71024dccf8* it = _2e8;
        while (it != filter) {
            prev = it;
            it = it->_18;
            if (!it)
                return;
        }
        if (prev)
            prev->_18 = filter->_18;
        if (filter->_18)
            filter->_18->_10 = prev;
    }
    filter->_18 = nullptr;
    filter->_20 = nullptr;
    filter->_10 = nullptr;
}

// NON_MATCHING: sub_7100D7EA7C is inlined here (the original calls it)
Unk_71024dccf8::~Unk_71024dccf8() {
    if (_20)
        _20->sub_7100D7EA7C(this);
}

}  // namespace ksys::act
