#include "KingSystem/Effect/eftEffectModelMgr.h"
#include "KingSystem/Effect/eftEffect.h"
#include "Game/gameGraphics.h"
#include <gsys/gsysEffectModelDrawMgr.h>

namespace ksys::eft {

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
        Graphics::instance()->mModelScenes[0]->mEffectModelDrawMgr->requestDeleteModel(mDrawModelId);
        _1 = true;
    }
    return mRefCount;
}

bool EffectModelData::finalize() {
    if (mRefCount != 0)
        return false;
    mTextureLinks.sub_7100FDD264();
    if (mDrawModelId != u32(-1) &&
        !Graphics::instance()->mModelScenes[0]->mEffectModelDrawMgr->execDeleteModel(mDrawModelId)) {
        sead::FormatFixedSafeString<128> label("EffectModelData::finalize[%s]", mName.cstr());
        sead::FormatFixedSafeString<256> message(
            "EffectModelData::finalize[%s] エフェクトモデルの二重解放が発生", mName.cstr());
    }
    _0 = false;
    _1 = false;
    return true;
}

}  // namespace ksys::eft
