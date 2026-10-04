#include "Game/Actor/actHorseObject.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"

namespace uking::act {

Unk_71024ebb00::Unk_71024ebb00() : ActorBindSet(16, mStorage) {}

Unk_71024ebb00::~Unk_71024ebb00() {
    mEntries = nullptr;
}

HorseObject::HorseObject(const CreateArg& arg) : Actor(arg) {}

HorseObject::~HorseObject() = default;

ksys::act::BaseProc* HorseObject::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) HorseObject(arg);
}

void HorseObject::initMaybe() {
    if (_1410 & 1)
        clearFadeInCreate();
    _1410 = 0;
    _850.resetAll();
    sub_71011DA824(&_850);
    _1408 = 0;
    Unk_710260af28::instance()->sub_7100F1E2F4(mModel, sead::Color4f{0.0f, 0.0f, 0.0f, 0.0f});
    _140c = 0;
    Unk_710260af28::instance()->sub_7100F1EAF8(mModel, 0.0f);
}

bool HorseObject::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

// NON_MATCHING: operand order of the merged `and` of the flag byte
void HorseObject::m70() {
    f32 value;
    if (auto* horse = sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr)))
        value = horse->m139();
    sub_71011CCB1C(value);
    if ((_1410 & 6) == 6) {
        _1410 &= ~6;
    } else if (_1410 & 2) {
        mActorFlags2.reset(ActorFlag2::_20);
        _1410 &= ~2;
    } else if (_1410 & 4) {
        mActorFlags2.set(ActorFlag2::_20);
        _1410 &= ~4;
    }
}

ksys::act::Actor* HorseObject::m31() {
    return sead::DynamicCast<ksys::act::Actor>(_840.getProc(nullptr, nullptr));
}

bool HorseObject::shouldUnload(s32* a1) {
    if (_840.hasProc())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

HorseReins::HorseReins(const CreateArg& arg) : Actor(arg) {}

HorseReins::~HorseReins() = default;

ksys::act::BaseProc* HorseReins::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) HorseReins(arg);
}

bool HorseReins::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

ksys::act::Actor* HorseReins::m31() {
    return sead::DynamicCast<ksys::act::Actor>(_840.getProc(nullptr, nullptr));
}

bool HorseReins::shouldUnload(s32* a1) {
    if (_840.hasProc())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

void HorseReins::initMaybe() {
    if (_868.isOn(4))
        clearFadeInCreate();
    mActorFlags2.reset(ActorFlag2::_20);
    _868.setDirect(3);
    _860 = 0;
    Unk_710260af28::instance()->sub_7100F1E2F4(mModel, sead::Color4f{0.0f, 0.0f, 0.0f, 0.0f});
    _864 = 0;
    Unk_710260af28::instance()->sub_7100F1EAF8(mModel, 0.0f);
}

ksys::act::Actor* HorseReins::sub_7100E7BA64() {
    return sead::DynamicCast<ksys::act::Actor>(_840.getProc(nullptr, nullptr));
}

void HorseReins::sub_7100E7BC10(ksys::act::BaseProc* horse) {
    _840.acquire(horse, false);
}

void HorseReins::updatePositionMaybe() {
    if (_868.isOn(8))
        mActorFlags2.set(ActorFlag2::_20);
}

}  // namespace uking::act
