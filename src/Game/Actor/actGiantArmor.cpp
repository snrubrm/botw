#include "Game/Actor/actGiantArmor.h"
#include <basis/seadNew.h>

namespace uking::act {

GiantArmor::GiantArmor(const CreateArg& arg) : DynamicActor(arg) {}

ksys::act::BaseProc* GiantArmor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) GiantArmor(arg);
}

void GiantArmor::initMaybe() {
    _c18 = 0;
    _c08 = 0;
    DynamicActor::initMaybe();
}

ksys::act::Actor* GiantArmor::m31() {
    return sead::DynamicCast<Actor>(_be8.getProc(nullptr, nullptr));
}

bool GiantArmor::canWakeUp_() {
    if (!Actor::canWakeUp_())
        return false;
    auto* actor = sead::DynamicCast<Actor>(_b90._40.getProc(nullptr, nullptr));
    if (actor && actor->getState() != State::Calc)
        return false;
    return true;
}

}  // namespace uking::act
