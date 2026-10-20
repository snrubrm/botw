#include "Game/Actor/actActorOption.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "KingSystem/ActorSystem/actUnk_7102459df8.h"

namespace uking::act {

ActorOption::ActorOption(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 1;
}

ksys::act::BaseProc* ActorOption::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) ActorOption(arg);
}

bool ActorOption::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!constructActorAtk(heap))
        return false;
    if (!initField858(heap))
        return false;
    if (m126() && _858 && !_858->m4(heap, nullptr))
        return false;
    if (!m157(heap))
        return false;
    _ba8 = new (heap, 8) ksys::act::ModelBindInfo();
    if (!_ba8)
        return false;
    sub_71011DA824(_ba8);
    if (getDamageMgr())
        _ba0 = new LinkInfo;
    return true;
}

void ActorOption::preDelete2_(const PreDeleteArg& arg) {
    if (_ba0) {
        delete _ba0;
        _ba0 = nullptr;
    }
    if (_ba8) {
        sub_71011DA834(_ba8);
        delete _ba8;
        _ba8 = nullptr;
    }
    if (_858) {
        _858->m6();
        delete _858;
        _858 = nullptr;
    }
    m158();
    sub_71006DC81C();
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
