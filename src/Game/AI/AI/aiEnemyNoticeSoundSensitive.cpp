#include "Game/AI/AI/aiEnemyNoticeSoundSensitive.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

EnemyNoticeSoundSensitive::EnemyNoticeSoundSensitive(const InitArg& arg)
    : EnemyNoticeSoundWithUI(arg) {}

EnemyNoticeSoundSensitive::~EnemyNoticeSoundSensitive() = default;

bool EnemyNoticeSoundSensitive::init_(sead::Heap* heap) {
    return EnemyNoticeSoundWithUI::init_(heap);
}

void EnemyNoticeSoundSensitive::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeSoundWithUI::enter_(params);
    _64 = 5;
    _68 = 7;
}

// NON_MATCHING: our clang threads the `lost` paths into the timer update; the original
// materialises the flag and tests it again
void EnemyNoticeSoundSensitive::calc_() {
    bool lost = false;
    auto* actor = mActor;
    if (auto* awareness = actor->getAwareness()) {
        Unk_71024514e8 filter(actor, nullptr);
        if (auto* sensor = awareness->_260[1])
            lost = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter) == nullptr;
        else
            lost = true;
    }

    if (!lost && _60 <= 0.0f && getCurrentChild()->isChangeable()) {
        _64 = 5;
        _68 = 7;
        m36();
        return;
    }

    if (lost)
        ksys::Timer::update(&_60, -1.0f);
    else
        _60 = _64 == _68 ? _64 : sead::GlobalRandom::instance()->getS32Range(_64, _68);
    EnemyNoticeSoundWithUI::calc_();
}

void EnemyNoticeSoundSensitive::leave_() {
    EnemyNoticeSoundWithUI::leave_();
}

void EnemyNoticeSoundSensitive::loadParams_() {
    EnemyNoticeSoundWithUI::loadParams_();
}

void EnemyNoticeSoundSensitive::m36() {
    sub_71003A6298();
}

}  // namespace uking::ai
