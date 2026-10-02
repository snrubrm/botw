#include "Game/AI/Action/actionDieHomeRun.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actUnk_71007A24BC.h"

namespace uking::action {

DieHomeRun::DieHomeRun(const InitArg& arg) : Die(arg) {}

DieHomeRun::~DieHomeRun() = default;

bool DieHomeRun::init_(sead::Heap* heap) {
    return Die::init_(heap);
}

void DieHomeRun::enter_(ksys::act::ai::InlineParamPack* params) {
    Die::enter_(params);
    mActor->getMtx().getTranslation(_170);
    _17c = 5.0f;
}

void DieHomeRun::leave_() {
    Die::leave_();
}

void DieHomeRun::loadParams_() {
    Die::loadParams_();
    getStaticParam(&mToStarHeight_s, "ToStarHeight");
    getStaticParam(&mFallHeight_s, "FallHeight");
}

void DieHomeRun::calc_() {
    Die::calc_();
    auto* actor = mActor;
    const f32 height = actor->getMtx().m[1][3] - _170.y;
    if (height < *mFallHeight_s || *mToStarHeight_s < height) {
        _ec = 2;
        setFinished();
        return;
    }

    ksys::Timer::update(&_17c, -1.0f);
    if (_17c < 0.0f &&
        (ksys::act::sub_71007A4638(actor, false) || ksys::act::sub_71007A4864(actor, false))) {
        _ec = 2;
        setFinished();
    }
}

}  // namespace uking::action
