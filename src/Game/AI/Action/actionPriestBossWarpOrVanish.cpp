#include "Game/AI/Action/actionPriestBossWarpOrVanish.h"
#include "Game/AI/aiUnk_7102450fa8.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

PriestBossWarpOrVanish::PriestBossWarpOrVanish(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PriestBossWarpOrVanish::~PriestBossWarpOrVanish() = default;

bool PriestBossWarpOrVanish::sub_710022134C(int idx, ksys::act::ActorConstDataAccess* accessor) {
    auto* unit =
        sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
    return unit->sub_71007194D4(idx, accessor);
}

bool PriestBossWarpOrVanish::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossWarpOrVanish::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossWarpOrVanish::leave_() {
    ksys::act::ai::Action::leave_();
}

void PriestBossWarpOrVanish::loadParams_() {
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void PriestBossWarpOrVanish::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
