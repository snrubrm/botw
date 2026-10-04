#include "Game/Actor/actActorOption.h"
#include <basis/seadNew.h>

namespace uking::act {

ActorOption::ActorOption(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 1;
}

ksys::act::BaseProc* ActorOption::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) ActorOption(arg);
}

bool ActorOption::shouldUnload(s32* a1) {
    if (_b90.hasProc())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

ksys::act::Actor* ActorOption::m31() {
    return sead::DynamicCast<Actor>(_b90.getProc(nullptr, nullptr));
}

ksys::act::Actor* ActorOption::m48() {
    return sead::DynamicCast<Actor>(_b90.getProc(nullptr, nullptr));
}

}  // namespace uking::act
