#include "Game/AI/AI/aiPriestBossMeta.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

PriestBossMeta::PriestBossMeta(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestBossMeta::~PriestBossMeta() = default;

Unk_7102450fa8* PriestBossMeta::sub_7100525A88() {
    return sead::DynamicCast<Unk_7102450fa8>(
        *static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
}

bool PriestBossMeta::sub_7100525B18(int idx, ksys::act::ActorConstDataAccess* accessor) {
    return sub_7100525A88()->sub_71007194D4(idx, accessor);
}

bool PriestBossMeta::sub_7100525BC0(int idx, ksys::act::BaseProcLink* link) {
    ksys::act::ActorConstDataAccess accessor;
    if (sub_7100525A88()->sub_71007194D4(idx, &accessor))
        accessor.linkAcquire(link);
    return link->hasProc();
}

bool PriestBossMeta::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestBossMeta::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestBossMeta::calc_() {}

void PriestBossMeta::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestBossMeta::loadParams_() {
    getAITreeVariable(&mMetaAILife_a, "MetaAILife");
    getAITreeVariable(&mMetaAIMaxLife_a, "MetaAIMaxLife");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

}  // namespace uking::ai
