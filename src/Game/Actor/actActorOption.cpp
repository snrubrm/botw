#include "Game/Actor/actActorOption.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

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

ksys::act::BaseProcLink& sub_7100000610(const ksys::act::ActorConstDataAccess& accessor) {
    auto* option = sead::DynamicCast<ActorOption>(accessor.getProc());
    if (!option)
        return ksys::act::getDummyBaseProcLink();
    return option->_b90;
}

ksys::act::Actor* ActorOption::m31() {
    return sead::DynamicCast<Actor>(_b90.getProc(nullptr, nullptr));
}

ksys::act::Actor* ActorOption::m48() {
    return sead::DynamicCast<Actor>(_b90.getProc(nullptr, nullptr));
}

}  // namespace uking::act
