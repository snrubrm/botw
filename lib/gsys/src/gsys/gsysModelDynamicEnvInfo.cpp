#include <gsys/gsysModelDynamicEnvInfo.h>
#include <lighting/aglLocalLightMapObj.h>
#include <heap/seadHeap.h>

namespace gsys {

ModelDynamicEnvInfo::ModelDynamicEnvInfo()
    : mOwned(nullptr), mReference(nullptr), _18(6), _19(0xff) {}

ModelDynamicEnvInfo::~ModelDynamicEnvInfo() {
    delete mOwned;
}

// NON_MATCHING: the separate translation unit leaves the empty CreateArg destructor as a call.
bool ModelDynamicEnvInfo::createLocalLightMapObj(sead::Heap* heap) {
    if (!mReference) {
        auto* obj = new (heap) agl::lght::LocalLightMapObj;
        agl::lght::LocalLightMapObj::CreateArg arg;
        obj->initialize(arg, heap);
        mOwned = obj;
        mReference = obj;
    }
    return true;
}

// NON_MATCHING: the compiler normalizes the returned flag after the conditional store, while
// the original selects the two return values on separate branches.
bool ModelDynamicEnvInfo::setReferenceLocalLightMapObj(const agl::lght::LocalLightMapObj* obj,
                                                      bool flag) {
    if (mOwned && mOwned != obj) {
        delete mOwned;
        mOwned = nullptr;
    }
    if (flag)
        mReference = obj;
    return flag;
}

}  // namespace gsys
