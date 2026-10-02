#include "Game/AI/Action/actionForkAlwaysTurnUDLimit.h"
#include <cmath>

namespace uking::action {

ForkAlwaysTurnUDLimit::ForkAlwaysTurnUDLimit(const InitArg& arg) : ForkAlwaysTurn(arg) {}

ForkAlwaysTurnUDLimit::~ForkAlwaysTurnUDLimit() = default;

bool ForkAlwaysTurnUDLimit::init_(sead::Heap* heap) {
    return ForkAlwaysTurn::init_(heap);
}

void ForkAlwaysTurnUDLimit::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysTurn::enter_(params);
}

void ForkAlwaysTurnUDLimit::leave_() {
    ForkAlwaysTurn::leave_();
}

void ForkAlwaysTurnUDLimit::loadParams_() {
    ForkAlwaysTurn::loadParams_();
    getStaticParam(&mLimitUD_s, "LimitUD");
}

void ForkAlwaysTurnUDLimit::calc_() {
    ForkAlwaysTurn::calc_();
}

void ForkAlwaysTurnUDLimit::m33(sead::Vector3f* dir) {
    const f32 xz = std::sqrt(dir->x * dir->x + dir->z * dir->z);
    const f32 angle = std::atan2(dir->y, xz);
    if (sead::Mathf::abs(angle) > *mLimitUD_s) {
        dir->y = xz * std::tan(*mLimitUD_s) * (dir->y > 0 ? 1.0f : -1.0f);
        dir->normalize();
    }
}

}  // namespace uking::action
