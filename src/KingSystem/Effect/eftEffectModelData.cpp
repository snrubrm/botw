#include "KingSystem/Effect/eftEffectModelMgr.h"
#include "KingSystem/Effect/eftEffect.h"
#include "Game/gameGraphics.h"
#include <gsys/gsysEffectModelDrawMgr.h>
#include <gsys/gsysModelResource.h>
#include <gsys/gsysG3dResModelEx.h>
#include <nn/g3d/ResFile.h>
#include <nn/g3d/ResModel.h>
#include "KingSystem/Resource/resBfRes.h"

namespace ksys::eft {

// NON_MATCHING: string-copy temporaries and the model search loop are scheduled differently.
bool EffectModelData::addEffectModel_0(sead::Heap* heap, const char* name,
                                       res::BfRes* resource) {
    auto* model_resource = resource->_50;
    mModelCount = 0;
    const s32 model_count = model_resource->getResFile()->mModelCount;
    for (s32 i = 0; i < model_count; ++i) {
        const sead::SafeString model_name(model_resource->getResModelEx(i)->getResModel()->GetName());
        if (model_name.findIndex("_Fxmdl") != -1) {
            mModelNames[mModelCount].copy(model_name);
            mModelNamePtrs[mModelCount] = mModelNames[mModelCount].cstr();
            ++mModelCount;
        } else if (model_name.findIndex("_EffectModel") != -1) {
            mModelNames[mModelCount].copy(model_name);
            mModelNamePtrs[mModelCount] = mModelNames[mModelCount].cstr();
            ++mModelCount;
        }
        if (i + 1 < model_count && mModelCount > 7) {
            sead::FormatFixedSafeString<128> label("EffectModelData::addEffectModel[%s]",
                                                  mName.cstr());
            sead::FormatFixedSafeString<256> message(
                "EffectModelData::addEffectModel[%s] エフェクトモデルの最大登録数[%d]を超えている",
                mName.cstr(), 8);
            break;
        }
    }
    if (mModelCount == 0)
        return false;
    mName.copy(name);
    mRes = resource;
    auto* scene = Graphics::instance()->mModelScenes(0);
    gsys::EffectModelDrawUnit::CreateArg arg;
    arg._0 = scene->mContextNum;
    arg._4 = 64;
    arg.mModelScene = scene;
    arg.mResource = model_resource;
    arg.mNames = mModelNamePtrs;
    arg.mCount = mModelCount;
    mDrawModelId = scene->mEffectModelDrawMgr->addModel(arg, heap);
    if (mDrawModelId != u32(-1)) {
        res::Unk_71024f9958::InitArg texture_arg;
        auto* unit = scene->mEffectModelDrawMgr->getUnit(mDrawModelId);
        if (unit && unit->mModel)
            texture_arg.model = unit->mModel;
        texture_arg.heap = heap;
        texture_arg.resource = resource;
        texture_arg.name = "EffectModelData";
        mTextureLinks.sub_7100FDD4A8(texture_arg);
    }
    return true;
}

s32 EffectModelData::decRefCnt() {
    Effect::instance()->debugLog("EffectModelData::decRefCnt() : [mRefCnt=%d -> %d] %s\n",
                                 mRefCount, mRefCount - 1, mName.cstr());
    if (mRefCount <= 0) {
        sead::FormatFixedSafeString<256> message(
            "EffectModelData::addEffectModel[%s] エフェクトモデルの参照カウンタ[%d]が不正",
            mName.cstr(), mRefCount);
    }
    --mRefCount;
    if (mRefCount == 0) {
        Graphics::instance()->mModelScenes(0)->mEffectModelDrawMgr->requestDeleteModel(mDrawModelId);
        _1 = true;
    }
    return mRefCount;
}

bool EffectModelData::finalize() {
    if (mRefCount != 0)
        return false;
    mTextureLinks.sub_7100FDD264();
    if (mDrawModelId != u32(-1) &&
        !Graphics::instance()->mModelScenes(0)->mEffectModelDrawMgr->execDeleteModel(mDrawModelId)) {
        sead::FormatFixedSafeString<128> label("EffectModelData::finalize[%s]", mName.cstr());
        sead::FormatFixedSafeString<256> message(
            "EffectModelData::finalize[%s] エフェクトモデルの二重解放が発生", mName.cstr());
    }
    _0 = false;
    _1 = false;
    return true;
}

}  // namespace ksys::eft
