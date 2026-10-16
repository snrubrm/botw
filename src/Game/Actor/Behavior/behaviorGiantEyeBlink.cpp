#include "Game/Actor/Behavior/behaviorGiantEyeBlink.h"

namespace uking::behavior {

GiantEyeBlink::GiantEyeBlink(const InitArg& arg) : EyeBlink(arg) {}

GiantEyeBlink::~GiantEyeBlink() = default;

bool GiantEyeBlink::init_(sead::Heap* heap) {
    return EyeBlink::init_(heap);
}

void GiantEyeBlink::calc() {
    EyeBlink::calc();
}

void GiantEyeBlink::enter() {
    EyeBlink::enter();
}

void GiantEyeBlink::leave() {
    EyeBlink::leave();
}

void GiantEyeBlink::loadParams() {
    EyeBlink::loadParams();
}

}  // namespace uking::behavior
