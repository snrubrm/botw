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

}  // namespace ksys::act
