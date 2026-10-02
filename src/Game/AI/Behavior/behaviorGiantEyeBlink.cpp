#include "Game/AI/Behavior/behaviorGiantEyeBlink.h"

namespace uking::behavior {

GiantEyeBlink::GiantEyeBlink(const InitArg& arg) : EyeBlink(arg) {}

GiantEyeBlink::~GiantEyeBlink() = default;

bool GiantEyeBlink::m6(sead::Heap* heap) {
    return EyeBlink::m6(heap);
}

void GiantEyeBlink::m7() {
    EyeBlink::m7();
}

void GiantEyeBlink::m8() {
    EyeBlink::m8();
}

void GiantEyeBlink::m9() {
    EyeBlink::m9();
}

void GiantEyeBlink::loadParams() {
    EyeBlink::loadParams();
}

}  // namespace uking::behavior
