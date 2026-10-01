#include "Game/AI/AI/aiWaterSurface4RemainsLava.h"

namespace uking::ai {

WaterSurface4RemainsLava::WaterSurface4RemainsLava(const InitArg& arg) : WaterSurface(arg) {}

WaterSurface4RemainsLava::~WaterSurface4RemainsLava() = default;

bool WaterSurface4RemainsLava::init_(sead::Heap* heap) {
    return WaterSurface::init_(heap);
}

void WaterSurface4RemainsLava::enter_(ksys::act::ai::InlineParamPack* params) {
    WaterSurface::enter_(params);
}

void WaterSurface4RemainsLava::calc_() {
    WaterSurface::calc_();
}

void WaterSurface4RemainsLava::leave_() {
    WaterSurface::leave_();
}

void WaterSurface4RemainsLava::loadParams_() {
    WaterSurface::loadParams_();
}

void WaterSurface4RemainsLava::m34() {
    _a4 = 0;
    _a8 = false;
    sub_71005EC820();
}

void WaterSurface4RemainsLava::m35() {
    bool turned_on = false;
    const bool on = sub_71005EC4BC();
    if (on) {
        if (!_a8) {
            _a8 = on;
            turned_on = true;
        }
    } else {
        _a8 = on;
    }

    auto* child = getCurrentChild();
    if ((child->isFinished() || child->isFailed()) && !isCurrentChild("待機")) {
        switch (_a4) {
        case 3:
            _a4 = 0;
            break;
        case 1:
            _a4 = 2;
            break;
        }
        sub_71005EC820();
        return;
    }

    if (turned_on && isCurrentChild("待機")) {
        switch (_a4) {
        case 0:
            _a4 = 1;
            sub_71005EC520();
            break;
        case 2:
            _a4 = 3;
            sub_71005EC6B0();
            break;
        }
    }
}

}  // namespace uking::ai
