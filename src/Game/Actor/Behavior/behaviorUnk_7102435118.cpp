#include "Game/Actor/Behavior/behaviorUnk_7102435118.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

Unk_7102435118::Unk_7102435118(const InitArg& arg) : CreateEaselBase(arg) {}

Unk_7102435118::~Unk_7102435118() = default;

bool Unk_7102435118::init_(sead::Heap* heap) {
    return CreateEaselBase::init_(heap);
}

void Unk_7102435118::calc() {
    CreateEaselBase::calc();
}

void Unk_7102435118::enter() {
    CreateEaselBase::enter();
}

void Unk_7102435118::leave() {
    CreateEaselBase::leave();
}

void Unk_7102435118::loadParams() {
    CreateEaselBase::loadParams();
}

const char* Unk_7102435118::m14() {
    const char* name;
    if (mActor->getMapObjIter().tryGetParamStringByKey(&name, "ActorName"))
        return name;
    return &sead::SafeString::cNullChar;
}

}  // namespace uking::behavior
