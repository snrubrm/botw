#include "Game/Actor/actHorseObject.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"

namespace uking::act {

HorseObject::HorseObject(const CreateArg& arg) : Actor(arg) {}

bool HorseObject::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    return true;
}

ksys::act::Actor* HorseObject::m31() {
    return sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr));
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
    return sead::DynamicCast<Actor>(_840.getProc(nullptr, nullptr));
}

bool HorseReins::shouldUnload(s32* a1) {
    if (_840.hasProc())
        return false;
    return shouldUnloadBecauseOfDistance(a1);
}

void HorseReins::initMaybe() {
    if (_868 & 4)
        clearFadeInCreate();
    mActorFlags2.reset(ActorFlag2::_20);
    _868 = 3;
    _860 = 0;
    Unk_710260af28::instance()->sub_7100F1E2F4(mModel, sead::Color4f{0.0f, 0.0f, 0.0f, 0.0f});
    _864 = 0;
    Unk_710260af28::instance()->sub_7100F1EAF8(mModel, 0.0f);
}

void HorseReins::updatePositionMaybe() {
    if (_868 & 8)
        mActorFlags2.set(ActorFlag2::_20);
}

}  // namespace uking::act
