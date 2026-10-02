#include "Game/AI/Behavior/behaviorNoise.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

Noise::Noise(const InitArg& arg) : NoiseBase(arg) {}

bool Noise::m6(sead::Heap* heap) {
    return _48.sub_7100D78564(heap);
}

void Noise::m7() {
    NoiseBase::m7();
}

void Noise::m8() {
    if (auto* owner = mActor->get548()) {
        _48.setRadius(*mSensorRadius_s);
        owner->sub_7100D783E4(&_48);
    }
    sub_710062E9F0();
}

void Noise::m9() {
    sub_710062DF30();
    NoiseBase::m9();
}

void Noise::loadParams() {
    NoiseBase::loadParams();
    getStaticParam(&mSensorRadius_s, "SensorRadius");
}

Noise::~Noise() {
    _48.sub_7100D786EC();
}

void Noise::sub_710062DF30() {
    if (auto* owner = mActor->get548())
        owner->sub_7100D78444(&_48);
}

}  // namespace uking::behavior
