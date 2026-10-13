#include "Game/Actor/actGiantArmor.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGiantArmor.h"

namespace uking::act {

GiantArmor::GiantArmor(const CreateArg& arg) : DynamicActor(arg) {}

ksys::act::BaseProc* GiantArmor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) GiantArmor(arg);
}

f32 GiantArmor::sub_7100029B54() const {
    return getParam()->getRes().mGParamList->getGiantArmor()->mDamageScale.ref();
}

bool GiantArmor::sub_7100029E7C(Actor* owner, s32 index) {
    const auto lock = sead::makeScopedLock(_b90._0);
    _b90._40.acquire(owner, false);
    _be0 = index;
    return true;
}

void GiantArmor::initMaybe() {
    _c18 = 0;
    _c08 = 0;
    DynamicActor::initMaybe();
}

ksys::act::Actor* GiantArmor::m31() {
    return sead::DynamicCast<Actor>(_be8.getProc(nullptr, nullptr));
}

void GiantArmor::updatePositionMaybe() {
    DynamicActor::updatePositionMaybe();
    if (auto* actor = sead::DynamicCast<Actor>(_be8.getProc(nullptr, this)))
        sub_71011CCB1C(actor->m139());
}

void GiantArmor::m73() {
    DynamicActor::m73();
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
