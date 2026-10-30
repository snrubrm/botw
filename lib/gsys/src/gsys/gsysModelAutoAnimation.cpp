#include "gsys/gsysModelAutoAnimation.h"

#include <nn/g3d/ModelAnimObj.h>
#include <nn/g3d/SkeletalAnimObj.h>

namespace gsys {

ModelAutoAnimation::InitArg::InitArg() = default;

// 0x7100bfffd8
ModelAutoAnimation::ModelAutoAnimation() {}

// NON_MATCHING: the compiler schedules the array traversal differently.
void ModelAutoAnimation::forceFrame(f32 frame) {
    auto** animations = mSkeletalAnims.data();
    const s32 count = mSkeletalAnims.size();
    for (s32 i = 0; i < count; ++i)
        animations[i]->GetFrameCtrl()->SetFrame(frame);
}

// NON_MATCHING: the compiler schedules the array traversal differently.
void ModelAutoAnimation::copyFrameTo(ModelAutoAnimation* other) const {
    auto** skeletal = mSkeletalAnims.data();
    const s32 skeletal_count = mSkeletalAnims.size();
    for (s32 i = 0; i < skeletal_count; ++i) {
        const f32 frame = skeletal[i]->GetFrameCtrl()->GetFrame();
        other->mSkeletalAnims.unsafeAt(i)->GetFrameCtrl()->SetFrame(frame);
    }
    auto** material = mMaterialAnims.data();
    const s32 material_count = mMaterialAnims.size();
    for (s32 i = 0; i < material_count; ++i) {
        const f32 frame = material[i]->GetFrameCtrl()->GetFrame();
        other->mMaterialAnims.unsafeAt(i)->GetFrameCtrl()->SetFrame(frame);
    }
}

// 0x7100c00718
void ModelAutoAnimation::forceUpdate() {
    update_(mModel, 0.0f);
}

}  // namespace gsys
