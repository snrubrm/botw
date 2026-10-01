#include "Game/AI/AI/aiSeqOctarockWigReaction.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SeqOctarockWigReaction::SeqOctarockWigReaction(const InitArg& arg) : SeqThreeAction(arg) {}

SeqOctarockWigReaction::~SeqOctarockWigReaction() = default;

bool SeqOctarockWigReaction::init_(sead::Heap* heap) {
    return SeqThreeAction::init_(heap);
}

void SeqOctarockWigReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqThreeAction::enter_(params);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_80000000);
}

void SeqOctarockWigReaction::calc_() {
    SeqThreeAction::calc_();
}

void SeqOctarockWigReaction::leave_() {
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_80000000);
    SeqThreeAction::leave_();
}

void SeqOctarockWigReaction::loadParams_() {
    SeqThreeAction::loadParams_();
}

}  // namespace uking::ai
