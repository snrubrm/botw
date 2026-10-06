#include "Game/AI/Action/actionEatForSunazarashiSPC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtBaseProcLinkForEvent.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Event/evtMetadata.h"

namespace uking::action {

EatForSunazarashiSPC::EatForSunazarashiSPC(const InitArg& arg) : HorseEatAction(arg) {}

EatForSunazarashiSPC::~EatForSunazarashiSPC() = default;

bool EatForSunazarashiSPC::init_(sead::Heap* heap) {
    return HorseEatAction::init_(heap);
}

void EatForSunazarashiSPC::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseEatAction::enter_(params);
}

// NON_MATCHING: stack layout only (the original keeps an extra 8-byte local below the CallArg, and shares the Bit
// enum's slot with the Metadata) and the operand order of the `1 << bit` shift.
void EatForSunazarashiSPC::leave_() {
    HorseEatAction::leave_();
    if (!mPrevEatActorName_a)
        return;
    if (isFinished() && _58.isOn(sead::BitFlag8::makeMask(Bit(Bit::_0))) && mActor->checkBasicSig()) {
        auto* manager = ksys::evt::Manager::instance();
        if (!manager)
            return;
        ksys::evt::Metadata metadata("Animal_SunazarashiSP_C", "EatEnd", "");
        ksys::evt::CallArg arg;
        arg._31 = true;
        arg._32 = false;
        arg._33 = true;
        arg.metadata = &metadata;
        arg.proc = mActor;
        manager->callEvent(arg);
    } else {
        static_cast<sead::BufferedSafeString*>(mPrevEatActorName_a)->clear();
    }
}

void EatForSunazarashiSPC::loadParams_() {
    HorseEatAction::loadParams_();
    getAITreeVariable(&mPrevEatActorName_a, "PrevEatActorName");
}

void EatForSunazarashiSPC::calc_() {
    HorseEatAction::calc_();
}

}  // namespace uking::action
