#include "Game/AI/AI/aiOctarockRootBase.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

OctarockRootBase::OctarockRootBase(const InitArg& arg) : EnemyRoot(arg) {}

OctarockRootBase::~OctarockRootBase() {
    auto* child = mActor->getConnectedCalcChild();
    if (child && child->isSleep())
        child->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

bool OctarockRootBase::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void OctarockRootBase::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void OctarockRootBase::calc_() {
    EnemyRoot::calc_();
}

void OctarockRootBase::leave_() {
    EnemyRoot::leave_();
}

void OctarockRootBase::loadParams_() {
    EnemyRoot::loadParams_();
}

}  // namespace uking::ai
