#include "Game/AI/AI/aiRideHorseAI.h"
#include "Game/AI/aiUnk_7100E81220.h"
#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RideHorseAI::RideHorseAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RideHorseAI::~RideHorseAI() = default;

bool RideHorseAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RideHorseAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = 0;
    ksys::act::ActorConstDataAccess accessor;
    if (!sub_7100E81220(mActor, &accessor)) {
        setFailed();
        return;
    }

    uking::act::Unk_7100e8b2b8* rideable = accessor.getHorseOptions();
    if (rideable && rideable->_8 & 0x400) {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(*mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS", -1);
        changeChild("なだめる", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addBool(*mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS", -1);
        changeChild("乗る", &pack);
    }
}

void RideHorseAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RideHorseAI::loadParams_() {
    getDynamicParam_2(&mHasToPlayRidingOnAS_d, "HasToPlayRidingOnAS");
}

}  // namespace uking::ai
