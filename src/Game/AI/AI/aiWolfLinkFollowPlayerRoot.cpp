#include "Game/AI/AI/aiWolfLinkFollowPlayerRoot.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

WolfLinkFollowPlayerRoot::WolfLinkFollowPlayerRoot(const InitArg& arg) : HorseFollow(arg) {}

WolfLinkFollowPlayerRoot::~WolfLinkFollowPlayerRoot() = default;

bool WolfLinkFollowPlayerRoot::init_(sead::Heap* heap) {
    if (!HorseFollow::init_(heap))
        return false;

    _100 = sead::DynamicCast<act::WolfLink>(mActor);
    if (!_100)
        return false;

    _144.makeIdentity();
    return true;
}

void WolfLinkFollowPlayerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
    m39(true);
    m40();
    m35();
    _17c = false;
}

void WolfLinkFollowPlayerRoot::leave_() {
    if (auto* rideable = _100->m132()) {
        rideable->_154 = 1.0f;
        HorseFollow::leave_();
    } else {
        setFailed();
    }
}

void WolfLinkFollowPlayerRoot::loadParams_() {
    HorseFollow::loadParams_();
    getStaticParam(&mLateralDistance_s, "LateralDistance");
    getStaticParam(&mAnteriorDistanceStop_s, "AnteriorDistanceStop");
    getStaticParam(&mAnteriorDistanceRun_s, "AnteriorDistanceRun");
    getStaticParam(&mAnteriorDistanceSprint_s, "AnteriorDistanceSprint");
}

f32 WolfLinkFollowPlayerRoot::m35() {
    return HorseFollow::m35();
}

void WolfLinkFollowPlayerRoot::m40() {
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(mTargetActor_d, &accessor))
        return;

    const sead::Vector3f pos = _100->getMtx().getTranslation();
    sead::Matrix34f inv;
    sead::Matrix34CalcCommon<f32>::inverse(inv, _144);
    sead::Vector3f local;
    local.setMul(inv, pos);

    const auto& aabb = accessor.sub_7100D0FD54();
    const f32 half_width = (aabb.getMax().x - aabb.getMin().x) * 0.5f + 0.1f;
    switch (_174) {
    case 0:
        if (local.x > half_width)
            _174 = 1;
        else if (local.x < half_width)
            _174 = 2;
        break;
    case 2:
        if (local.x > half_width) {
            _174 = 1;
            break;
        }
        [[fallthrough]];
    default:
        if (local.x < half_width)
            _174 = 2;
        break;
    }
}

}  // namespace uking::ai
