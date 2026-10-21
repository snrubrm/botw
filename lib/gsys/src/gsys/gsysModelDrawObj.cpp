#include <gsys/gsysModelDrawObj.h>

#include <gsys/gsysModelDynamicEnvInfo.h>

namespace gsys {

ModelDrawObj::CreateArg::CreateArg() : _0(1), _4(1), _8(true) {}

// NON_MATCHING: the original stores the vtable 0x7102531f60 at +0x28 (the real ModelOcclusionQuery,
// still the game-side RTTI placeholder Unk_7102531f60); ours is the layout-only class.
ModelDrawObj::ModelDrawObj()
    : _8(0), _a(3), _b(0), _c(0), _10(0), _12(0xffff), _18(nullptr),
      _a0(sead::Vector3f::zero), _ac(0), mMatrix(sead::Matrix34f::ident),
      mPosition(sead::Vector3f::ones), _ec(sead::Matrix34f::ident), _120(nullptr),
      mDynamicEnvInfo(nullptr) {}

void ModelDrawObj::freeBuffer(ModelDrawObj* array, int count) {
    for (int i = 1; i < count; ++i)
        array[i].~ModelDrawObj();
    array[0].~ModelDrawObj();
}

agl::lght::LocalLightMapObj* ModelDrawObj::getReferenceLocalLightMapObj() const {
    if (!mDynamicEnvInfo)
        return nullptr;
    return mDynamicEnvInfo->getReferenceLocalLightMapObj();
}

void ModelDrawObj::setReferenceLocalLightMapObj(const agl::lght::LocalLightMapObj* obj) {
    if (mDynamicEnvInfo)
        mDynamicEnvInfo->setReferenceLocalLightMapObj(obj, true);
}

}  // namespace gsys
