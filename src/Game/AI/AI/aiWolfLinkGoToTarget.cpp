#include "Game/AI/AI/aiWolfLinkGoToTarget.h"
#include "Game/Actor/actWolfLink.h"

bool sub_7100742738(sead::Vector3f* out, uking::act::WolfLink* wolf, f32 value);

namespace uking::ai {

WolfLinkGoToTarget::WolfLinkGoToTarget(const InitArg& arg) : HorseFollow(arg) {}

WolfLinkGoToTarget::~WolfLinkGoToTarget() = default;

bool WolfLinkGoToTarget::init_(sead::Heap* heap) {
    if (!HorseFollow::init_(heap))
        return false;
    _e0 = sead::DynamicCast<act::WolfLink>(mActor);
    return _e0 != nullptr;
}

void WolfLinkGoToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseFollow::enter_(params);
}

void WolfLinkGoToTarget::leave_() {
    HorseFollow::leave_();
}

void WolfLinkGoToTarget::calc_() {
    if (isFinished() || isFailed())
        return;

    sead::Vector3f out;
    if (isCurrentChild("崖である") || sub_7100742738(&out, _e0, -1.0f)) {
        if (isCurrentChild("崖である")) {
            auto* child = getCurrentChild();
            if (!child)
                return;
            if (!child->isFinished() && !child->isFailed())
                return;
            if (child->isFailed()) {
                setFailed();
                return;
            }
        }
        HorseFollow::calc_();
    } else {
        changeChild("崖である", nullptr);
    }
}

void WolfLinkGoToTarget::loadParams_() {
    HorseFollow::loadParams_();
}

}  // namespace uking::ai
