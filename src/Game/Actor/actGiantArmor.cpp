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

void GiantArmor::sub_7100029AF8(f32* out_scale, s32* out_level,
                              const ai::Unk_71023f36d8::Info* info) {
    if (_c10) {
        _c10->m4(out_scale, out_level, info);
        return;
    }
    const f32 scale = getParam()->getRes().mGParamList->getGiantArmor()->mDamageScale.ref();
    s32 level = info->level;
    if (scale <= 0.0f)
        level = 1;
    if (out_scale)
        *out_scale = scale;
    if (out_level)
        *out_level = level;
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
