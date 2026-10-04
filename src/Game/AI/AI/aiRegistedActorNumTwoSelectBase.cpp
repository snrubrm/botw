#include "Game/AI/AI/aiRegistedActorNumTwoSelectBase.h"
#include "Game/AI/aiUnk_71025b1808.h"

namespace uking::ai {

RegistedActorNumTwoSelectBase::RegistedActorNumTwoSelectBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RegistedActorNumTwoSelectBase::~RegistedActorNumTwoSelectBase() = default;

bool RegistedActorNumTwoSelectBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RegistedActorNumTwoSelectBase::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* unit = sead::DynamicCast<Unk_71025b1808>(
        *static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    s32 count = 0;
    if (unit) {
        for (auto& entry : unit->_8.mEntries)
            count += entry.link.hasProcInCalcState();
    }
    m34(count, params);
}

void RegistedActorNumTwoSelectBase::calc_() {}

void RegistedActorNumTwoSelectBase::m34(int num, ksys::act::ai::InlineParamPack* params) {}

void RegistedActorNumTwoSelectBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RegistedActorNumTwoSelectBase::loadParams_() {
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

bool RegistedActorNumTwoSelectBase::isFailed() const {
    return getCurrentChild()->isFailed() || mFlags.isOn(Flag::Failed);
}

bool RegistedActorNumTwoSelectBase::isFinished() const {
    return getCurrentChild()->isFinished() || mFlags.isOn(Flag::Finished);
}

}  // namespace uking::ai
