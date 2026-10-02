#include "Game/AI/AI/aiGiantStoneShootAngrySelect.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"

namespace uking::ai {

GiantStoneShootAngrySelect::GiantStoneShootAngrySelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GiantStoneShootAngrySelect::~GiantStoneShootAngrySelect() = default;

bool GiantStoneShootAngrySelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool GiantStoneShootAngrySelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool GiantStoneShootAngrySelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantStoneShootAngrySelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* handle = *mIgniteHandle_d;
    if (handle && handle->isProcReady() &&
        (_50 || sead::GlobalRandom::instance()->getS32Range(0, 100) >= *mThrowableAngryRate_s)) {
        sub_71003FAC88();
        return;
    }
    _50 = true;
    changeChild("怒り");
}

void GiantStoneShootAngrySelect::calc_() {}

void GiantStoneShootAngrySelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantStoneShootAngrySelect::loadParams_() {
    getStaticParam(&mThrowableAngryRate_s, "ThrowableAngryRate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
}

void GiantStoneShootAngrySelect::sub_71003FAC88() {
    _50 = false;
    ksys::act::ai::InlineParamPack params;
    params.addVec3(*mTargetPos_d, "TargetPos", -1);
    params.addPointer(*mIgniteHandle_d, "IgniteHandle", ksys::AIDefParamType::BaseProcHandle, -1);
    changeChild("投石", &params);
}

}  // namespace uking::ai
