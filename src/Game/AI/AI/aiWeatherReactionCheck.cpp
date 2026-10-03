#include "Game/AI/AI/aiWeatherReactionCheck.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007130BC.h"
#include "Game/Damage/dmgInfoManager.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace uking::ai {

WeatherReactionCheck::WeatherReactionCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeatherReactionCheck::~WeatherReactionCheck() = default;

bool WeatherReactionCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeatherReactionCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* mgr = dmg::DamageInfoMgr::instance();
    if ((*mIsReactionRain_s && mgr->sub_7100674704()) ||
        (*mIsReactionSnow_s && mgr->sub_7100674730())) {
        if (!_60.isOnBit(0)) {
            _60.setBit(0);
            const s32 max_time = *mRandTime_s;
            _64 = sead::GlobalRandom::instance()->getS32Range(0, max_time);
        }
    }
    changeChild("通常", params);
}

// NON_MATCHING: regalloc only (the original keeps `&_64` in x0 across the LodState branch and the Timer::update
// call; ours copies it into a callee-saved register and needs an extra x21)
void WeatherReactionCheck::calc_() {
    auto* mgr = dmg::DamageInfoMgr::instance();
    if ((*mIsReactionRain_s && mgr->sub_7100674704()) ||
        (*mIsReactionSnow_s && mgr->sub_7100674730())) {
        if (!_60.isOnBit(0)) {
            _60.setBit(0);
            const s32 max_time = *mRandTime_s;
            _64 = sead::GlobalRandom::instance()->getS32Range(0, max_time);
        }
    }

    if (_64 > 0.0f) {
        if (auto* lod = mActor->getLodState())
            _64 -= lod->_40;
        ksys::Timer::update(&_64, -1.0f);
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (*mIsReturnNormal_s && !isCurrentChild("通常")) {
            changeChild("通常");
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else if (child->isChangeable() && _60.isOnBit(0) && _64 <= 0.0f) {
        _60.resetBit(0);
        if (wm::getWeatherMgr() && *mIsReactionRain_s && wm::getWeatherMgr()->isRaining())
            changeChild("雨");
        else if (wm::getWeatherMgr() && *mIsReactionSnow_s && wm::getWeatherMgr()->isSnowing())
            changeChild("雪");
    }
}

void WeatherReactionCheck::leave_() {
    _60.reset(1);
}

void WeatherReactionCheck::loadParams_() {
    getStaticParam(&mRandTime_s, "RandTime");
    getStaticParam(&mIsReactionRain_s, "IsReactionRain");
    getStaticParam(&mIsReactionSnow_s, "IsReactionSnow");
    getStaticParam(&mIsReturnNormal_s, "IsReturnNormal");
    getStaticParam(&mIsForceChangeable_s, "IsForceChangeable");
}

bool WeatherReactionCheck::isFailed() const {
    return getCurrentChild()->isFailed() && (!*mIsReturnNormal_s || isCurrentChild("通常"));
}

bool WeatherReactionCheck::isFinished() const {
    return getCurrentChild()->isFinished() && (!*mIsReturnNormal_s || isCurrentChild("通常"));
}

bool WeatherReactionCheck::isChangeable() const {
    if (*mIsForceChangeable_s)
        return true;
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
