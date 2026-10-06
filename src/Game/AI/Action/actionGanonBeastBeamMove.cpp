#include "Game/AI/Action/actionGanonBeastBeamMove.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actBeamBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

GanonBeastBeamMove::GanonBeastBeamMove(const InitArg& arg) : SimpleLineBeam(arg) {}

GanonBeastBeamMove::~GanonBeastBeamMove() = default;

bool GanonBeastBeamMove::init_(sead::Heap* heap) {
    if (!SimpleLineBeam::init_(heap))
        return false;

    auto* transceiver = &mActor->getMessageTransceiver();
    for (auto& sender : _50)
        sender._8 = transceiver;
    return true;
}

void GanonBeastBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLineBeam::enter_(params);

    _288 = *mRestNumMax_s;
    const f32 min_limit = *mRestDistMinLimit_s;
    const sead::Vector3f& player_pos = getPlayerPosition();
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    const f32 dx = player_pos.x - pos.x;
    const f32 dz = player_pos.z - pos.z;
    _27c = sead::Mathf::clamp(sead::Mathf::sqrt(dx * dx + dz * dz) * 0.5f, min_limit, *mRestDistLimit_s);
    if (sead::DynamicCast<act::LineBeam>(mActor))
        mActor->getMtx().getTranslation(_270);
    _280 = *mRestDistMinLimit_s;
    _284 = *mRestDistTime_s;
    _28c = false;
}

void GanonBeastBeamMove::leave_() {
    SimpleLineBeam::leave_();
}

void GanonBeastBeamMove::loadParams_() {
    SimpleLineBeam::loadParams_();
    getStaticParam(&mRestDistTime_s, "RestDistTime");
    getStaticParam(&mRestDistTimeAdd_s, "RestDistTimeAdd");
    getStaticParam(&mRestNumMax_s, "RestNumMax");
    getStaticParam(&mRestDistLimit_s, "RestDistLimit");
    getStaticParam(&mRestDistMinLimit_s, "RestDistMinLimit");
    getStaticParam(&mRestDistInterval_s, "RestDistInterval");
    getStaticParam(&mRestActor_s, "RestActor");
}

void GanonBeastBeamMove::calc_() {
    SimpleLineBeam::calc_();
}

}  // namespace uking::action
