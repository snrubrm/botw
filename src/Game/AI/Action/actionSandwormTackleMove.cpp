#include "Game/AI/Action/actionSandwormTackleMove.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SandwormTackleMove::SandwormTackleMove(const InitArg& arg) : AtkTackleMove(arg) {}

SandwormTackleMove::~SandwormTackleMove() {
    _130.sub_71F858();
}

bool SandwormTackleMove::init_(sead::Heap* heap) {
    if (!AtkTackleMove::init_(heap))
        return false;
    return _130.sub_71F6DC(heap);
}

void SandwormTackleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AtkTackleMove::enter_(params);
}

void SandwormTackleMove::leave_() {
    AtkTackleMove::leave_();
    _130.sub_71FEFC();
}

void SandwormTackleMove::loadParams_() {
    AtkTackleMove::loadParams_();
    getStaticParam(&mTargetSandOffset_s, "TargetSandOffset");
    getStaticParam(&mSandOffsetSpeed_s, "SandOffsetSpeed");
    getStaticParam(&mEatRadius_s, "EatRadius");
    getStaticParam(&mEatNode_s, "EatNode");
    getStaticParam(&mEatOffset_s, "EatOffset");
}

void SandwormTackleMove::calc_() {
    AtkTackleMove::calc_();
}

bool SandwormTackleMove::handleAck_(const ksys::MessageAck* ack) {
    return _130.sub_71FF70(ack);
}

bool SandwormTackleMove::isFailed() const {
    return false;
}

void SandwormTackleMove::m32(sead::Vector3f* pos) {
    if (!_f4) {
        TackleMove::m32(pos);
        return;
    }
    pos->setMul(mActor->getMtx(), sead::Vector3f::ez * 10.0f);
}

f32 SandwormTackleMove::m34() {
    return *mSpeed_s * _f0;
}

f32 SandwormTackleMove::m35() {
    return 0.3f;
}

void SandwormTackleMove::m36() {}

void SandwormTackleMove::m37() {}

bool SandwormTackleMove::m38() {
    return _f5;
}

}  // namespace uking::action
