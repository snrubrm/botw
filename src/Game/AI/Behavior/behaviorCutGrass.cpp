#include "Game/AI/Behavior/behaviorCutGrass.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Terrain/teraSystem.h"

namespace uking::behavior {

CutGrass::CutGrass(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

CutGrass::~CutGrass() = default;

bool CutGrass::m6(sead::Heap* heap) {
    return true;
}

// NON_MATCHING: the compiler shares the position and parameter setup between the two grass calls.
void CutGrass::m7() {
    auto* terrain = ksys::tera::Terrain::instance();
    if (!terrain || !terrain->isGrassEnabled())
        return;
    const bool call_effect = *mIsCallEffect_s;
    auto* grass = terrain->sub_710114DE4C();
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    if (call_effect)
        grass->sub_7101151064(&position, *mCutRange_s, *mIntensity_s, *mIsCallEffect_s, false, true);
    else
        grass->sub_7101150F88(&position, *mCutRange_s, *mIntensity_s, false);
}

void CutGrass::m8() {}

void CutGrass::m9() {}

void CutGrass::loadParams() {
    getStaticParam(&mCutRange_s, "CutRange");
    getStaticParam(&mIntensity_s, "Intensity");
    getStaticParam(&mIsCallEffect_s, "IsCallEffect");
}

}  // namespace uking::behavior
