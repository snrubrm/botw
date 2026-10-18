#include "gsys/gsysModelRig.h"

namespace gsys {

ModelRig::ModelRig()
    : mModelName(sead::FixedSafeString<64>("untitled"), "ModelName", "モデル名", this),
      mBonePrefix(sead::FixedSafeString<64>("untitled"), "BonePrefix", "ボーンプリフィックス", this),
      mMaterialPrefix(sead::FixedSafeString<64>("untitled"), "MaterialPrefix",
                      "マテリアルプリフィックス", this) {}

}  // namespace gsys
