#include <gsys/gsysModelDrawObj.h>

#include <gsys/gsysModelDynamicEnvInfo.h>

namespace gsys {

ModelDrawObj::CreateArg::CreateArg() : _0(1), _4(1), _8(true) {}

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
