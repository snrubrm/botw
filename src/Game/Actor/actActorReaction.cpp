#include "Game/Actor/actActorReaction.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorUnk6b8.h"

namespace uking::act {

ActorReaction::ActorReaction(const CreateArg& arg) : Actor(arg) {
    _1c0 = 2;
    getJobHandler(ksys::act::JobType::PreCalc) = nullptr;
    getJobHandler(ksys::act::JobType::Calc1) = nullptr;
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
}

ActorReaction::~ActorReaction() = default;

ksys::act::BaseProc* ActorReaction::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) ActorReaction(arg);
}

}  // namespace uking::act

Unk_71024efd58::Unk_71024efd58(const InitArg& arg) : _8(arg.actor), _10(arg._8) {}

Unk_71024efd58::~Unk_71024efd58() = default;

namespace ksys::act {

// Keep the native vptr store, following GameDataFlagSelector (upstream commit 96101229).
ActorUnk6b8::~ActorUnk6b8() { ; }

void ActorUnk6b8::m8() {}

}  // namespace ksys::act
