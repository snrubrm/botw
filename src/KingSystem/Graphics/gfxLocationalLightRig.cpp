#include "KingSystem/Graphics/gfxLocationalLightRig.h"
#include <gsys/gsysModel.h>
#include <prim/seadScopedLock.h>

namespace ksys::gfx {

// NON_MATCHING: adjacent halfword stores merge and initialization is reordered.
void LocationalLightRig::m24(gsys::Model* model, const gsys::BoneAccessKey& key,
                             const sead::SafeString& name) {
    auto lock = sead::makeScopedLock(mCS);
    if (name.endsWith("_End"))
        return;
    auto* light = mLightMgr->mRigLightPool.allocate();
    if (!light)
        return;
    light->mBoneIndex = key.bone_index;
    light->mFlags |= 1;
    light->mRig = this;
    light->mObjectLight = nullptr;
    light->mEndBoneIndex = -1;
    light->mVisibilityMask = 0;
    model->pushBack(key.model_unit_index, light);
    mLights.pushBack(light);
}

void LocationalLightRig::m25(gsys::Model*, const gsys::MaterialAccessKey&,
                             const sead::SafeString&) {}

// NON_MATCHING: OffsetList iterator offset handling and field stores differ.
void LocationalLightRig::m26(gsys::Model* model, int unit_index) {
    auto lock = sead::makeScopedLock(mCS);
    auto it = mLights.begin();
    while (it != mLights.end()) {
        auto* light = &*it;
        if (!model->hasRigObj(unit_index, light)) {
            ++it;
            continue;
        }
        mLights.erase(light);
        model->erase(unit_index, light);
        if (light->mRenderLight) {
            light->mRig->mLightMgr->sub_7100F13A58(light->mRenderLight);
            light->mRenderLight = nullptr;
        }
        light->mFlags = 0;
        light->mRig = nullptr;
        light->mObjectLight = nullptr;
        light->mBoneIndex = -1;
        light->mEndBoneIndex = -1;
        light->mVisibilityMask = 0xffff;
        mLightMgr->mRigLightPool.release(light);
        it = mLights.begin();
    }
}

}  // namespace ksys::gfx
