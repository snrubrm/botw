#include "Game/AI/Action/actionIncreaseNumKorokNuts.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

IncreaseNumKorokNuts::IncreaseNumKorokNuts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IncreaseNumKorokNuts::~IncreaseNumKorokNuts() = default;

bool IncreaseNumKorokNuts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreaseNumKorokNuts::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IncreaseNumKorokNuts::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreaseNumKorokNuts::loadParams_() {
    getStaticParam(&mActorName_s, "ActorName");
    getDynamicParam(&mValue_d, "Value");
}

void IncreaseNumKorokNuts::calc_() {
    if (isFinished() || isFailed() || ui::sub_7100A96F6C())
        return;
    setFinished();
}

}  // namespace uking::action
