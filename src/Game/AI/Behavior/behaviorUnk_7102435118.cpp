#include "Game/AI/Behavior/behaviorUnk_7102435118.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::behavior {

Unk_7102435118::Unk_7102435118(const InitArg& arg) : CreateEaselBase(arg) {}

Unk_7102435118::~Unk_7102435118() = default;

bool Unk_7102435118::m6(sead::Heap* heap) {
    return CreateEaselBase::m6(heap);
}

void Unk_7102435118::m7() {
    CreateEaselBase::m7();
}

void Unk_7102435118::m8() {
    CreateEaselBase::m8();
}

void Unk_7102435118::m9() {
    CreateEaselBase::m9();
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
