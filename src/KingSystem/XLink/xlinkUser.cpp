#include "KingSystem/XLink/xlinkUser.h"
#include <cfloat>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelAnimation.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModelUnit.h>
#include <utility/aglScreenShotMgr.h>
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actActor.h"
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

// NON_MATCHING: the flattened bone-index comparison and saved registers differ.
const char* Unk_71025168a0::getBoneName(s32 index) const {
    if (!mXLink)
        return "";
    auto* model = mXLink->mModel;
    if (!model)
        return "";
    s32 offset = 0;
    for (s32 i = 0; i < model->getUnits().size(); ++i) {
        auto* unit = model->getUnits().unsafeAt(i)->mModelUnit;
        s32 bone = 0;
        for (; bone < unit->getBoneNum(); ++bone) {
            if (bone == index - offset) {
                const auto name = unit->getBoneName(bone);
                return name.cstr();
            }
        }
        offset += bone;
    }
    return "";
}

sead::Matrix34f* Unk_71025168a0::getBoneWorldMtxPtr(const char* name) const {
    if (!mXLink || !mXLink->mModel)
        return nullptr;
    auto* model = mXLink->mModel;
    const auto key = model->searchBone(name);
    if (!key.isValid())
        return nullptr;
    return model->getUnits().unsafeAt(key.model_unit_index)->mModelUnit->getBoneWorldMatrixPtr(
        key.bone_index);
}

char* Unk_71025168a0::getDebugUserName() const {
    if (!mXLink || !mXLink->mActor)
        return nullptr;
    // IUser's debug-name API returns a mutable pointer to the actor's existing name buffer.
    return const_cast<char*>(mXLink->mActor->getName().cstr());
}

u32 Unk_71025168a0::getNumAction(s32 index) const {
    if (!mXLink)
        return 0;
    if (index >= mXLink->_70 + mXLink->_71 + mXLink->_72) {
        const auto* root_ai = mXLink->getRootAi();
        return root_ai ? root_ai->getActions().getClasses().size() : 0;
    }
    if (index >= mXLink->_70 + mXLink->_71) {
        const auto* animation = mXLink->getModelAnimation();
        if (!animation)
            return 0;
        s32 count = 0;
        for (s32 type = 0; type < 6; ++type)
            count += animation->getMaterialAnmNum(static_cast<gsys::MaterialAnmType>(type));
        return count;
    }
    if (index >= mXLink->_70) {
        const auto* animation = mXLink->getModelAnimation();
        return animation ? animation->mSkeletalResources.size() : 0;
    }
    const auto* as_list = mXLink->getASList();
    return as_list ? as_list->_138.size() : 0;
}

void Unk_71025168a0::captureScreen(const char* name) {
    agl::utl::ScreenShotMgr::instance()->reserveCaptureWithDebugHeap(
        true, agl::TextureDataSerializerTGA::TGAFormat::_1, name, false);
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
