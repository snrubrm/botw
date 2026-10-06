#include "Game/AI/Action/actionResetGimmick.h"
#include "Game/gameResetter.h"

namespace uking::action {

ResetGimmick::ResetGimmick(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ResetGimmick::~ResetGimmick() = default;

bool ResetGimmick::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ResetGimmick::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 option = *mSystemResetOption_d;
    Resetter::instance()->startReset(ResetType{0}, ResetOption{option == 3 ? 0 : option}, mAdditionalResetActor_d,
                                    *mIsResetCamera_d, option == 3);
}

void ResetGimmick::leave_() {
    ksys::act::ai::Action::leave_();
}

void ResetGimmick::loadParams_() {
    getDynamicParam(&mSystemResetOption_d, "SystemResetOption");
    getDynamicParam(&mIsResetCamera_d, "IsResetCamera");
    getDynamicParam(&mAdditionalResetActor_d, "AdditionalResetActor");
}

void ResetGimmick::calc_() {
    if (isFinished() || isFailed())
        return;
    if (Resetter::instance()->finishedReset())
        setFinished();
}

}  // namespace uking::action
