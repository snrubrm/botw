#include "Game/Actor/AI/aiWolfLinkFollowPlayerRoot.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include <math/seadMathCalcCommon.h>
#include <cmath>

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

// NON_MATCHING: cross-product arithmetic, matrix snapshots and register allocation.
void WolfLinkFollowPlayerRoot::m39(bool force) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (!mTargetActor_d || !ksys::act::acquireActor(mTargetActor_d, &accessor))
        return;
    if (force) {
        _144 = accessor.getActorMtx();
        _144.getBase(_12c, 2);
        _144.getTranslation(_138);
    } else if (!(_100->_1698 & 0x10)) {
        const auto matrix = accessor.getActorMtx();
        const auto direction = matrix.getBase(2);
        const auto position = matrix.getTranslation();
        const f32 angle = std::atan2(_12c.cross(direction).length(), _12c.dot(direction));
        const f32 dx = _138.x - position.x;
        const f32 dz = _138.z - position.z;
        if (dx * dx + dz * dz < 1.0f || angle >= sead::Mathf::deg2rad(4.0f)) {
            if (angle >= sead::Mathf::deg2rad(4.0f))
                _12c = direction;
            _144.getTranslation(_138);
            _114 = sead::Vector3f::ez;
        } else {
            _144 = matrix;
            _12c = direction;
            _138 = position;
            _17c = false;
        }
    }
}

void WolfLinkFollowPlayerRoot::m40() {
    ksys::act::ActorLinkConstDataAccess accessor;
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
