#include "Game/Actor/Behavior/behaviorNoise.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

Noise::Noise(const InitArg& arg) : NoiseBase(arg) {}

bool Noise::init_(sead::Heap* heap) {
    return _48.sub_7100D78564(heap);
}

void Noise::calc() {
    NoiseBase::calc();
}

void Noise::enter() {
    if (auto* owner = mActor->get548()) {
        _48.setRadius(*mSensorRadius_s);
        owner->sub_7100D783E4(&_48);
    }
    sub_710062E9F0();
}

void Noise::leave() {
    sub_710062DF30();
    NoiseBase::leave();
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
