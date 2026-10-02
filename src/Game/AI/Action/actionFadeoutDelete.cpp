#include "Game/AI/Action/actionFadeoutDelete.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

FadeoutDelete::FadeoutDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FadeoutDelete::~FadeoutDelete() = default;

bool FadeoutDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FadeoutDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    const f32 time = *mFadeoutTime_s;
    _30 = ksys::Timer(time, time);
    if (auto* attention = mActor->getAttention())
        attention->disableAllClients();
}

void FadeoutDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void FadeoutDelete::loadParams_() {
    getStaticParam(&mFadeoutTime_s, "FadeoutTime");
    getStaticParam(&mDeleteType_s, "DeleteType");
}

// NON_MATCHING: the original keeps the mActor load in both branches (branch layout)
void FadeoutDelete::calc_() {
    _30.update();
    if (_30.value <= sead::Mathf::epsilon()) {
        if (*mDeleteType_s == 1)
            mActor->deleteEx(ksys::act::Actor::DeleteType::_4, ksys::act::BaseProc::DeleteReason::_0);
        else
            mActor->deleteEx(ksys::act::Actor::DeleteType::_1, ksys::act::BaseProc::DeleteReason::_0);
    }
}

}  // namespace uking::action
