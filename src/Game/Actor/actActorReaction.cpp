#include "Game/Actor/actActorReaction.h"
#include <basis/seadNew.h>

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
