#include "KingSystem/Mii/miiModelCreator.h"
#include <prim/seadFormatPrint.h>
#include <resource/seadResource.h>
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::mii {

SEAD_SINGLETON_DISPOSER_IMPL(ModelCreator)

ModelCreator::~ModelCreator() {
    if (mBnetfpHandle.requestedLoad())
        mBnetfpHandle.unloadAndResetUnitFlag20000();
    delete mNetfp;
    if (mConstructionInfoHandle.requestedLoad())
        mConstructionInfoHandle.unloadAndResetUnitFlag20000();
    delete mConstructionInfo;
}

void ModelCreator::init(sead::Heap* heap) {
    loadUMiiConstructionInfo(heap);
    loadUmiiBnetfp(heap);
    _28._9 = false;
}

void ModelCreator::loadUMiiConstructionInfo(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "neModelCreator";
    req.mLoadCompressed = false;
    sead::FormatFixedSafeString<128> path("Mii/UMiiConstructionInfo.byml");
    auto* resource = sead::DynamicCast<sead::DirectResource>(
        mConstructionInfoHandle.load(path, &req, nullptr));
    mConstructionInfo = new (heap) al::ByamlIter(resource->getRawData());
}

void ModelCreator::loadUmiiBnetfp(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "neModelCreator";
    sead::FormatFixedSafeString<128> path("Mii/umii.bnetfp");
    auto* resource =
        sead::DynamicCast<sead::DirectResource>(mBnetfpHandle.load(path, &req, nullptr));
    mNetfp = new (heap) Netfp;
    mNetfp->initParamsAndLoadArchive(resource->getRawData(), heap);
}

sead::SafeArray<sead::SafeString, 4> s_rot_labels{{
    "肩(Clavicle_L/R)",
    "腕(Arm_1_L/R)",
    "脚(Leg_1_L/R:X)",
    "股(Leg_1_L/R:Y)",
}};

}  // namespace ksys::mii

namespace ksys::mii {

bool ModelCreator::sub_7100F4C9FC(const char** out, const s32& index, const Arg& arg) const {
    if (!mConstructionInfo)
        return false;

    al::ByamlIter iter;
    switch (arg.type) {
    case 3:
        if (!mConstructionInfo->tryGetIterByKey(&iter, "Hair"))
            return false;
        break;
    case 1:
        if (!mConstructionInfo->tryGetIterByKey(&iter, "Mouth"))
            return false;
        break;
    default:
        return false;
    }
    sead::FormatFixedSafeString<8> key("%03d", index);
    return iter.tryGetStringByKey(out, key.cstr());
}

}  // namespace ksys::mii
