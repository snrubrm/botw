#include "Game/AI/Action/actionForkAITreeValWeakPointTimer.h"
#include "Game/AI/aiUnk_71025b27b8.h"

namespace uking::action {

ForkAITreeValWeakPointTimer::ForkAITreeValWeakPointTimer(const InitArg& arg) : Fork(arg) {}

ForkAITreeValWeakPointTimer::~ForkAITreeValWeakPointTimer() = default;

bool ForkAITreeValWeakPointTimer::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkAITreeValWeakPointTimer::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    auto* counter =
        sead::DynamicCast<Unk_71025b27b8>(*static_cast<Unk_71025afb58**>(mWeakPointCounter_a));
    if (counter && counter->_8 <= 0.0f)
        counter->_8 = *mTimer_s;
}

void ForkAITreeValWeakPointTimer::leave_() {
    Fork::leave_();
}

void ForkAITreeValWeakPointTimer::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mTimer_s, "Timer");
    getAITreeVariable(&mWeakPointCounter_a, "WeakPointCounter");
}

void ForkAITreeValWeakPointTimer::calc_() {
    Fork::calc_();
    auto* counter =
        sead::DynamicCast<Unk_71025b27b8>(*static_cast<Unk_71025afb58**>(mWeakPointCounter_a));
    if (!counter)
        setFailed();
    else if (counter->_8 <= 0.0f)
        setFinished();
}

}  // namespace uking::action
