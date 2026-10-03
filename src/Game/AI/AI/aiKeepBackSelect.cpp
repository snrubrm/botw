#include "Game/AI/AI/aiKeepBackSelect.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

KeepBackSelect::KeepBackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeepBackSelect::~KeepBackSelect() = default;

bool KeepBackSelect::init_(sead::Heap* heap) {
    if (!mNodeName_s.isEmpty()) {
        auto* model = mActor->getModel();
        const sead::SafeString& name = mNodeName_s;
        _70.search(model, name);
    }
    return true;
}

void KeepBackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 keep_time = *mKeepTime_s;
    _ac = keep_time;
    _b0 = keep_time;
    _a8 = keep_time;
    changeChild("角度内", params);
}

void KeepBackSelect::calc_() {
    if (isCurrentChild("角度内")) {
        f32* timer = &_a8;
        if (sub_710045134C()) {
            ksys::Timer::update(timer, -1.0f);
        } else {
            s32 value = _ac;
            if (_b0 != _ac)
                value = sead::GlobalRandom::instance()->getS32Range(_ac, _b0);
            *timer = value;
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        s32 value = _ac;
        if (_b0 != _ac)
            value = sead::GlobalRandom::instance()->getS32Range(_ac, _b0);
        _a8 = value;
        changeChild("角度内", nullptr);
    } else if (child->isChangeable()) {
        if (isCurrentChild("角度内") && _a8 <= 0.0f)
            changeChild("角度外", nullptr);
    }
}

void KeepBackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KeepBackSelect::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mBaseAxis_s, "BaseAxis");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getStaticParam(&mXZOnly_s, "XZOnly");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mLocalOffset_s, "LocalOffset");
}

}  // namespace uking::ai
