#include "Game/AI/Action/actionWarpPlayerBase.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/World/worldManager.h"

namespace uking::action {

WarpPlayerBase::WarpPlayerBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpPlayerBase::~WarpPlayerBase() = default;

bool WarpPlayerBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPlayerBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPlayerBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerBase::loadParams_() {}

// NON_MATCHING: natural control flow, temporary layout, and accessor scope merging differ.
void WarpPlayerBase::calc_() {
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
        if (auto* info = ksys::act::PlayerInfo::instance()) {
            f32 remaining = 0.0f;
            {
                ksys::act::ActorConstDataAccess accessor;
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

void WarpPlayerBase::m32() {}

bool WarpPlayerBase::m33() {
    return false;
}

bool WarpPlayerBase::m34(const sead::Vector3f& pos) {
    if (auto* manager = ksys::world::Manager::instance()) {
        if (manager->isForbidComeback(manager->getClimate(pos)))
            return false;
    }
    return !ksys::gdt::getFlag_PSavePosNotUpdate(false);
}

void WarpPlayerBase::m35(const sead::Vector3f& pos, f32 angle) {
    if (auto* info = ksys::act::PlayerInfo::instance()) {
        ksys::act::acc::PlayerBase accessor;
        ksys::act::acquireActor(&info->getPlayerLink(), &accessor);
        accessor.setRestartBuf(pos, sead::Mathf::rad2deg(angle));
    }
}

void WarpPlayerBase::m36(const sead::Vector3f& pos, f32 angle) {
    ksys::gdt::setFlag_PlayerSavePos(pos, false);
    ksys::gdt::setFlag_PlayerSavePosAngleYDegree(sead::Mathf::rad2deg(angle), false);
}

}  // namespace uking::action
