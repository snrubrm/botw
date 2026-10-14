#include "Game/Actor/actActorOption.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace uking::act {

ActorOption::ActorOption(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 1;
}

ksys::act::BaseProc* ActorOption::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) ActorOption(arg);
}

void ActorOption::sub_71000003F4(ksys::act::Actor* source, const sead::SafeString& bone,
                                const sead::Vector3f& translation, const sead::Vector3f& rotation) {
    _b90.acquire(source, false);
    if (auto* bind = sead::DynamicCast<ksys::act::ModelBindInfo>(_ba8)) {
        bind->x(source);
        bind->_28 = bone.cstr();
        bind->_30.getKey().reset();
        bind->_68.makeRT(rotation, translation);
    }
}

bool ActorOption::shouldUnload(s32* a1) {
    if (_b90.hasProc())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

ksys::act::BaseProcLink& sub_7100000610(const ksys::act::ActorLinkConstDataAccess& accessor) {
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
