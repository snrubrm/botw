#include "Game/AI/Action/actionForkEndByPartsActorEnd.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ForkEndByPartsActorEnd::ForkEndByPartsActorEnd(const InitArg& arg) : Fork(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ForkEndByPartsActorEnd::~ForkEndByPartsActorEnd() {
    ;
}

bool ForkEndByPartsActorEnd::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkEndByPartsActorEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
    if (!mActor->m101())
        setFailed();
}

void ForkEndByPartsActorEnd::leave_() {
    Fork::leave_();
}

void ForkEndByPartsActorEnd::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mPartsKey_s, "PartsKey");
}

void ForkEndByPartsActorEnd::calc_() {
    Fork::calc_();
    auto* parts = mActor->m101();
    if (!parts) {
        setFailed();
        return;
    }
    if (!parts->getActorPartsActor(mPartsKey_s).hasProcInCalcState())
        setEndState();
}

}  // namespace uking::action
