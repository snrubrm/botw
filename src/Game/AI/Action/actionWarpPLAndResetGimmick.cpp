#include "Game/AI/Action/actionWarpPLAndResetGimmick.h"
#include <prim/seadSafeString.h>
#include "Game/gameResetter.h"
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

WarpPLAndResetGimmick::WarpPLAndResetGimmick(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpPLAndResetGimmick::~WarpPLAndResetGimmick() = default;

bool WarpPLAndResetGimmick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPLAndResetGimmick::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!Resetter::instance()->sub_71007D2320(nullptr, ResetOption{*mSystemResetOption_d}, mStartPosName_d,
                                              mAdditionalResetActor_d, false)) {
        sead::FixedSafeString<128> flow;
        sead::FixedSafeString<128> entry;
        getActiveEventFlowPath_0(mActor, &flow, &entry);
        setFailed();
    }
}

void WarpPLAndResetGimmick::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPLAndResetGimmick::loadParams_() {
    getDynamicParam(&mSystemResetOption_d, "SystemResetOption");
    getDynamicParam(&mStartPosName_d, "StartPosName");
    getDynamicParam(&mAdditionalResetActor_d, "AdditionalResetActor");
}

void WarpPLAndResetGimmick::calc_() {
    if (isFinished() || isFailed())
        return;
    if (Resetter::instance()->finishedReset())
        setFinished();
}

}  // namespace uking::action
