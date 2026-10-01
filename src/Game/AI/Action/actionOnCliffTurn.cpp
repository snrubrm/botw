#include "Game/AI/Action/actionOnCliffTurn.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

OnCliffTurn::OnCliffTurn(const InitArg& arg) : TurnBase(arg) {}

OnCliffTurn::~OnCliffTurn() = default;

bool OnCliffTurn::init_(sead::Heap* heap) {
    return TurnBase::init_(heap);
}

void OnCliffTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

void OnCliffTurn::leave_() {
    TurnBase::leave_();
}

void OnCliffTurn::loadParams_() {
    TurnBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void OnCliffTurn::calc_() {
    TurnBase::calc_();
}

void OnCliffTurn::m33(sead::Vector3f* up) {
    mActor->getMtx().getBase(*up, 1);
}

void OnCliffTurn::m34(sead::Vector3f* front) {
    mActor->getMtx().getBase(*front, 2);
}

void OnCliffTurn::m35(sead::Vector3f* dir) {
    dir->normalize();
}

}  // namespace uking::action
