#include "Game/Actor/Action/actionDestPlayerWarpBase.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

DestPlayerWarpBase::DestPlayerWarpBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DestPlayerWarpBase::~DestPlayerWarpBase() = default;

bool DestPlayerWarpBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original copies _4c (ones, then the player scale) as 8 + 4 bytes; Vector3f::operator= copies
// per element.
void DestPlayerWarpBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = sead::Matrix34f::ident;
    _4c = sead::Vector3f::ones;
    _58 = false;
    _59 = false;

    auto* player = uking::act::PlayerInfo::instance()->getPlayer();
    _4c = player->getScale();
    m32();

    {
        const sead::Vector3f pos = _1c.getTranslation();
        ksys::phys::RayCastBodyQuery query(nullptr, ksys::phys::GroundHit::HitAll);
        sead::Vector3f start{pos.x, pos.y + 1.0f, pos.z};
        const sead::Vector3f end{pos.x, pos.y + -1.0f, pos.z};
        query.setStartAndEnd(start, end);
        query.enableLayer(ksys::phys::ContactLayer::EntityGround);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
        query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
        if (query.worldRayCast(ksys::phys::ContactLayerType::Entity)) {
            query.getHitPosition(&start);
            _1c.setTranslation(start);
        }
    }

    player->setNewPlayerMtx(_1c);
    if (player->isRidingHorse()) {
        auto* proc = uking::act::PlayerInfo::instance()->getHorseLink().getProc(nullptr);
        if (auto* horse = sead::DynamicCast<ksys::act::Actor>(proc))
            horse->setMtx(_1c, false, true);
        auto* ride_info = sead::DynamicCast<ksys::act::Player::RideInfo>(player->getPlayerRideInfo());
        ride_info->setFlagOn(ksys::act::Player::RideInfo::Flag::_1);
    }
    _5c = 10.0f;
}

void DestPlayerWarpBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void DestPlayerWarpBase::loadParams_() {}

// NON_MATCHING: natural control flow, temporary layout, and accessor scope merging differ.
void DestPlayerWarpBase::calc_() {
    if (isFinished() || isFailed())
        return;
    if (!_58) {
        _58 = true;
        return;
    }
    if (!m33()) {
        setFinished();
        return;
    }
    const sead::Vector3f pos = _1c.getTranslation();
    if (m34(pos)) {
        if (auto* info = uking::act::PlayerInfo::instance()) {
            f32 remaining = 0.0f;
            {
                ksys::act::ActorLinkConstDataAccess accessor;
                ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
                const auto& matrix = accessor.getActorMtx();
                const f32 dx = pos.x - matrix.m[0][3];
                const f32 dz = pos.z - matrix.m[2][3];
                if (dx * dx + dz * dz < 1.0f) {
                    const sead::Vector3f rotation = _1c.getRotation();
                    if (_59) {
                        m36(pos, rotation.y);
                    } else {
                        m35(pos, rotation.y);
                        _59 = true;
                        return;
                    }
                } else {
                    ksys::Timer::update(&_5c, -1.0f);
                    remaining = _5c;
                }
            }
            if (remaining > 0.0f)
                return;
        }
    }
    setFinished();
}

void DestPlayerWarpBase::m32() {}

bool DestPlayerWarpBase::m33() {
    return false;
}

bool DestPlayerWarpBase::m34(const sead::Vector3f& pos) {
    if (auto* manager = ksys::world::Manager::instance()) {
        if (manager->isForbidComeback(manager->getClimate(pos)))
            return false;
    }
    return !ksys::gdt::getFlag_PSavePosNotUpdate(false);
}

void DestPlayerWarpBase::m35(const sead::Vector3f& pos, f32 angle) {
    if (auto* info = uking::act::PlayerInfo::instance()) {
        ksys::act::acc::PlayerBase accessor;
        ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
        accessor.setRestartBuf(pos, sead::Mathf::rad2deg(angle));
    }
}

void DestPlayerWarpBase::m36(const sead::Vector3f& pos, f32 angle) {
    ksys::gdt::setFlag_PlayerSavePos(pos, false);
    ksys::gdt::setFlag_PlayerSavePosAngleYDegree(sead::Mathf::rad2deg(angle), false);
}

}  // namespace uking::action
