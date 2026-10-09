#include "KingSystem/XLink/xlinkUser.h"
#include <cfloat>
#include <gsys/gsysModel.h>
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/XLink/xlinkXLink.h"

namespace ksys::xlink {

Unk_71025168a0::Unk_71025168a0(XLink* xlink) : mXLink(xlink) {}
Unk_71025168a0::~Unk_71025168a0() = default;

void Unk_71025168a0::setExtraLabels(const char* const* labels, s32 count) {
    mExtraLabels = labels;
    mNumExtraLabels = count;
}

void Unk_71025168a0::getReservedAssetName(xlink2::ToolConnectionContext* ctx) const {
    ctx->addLabel("Disappear");
    ctx->addLabel("ReactionLand");
    ctx->addLabel("ReactionSlide");
    ctx->addLabel("ReachedLimit");
    ctx->addLabel("BurnStart");
    ctx->addLabel("Burning");
    ctx->addLabel("WindDirChangeTest");
    if (mExtraLabels) {
        for (s32 i = 0; i < mNumExtraLabels; ++i)
            ctx->addLabel(mExtraLabels[i]);
    }
}

u32 Unk_71025168a0::getNumBone() const {
    return mXLink && mXLink->mModel ? mXLink->mModel->getTotalBoneNum() : 0;
}

f32 Unk_71025168a0::getSortKey(const sead::Vector3f& position) const {
    const auto* camera = CameraMgr::instance()->getLookAtCamera();
    if (!camera)
        return FLT_MAX;
    sead::Vector3f camera_pos;
    camera->worldPosToCameraPosByMatrix(&camera_pos, position);
    if (camera_pos.z > 0)
        return FLT_MAX;
    return camera_pos.length();
}

sead::Matrix34f Unk_71025168a0::getAutoInputMtxSource() const {
    return sUnk_7102652e40;
}

}  // namespace ksys::xlink
