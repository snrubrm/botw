#include "gsys/gsysModel.h"
#include "gsys/gsysModelAutoAnimation.h"
#include "gsys/gsysModelNW.h"

namespace gsys {

void Model::setAutoAnimationFrameRate(f32 frame_rate) {
    mAutoAnimationFrameRate = frame_rate;
    for (auto& info : mUnitAccess) {
        if (auto* unit = sead::DynamicCast<ModelNW>(info.mModelUnit)) {
            if (unit->mAutoAnimation)
                unit->mAutoAnimation->mFrameRate = frame_rate;
        }
    }
}

}  // namespace gsys
