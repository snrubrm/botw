#include "Game/Actor/AI/aiRegistedActor.h"
#include "Game/Actor/aiUnk_71025b1808.h"

namespace uking::ai {

RegistedActor::RegistedActor(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RegistedActor::~RegistedActor() = default;

bool RegistedActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RegistedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* unit = sead::DynamicCast<Unk_71025b1808>(
        *static_cast<Unk_71025afb58**>(mRegistedActorUnit_a));
    s32 count = 0;
    if (unit) {
        for (auto& entry : unit->_8.mEntries)
            count += entry.link.hasProcInCalcState();
    }
    m34(count, params);
}

void RegistedActor::calc_() {}

void RegistedActor::m34(int num, ksys::act::ai::InlineParamPack* params) {}

void RegistedActor::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RegistedActor::loadParams_() {
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

bool RegistedActor::isFailed() const {
    return getCurrentChild()->isFailed() || mFlags.isOn(Flag::Failed);
}

bool RegistedActor::isFinished() const {
    return getCurrentChild()->isFinished() || mFlags.isOn(Flag::Finished);
}

}  // namespace uking::ai
