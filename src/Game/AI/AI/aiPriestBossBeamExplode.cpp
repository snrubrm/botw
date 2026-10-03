#include "Game/AI/AI/aiPriestBossBeamExplode.h"
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

PriestBossBeamExplode::PriestBossBeamExplode(const InitArg& arg) : BeamExplodeEitherHit(arg) {}

PriestBossBeamExplode::~PriestBossBeamExplode() = default;

bool PriestBossBeamExplode::init_(sead::Heap* heap) {
    return BeamExplodeEitherHit::init_(heap);
}

void PriestBossBeamExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplodeEitherHit::enter_(params);
}

void PriestBossBeamExplode::calc_() {
    BeamExplodeEitherHit::calc_();
    if (!isCurrentChild("着弾前"))
        return;

    auto* beam = sead::DynamicCast<act::BeamBase>(mActor);
    if (!beam)
        return;

    const sead::Vector3f beam_pos = beam->_c68;
    const sead::Vector3f player_pos = getPlayerPosition();
    const f32 player_dist = (beam_pos - player_pos).length();
    f32 max_dist;
    if (player_dist <= f32(*mMaxDistanceChangeableBorder_s))
        max_dist = f32(*mMaxDistanceChangeableBorder_s + *mMaxDistanceChangeableRevise_s);
    else
        max_dist = player_dist + f32(*mMaxDistanceChangeableRevise_s);

    if ((mActor->getMtx().getTranslation() - beam_pos).length() >= max_dist)
        m34();
}

void PriestBossBeamExplode::leave_() {
    BeamExplodeEitherHit::leave_();
}

void PriestBossBeamExplode::loadParams_() {
    BeamExplodeEitherHit::loadParams_();
    getStaticParam(&mMaxDistance_s, "MaxDistance");
    getStaticParam(&mMaxDistanceChangeableBorder_s, "MaxDistanceChangeableBorder");
    getStaticParam(&mMaxDistanceChangeableRevise_s, "MaxDistanceChangeableRevise");
}

bool PriestBossBeamExplode::handleMessage_(const ksys::Message* message) {
    if (message->getType() == 0x8000039 && isCurrentChild("着弾前"))
        m34();
    return true;
}

}  // namespace uking::ai
