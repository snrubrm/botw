#include "Game/AI/Action/actionPriestBossClonesSpawnForDemo.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

// NON_MATCHING: zero-store merging of _54-_5c (the original merges _58/_5c, ours _54/_58)
PriestBossClonesSpawnForDemo::PriestBossClonesSpawnForDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PriestBossClonesSpawnForDemo::~PriestBossClonesSpawnForDemo() = default;

bool PriestBossClonesSpawnForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossClonesSpawnForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossClonesSpawnForDemo::leave_() {
    auto* physics = mActor->getPhysics();
    physics->sub_7100FBDFA4(physics->get178(0));
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    sub_71007A3800(mActor);
}

void PriestBossClonesSpawnForDemo::loadParams_() {
    getDynamicParam(&mDurationFrame_d, "DurationFrame");
    getDynamicParam(&mDecelerationFrame_d, "DecelerationFrame");
    getDynamicParam(&mASName_d, "ASName");
    getDynamicParam(&mOffset_d, "Offset");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

void PriestBossClonesSpawnForDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

int PriestBossClonesSpawnForDemo::m32() {
    return 1;
}

f32 PriestBossClonesSpawnForDemo::m33(f32 t) {
    t -= 1.0f;
    return (t * t - 1.0f) + 1.0f;
}

bool PriestBossClonesSpawnForDemo::sub_7100066884() {
    return _5c >= f32(*mDurationFrame_d);
}

}  // namespace uking::action
