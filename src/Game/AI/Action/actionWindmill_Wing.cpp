#include "Game/AI/Action/actionWindmill_Wing.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/World/worldManager.h"

namespace uking::action {

Windmill_Wing::Windmill_Wing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Windmill_Wing::~Windmill_Wing() = default;

f32 Windmill_Wing::sub_71002BDA28() {
    const f32 wind_a = *mASPlaySpeedMaxWindPower_s;
    const f32 wind_b = *mASPlaySpeedMinWindPower_s;
    const f32 min_wind = wind_a < wind_b ? wind_a : wind_b;
    const f32 max_wind = wind_a < wind_b ? wind_b : wind_a;
    const f32 speed_a = *mASPlaySpeedMax_s;
    const f32 speed_b = *mASPlaySpeedMin_s;
    const f32 min_speed = speed_a < speed_b ? speed_a : speed_b;
    const f32 max_speed = speed_a < speed_b ? speed_b : speed_a;
    f32 speed = min_speed;
    if (auto* manager = ksys::world::Manager::instance()) {
        const f32 wind = manager->getWindSpeed();
        if (wind <= min_wind) {
            // below the range: the min speed
        } else if (wind >= max_wind) {
            speed = max_speed;
        } else {
            const f32 wind_range = max_wind - min_wind;
            const f32 speed_range = max_speed - min_speed;
            speed = min_speed + speed_range / wind_range * (wind - min_wind);
        }
    }
    return speed;
}

bool Windmill_Wing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Windmill_Wing::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = sead::GlobalRandom::instance()->getF32() * sead::Mathf::piHalf();
    m32(true);
    m33();
    if (*mIsTurnToWindDir_s)
        m34(1.0f);
}

void Windmill_Wing::leave_() {
    ksys::act::ai::Action::leave_();
}

void Windmill_Wing::loadParams_() {
    getStaticParam(&mStartFrameRange_s, "StartFrameRange");
    getStaticParam(&mASPlaySpeedMin_s, "ASPlaySpeedMin");
    getStaticParam(&mASPlaySpeedMax_s, "ASPlaySpeedMax");
    getStaticParam(&mASPlaySpeedMinWindPower_s, "ASPlaySpeedMinWindPower");
    getStaticParam(&mASPlaySpeedMaxWindPower_s, "ASPlaySpeedMaxWindPower");
    getStaticParam(&mTurnRate_s, "TurnRate");
    getStaticParam(&mIsTurnToWindDir_s, "IsTurnToWindDir");
}

void Windmill_Wing::calc_() {
    m32(false);
    if (*mIsTurnToWindDir_s)
        m34(0.0f);
}

void Windmill_Wing::m33() {
    playAS("Rotate", false, 0, 0, -1.0f);
}

}  // namespace uking::action
