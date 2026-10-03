#include "Game/AI/AI/aiTargetActorGrabAdapter.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetActorGrabAdapter::TargetActorGrabAdapter(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetActorGrabAdapter::~TargetActorGrabAdapter() = default;

bool TargetActorGrabAdapter::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetActorGrabAdapter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    sendMessage(*acc.getMessageTransceiverId(), ksys::MessageType(0x8000001), mActor);
    sead::Vector3f pos;
    acc.getActorMtx().getTranslation(pos);
    pack.addActor(*mTargetActor_d, "TargetActor", -1);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("行動", &pack);
}

void TargetActorGrabAdapter::calc_() {
    auto* child = getCurrentChild();
    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(mTargetActor_d, &acc);
    sead::Vector3f pos;
    acc.getActorMtx().getTranslation(pos);
    child->setDynamicParam(pos, "TargetPos");
    child->setDynamicParamImpl(*mTargetActor_d, "TargetActor", &ksys::act::ai::ParamPack::setActor);
}

void TargetActorGrabAdapter::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetActorGrabAdapter::loadParams_() {
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

bool TargetActorGrabAdapter::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetActorGrabAdapter::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

}  // namespace uking::ai
