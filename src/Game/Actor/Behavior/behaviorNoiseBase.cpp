#include "Game/Actor/Behavior/behaviorNoiseBase.h"
#include "Game/Actor/aiUnk_71005D6D10.h"

namespace uking::behavior {

NoiseBase::NoiseBase(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void NoiseBase::calc() {
    if (_38)
        sub_71005D8D4C(mActor, m14(), true, *mIsShock_s);
}

void NoiseBase::leave() {
    _38 = false;
}

void NoiseBase::loadParams() {
    getStaticParam(&mNoiseValue_s, "NoiseValue");
    getStaticParam(&mIsShock_s, "IsShock");
}

void NoiseBase::sub_710062E9F0() {
    _38 = false;
}

void NoiseBase::sub_710062E9F8() {
    _38 = true;
}

}  // namespace uking::behavior
