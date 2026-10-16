#include "Game/Actor/Behavior/behaviorEyeBlink.h"
#include <random/seadGlobalRandom.h>
#include "Game/Actor/actEnemy.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

EyeBlink::EyeBlink(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

EyeBlink::~EyeBlink() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        enemy->_f60.sub_7100701D4C();
}

bool EyeBlink::init_(sead::Heap* heap) {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
        enemy->_f60.sub_7100701BE4(mLeftEyeLidName_s, mRightEyeLidName_s, *mCloseOffset_s);
        const s32 min = *mTimerMin_s;
        const s32 max = *mTimerMax_s;
        _68 = sead::GlobalRandom::instance()->getS32Range(min, max);
        return true;
    }
    return false;
}

void EyeBlink::calc() {
    ksys::Timer::update(&_68, -1.0f);
    if (_68 <= 0) {
        auto* actor = mActor;
        if (auto* enemy = sead::DynamicCast<act::Enemy>(actor)) {
            enemy->_f60.sub_7100701DBC(*mBlinkCount_s);
            const s32 min = *mTimerMin_s;
            const s32 max = *mTimerMax_s;
            _68 = sead::GlobalRandom::instance()->getS32Range(min, max);
        }
    }
}

void EyeBlink::enter() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        enemy->_f60.sub_7100701CE8();
}

void EyeBlink::leave() {
    auto* actor = mActor;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(actor))
        enemy->_f60.removeOrDefer();
}

void EyeBlink::loadParams() {
    getStaticParam(&mTimerMin_s, "TimerMin");
    getStaticParam(&mTimerMax_s, "TimerMax");
    getStaticParam(&mBlinkCount_s, "BlinkCount");
    getStaticParam(&mLeftEyeLidName_s, "LeftEyeLidName");
    getStaticParam(&mRightEyeLidName_s, "RightEyeLidName");
    getStaticParam(&mCloseOffset_s, "CloseOffset");
}

}  // namespace uking::behavior
