#include "Game/AI/Action/actionPriestBossClonesSpawn.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

PriestBossClonesSpawn::PriestBossClonesSpawn(const InitArg& arg)
    : PriestBossClonesSpawnForDemo(arg) {}

PriestBossClonesSpawn::~PriestBossClonesSpawn() = default;

bool PriestBossClonesSpawn::init_(sead::Heap* heap) {
    return PriestBossClonesSpawnForDemo::init_(heap);
}

void PriestBossClonesSpawn::enter_(ksys::act::ai::InlineParamPack* params) {
    if (mASNameForAITree_s != "default")
        setDynamicParamImpl(mASNameForAITree_s, "ASName", &ksys::act::ai::ParamPack::setString);
    PriestBossClonesSpawnForDemo::enter_(params);
    const bool no_delay = *mDelayFrame_d == 0;
    _d9 = no_delay;
    mActor->getActorFlags2().change(ksys::act::Actor::ActorFlag2::_20, no_delay);
    sub_7100066CE4(*mDelayFrame_d);
    _d8 = false;
}

void PriestBossClonesSpawn::leave_() {
    PriestBossClonesSpawnForDemo::leave_();
    sub_71002218D8();
}

void PriestBossClonesSpawn::loadParams_() {
    PriestBossClonesSpawnForDemo::loadParams_();
    getStaticParam(&mASNameForAITree_s, "ASNameForAITree");
    getDynamicParam(&mDelayFrame_d, "DelayFrame");
}

void PriestBossClonesSpawn::calc_() {
    if (_d9 && _5c >= 1.0f) {
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        _d9 = false;
    }
    PriestBossClonesSpawnForDemo::calc_();
    if (sub_7100066884())
        sub_71002218D8();
}

void PriestBossClonesSpawn::sub_71002218D8() {
    if (_d8)
        return;
    ksys::act::ActorConstDataAccess accessor;
    if (sub_71000664E4()) {
        if (sub_71000664E4()->sub_71007194CC(&accessor)) {
            auto* actor = mActor;
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_a0._18.mLock);
                _a0._18._0 = 4;
                _a0._18._18 = false;
                _a0._18.mLink.acquire(actor, false);
            }
            _a0.sub_710070DBB0(*accessor.getMessageTransceiverId(), false);
        }
    }
    _d8 = true;
}

int PriestBossClonesSpawn::m32() {
    if (sub_71000664E4())
        return !sub_71000664E4()->isFlagOn(Unk_7102450fa8::Flag::_4);
    return true;
}

}  // namespace uking::action
