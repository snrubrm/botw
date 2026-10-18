#include "KingSystem/Mii/miiHylianInfo.h"
#include <g3d/aglMaterialAnimObj.h>
#include <gsys/gsysModelAnimation.h>
#include <nn/g3d/MaterialAnimObj.h>
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"

namespace ksys::mii {

void HylianInfo::sub_71012A504C(gsys::ModelAnimation* animation) {
    const auto key = animation->searchMaterialAnmKey(static_cast<gsys::MaterialAnmType>(3),
                                                    "Face_Default_Blink");
    if (key.isValid())
        animation->setMaterialAnmByKey(mMaterialAnmSlot, key, 0.0f);
    else
        mMaterialAnmSlot = -1;
}

// NON_MATCHING: material-object guards and fallback texture branches are ordered differently.
void HylianInfo::sub_71012A5304(gsys::ModelAnimation* animation, res::Unk_71024f9938* cache,
                               res::Unk_71024f9a70* loader) {
    if (!cache || mMaterialAnmSlot < 0)
        return;
    auto& slot = animation->getMaterialAnms()[mMaterialAnmSlot];
    const auto key = slot.getKey();
    if (!key.isValid())
        return;
    if (key.type != 3 || !slot.animObj) {
        animation->sub_7100BFDD10(mMaterialAnmSlot);
        mMaterialAnmSlot = -1;
        return;
    }
    auto* material = static_cast<nn::g3d::MaterialAnimObj*>(slot.animObj);
    for (s32 i = 0; i < mTextureNames.size(); ++i) {
        auto* texture = cache->sub_7100FDD100(mTextureNames[i], loader);
        if (!texture)
            texture = res::sub_7100FE124C();
        agl::g3d::MaterialAnimObj::SetResTexture(material, i, texture);
    }
}

}  // namespace ksys::mii
