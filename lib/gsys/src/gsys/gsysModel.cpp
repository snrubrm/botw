#include "gsys/gsysModel.h"
#include "gsys/gsysModelSceneEnv.h"
#include "gsys/gsysModelAutoAnimation.h"
#include "gsys/gsysModelNW.h"

namespace gsys {

void Model::getBounding(sead::Vector4f* bounding) const {
    const sead::Vector4f* source = mBoundingOverrideMaybe;
    if (!source) {
        gatherBounding_();
        source = &mBounding;
    }
    *bounding = *source;
}

void Model::setAutoAnimationFrameRate(f32 frame_rate) {
    mAutoAnimationFrameRate = frame_rate;
    for (auto& info : mUnitAccess) {
        if (auto* unit = sead::DynamicCast<ModelNW>(info.mModelUnit)) {
            if (unit->mAutoAnimation)
                unit->mAutoAnimation->mFrameRate = frame_rate;
        }
    }
}

void Model::forceAutoAnimationFrame(f32 frame) {
    for (auto& info : mUnitAccess) {
        if (auto* unit = sead::DynamicCast<ModelNW>(info.mModelUnit)) {
            if (unit->mAutoAnimation)
                unit->mAutoAnimation->forceFrame(frame);
        }
    }
}

void Model::forceUpdateAutoAnimation() {
    for (auto& info : mUnitAccess) {
        if (auto* unit = sead::DynamicCast<ModelNW>(info.mModelUnit)) {
            if (unit->mAutoAnimation)
                unit->mAutoAnimation->forceUpdate();
        }
    }
}

}  // namespace gsys
