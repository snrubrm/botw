#include "Game/AI/AI/aiAirOctaBurnReaction.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/System/VFR.h"

namespace uking::ai {

AirOctaBurnReaction::AirOctaBurnReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaBurnReaction::~AirOctaBurnReaction() = default;

bool AirOctaBurnReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool AirOctaBurnReaction::sub_71002FAA64() {
    ksys::act::ActorConstDataAccess accessor;
    bool result = false;
    if (ksys::act::acquireActor(
            &sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a)->mBaseProcLink2, &accessor) &&
        accessor.hasProc()) {
        result = accessor.sub_7100D13448(-1);
    }
    return result;
}

// NON_MATCHING: instruction scheduling only (the original materialises the child name address before the
// merged `_60` / `_64` store; same logic)
void AirOctaBurnReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    bool acquired;
    ksys::act::BaseProc* proc;
    {
        ksys::act::ActorConstDataAccess accessor;
        acquired = ksys::act::acquireActor(
            &sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a)->mBaseProcLink2, &accessor);
        proc = accessor.getProc();
    }
    if (acquired && proc && sub_71002FAA64()) {
        _60 = 1;
        _64 = 0.0f;
        changeChild("先行動");
    } else {
        _60 = 0;
        _64 = 0.0f;
        changeChild("後行動");
    }
    _68 = *mChangeRandTime_s * sead::GlobalRandom::instance()->getF32();
    _6c = *mDisconnectTime_s + *mDisconnectRandTime_s * sead::GlobalRandom::instance()->getF32();
}

void AirOctaBurnReaction::calc_() {
    _64 += ksys::VFR::instance()->getRawDeltaTime();
    getCurrentChild();
    switch (_60) {
    case 0:
        if (_64 > *mSingleBurnTime_s)
            setFinished();
        break;
    case 1: {
        bool acquired;
        ksys::act::BaseProc* proc;
        {
            ksys::act::ActorConstDataAccess accessor;
            acquired = ksys::act::acquireActor(
                &sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a)->mBaseProcLink2, &accessor);
            proc = accessor.getProc();
        }
        if (acquired && proc && sub_71002FAA64()) {
            if (isCurrentChild("先行動") && _64 > _68) {
                changeChild("後行動");
                _64 = 0;
            }
        } else {
            _60 = 2;
            _64 = 0.0f;
            changeChild("後行動");
        }
        break;
    }
    case 2:
        if (_64 > _6c)
            setFinished();
        break;
    }
}

void AirOctaBurnReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AirOctaBurnReaction::loadParams_() {
    getStaticParam(&mDisconnectTime_s, "DisconnectTime");
    getStaticParam(&mDisconnectRandTime_s, "DisconnectRandTime");
    getStaticParam(&mSingleBurnTime_s, "SingleBurnTime");
    getStaticParam(&mChangeRandTime_s, "ChangeRandTime");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
