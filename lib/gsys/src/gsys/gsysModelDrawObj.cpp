#include <gsys/gsysModelDrawObj.h>

#include <gsys/gsysModelDynamicEnvInfo.h>

namespace gsys {

agl::lght::LocalLightMapObj* ModelDrawObj::getReferenceLocalLightMapObj() const {
    if (!mDynamicEnvInfo)
        return nullptr;
    return mDynamicEnvInfo->getReferenceLocalLightMapObj();
}

}  // namespace gsys
