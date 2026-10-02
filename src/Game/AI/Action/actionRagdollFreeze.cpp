#include "Game/AI/Action/actionRagdollFreeze.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"

namespace uking::action {

RagdollFreeze::RagdollFreeze(const InitArg& arg) : Freeze(arg) {}

RagdollFreeze::~RagdollFreeze() = default;

bool RagdollFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void RagdollFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void RagdollFreeze::leave_() {
    Freeze::leave_();
}

void RagdollFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mDownFrontCtrlOffset_s, "DownFrontCtrlOffset");
    getStaticParam(&mDownBackCtrlOffset_s, "DownBackCtrlOffset");
}

void RagdollFreeze::calc_() {
    Freeze::calc_();
    auto* actor = sead::DynamicCast<ksys::act::PlayerOrEnemy>(mActor);
    if (!actor || !actor->m151(3))
        setFinished();
}

}  // namespace uking::action
