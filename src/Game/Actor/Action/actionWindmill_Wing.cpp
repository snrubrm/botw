#include "Game/Actor/Action/actionWindmill_Wing.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include <cmath>
#include <math/seadQuat.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

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

void Windmill_Wing::m32(bool a1) {
    auto* manager = ksys::world::Manager::instance();
    if (!manager)
        return;
    manager->getWindSpeed();
    const f32 speed = sub_71002BDA28();
    if (a1)
        _5c = speed;
    else
        ksys::VFR::lerp(&_5c, speed, 0.005f);
    if (auto* as_list = mActor->getASList())
        as_list->x_3(0, 0, &ksys::as::ASList::Unk2::sub_7101163100, _5c);
    sub_71012412E4(mActor, 3, _5c, false);
}

void Windmill_Wing::m33() {
    playAS("Rotate", false, 0, 0, -1.0f);
}

// NON_MATCHING: vector interpolation and quaternion/matrix scheduling differ.
void Windmill_Wing::m34(f32 turn) {
    sead::Vector3f wind = sead::Vector3f::ez;
    f32 speed = 1.0f;
    if (auto* manager = ksys::world::Manager::instance()) {
        wind = -manager->getWindDirection();
        speed = manager->getWindSpeed();
        if (speed < 0.1f)
            speed = 0.1f;
        else if (speed > 10.0f)
            speed = 10.0f;
    }
    wind.normalize();
    sead::Matrix34f transform = mActor->getMtx();
    auto* body = mActor->getMainBody();
    if (body)
        body->getTransform(&transform);
    sead::Vector3f front(transform(0, 2), transform(1, 2), transform(2, 2));
    f32 rate;
    if (turn > 0.0f) {
        rate = turn;
    } else {
        rate = (speed / 10.0f) * *mTurnRate_s;
        rate *= rate;
    }
    ksys::VFR::lerp(&front, wind, rate);
    ksys::Timer::update(&_58, speed * 0.01f);
    if (_58 >= sead::Mathf::pi2())
        ksys::Timer::update(&_58, -sead::Mathf::pi2());
    sead::Quatf quaternion;
    quaternion.setAxisRadian(sead::Vector3f::ey, std::sin(_58) * 0.001f);
    sead::Matrix33f rotation;
    rotation.fromQuat(quaternion);
    front.rotate(rotation);
    sead::Matrix34f result;
    const sead::Vector3f position = mActor->getMtx().getTranslation();
    ksys::util::sub_71011F0260(&result, front, sead::Vector3f::ey, position, false);
    if (body)
        body->changeRotation(result, sead::Mathf::epsilon());
}

}  // namespace uking::action
