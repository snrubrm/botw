#include "KingSystem/Mii/miiModelCreator.h"
#include "KingSystem/Mii/miiUMii.h"
#include <container/seadSafeArray.h>
#include <prim/seadFormatPrint.h>
#include <random/seadGlobalRandom.h>
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


// 0x710260c550 (bss; filled from Mii/UMiiConstructionInfo.byml): the Mii actor-name tables, indexed by
// sead::SafeArray::operator[] (which falls back to element 0 on an out-of-range index).
struct ModelCreatorNames {
    u8 _0[0x578];
    sead::SafeArray<sead::SafeString, 8> names8;
    sead::SafeArray<sead::SafeString, 27> names27;
};
static ModelCreatorNames sUnk_710260C550;

const sead::SafeString& ModelCreator::getActorName(const Arg& arg) const {
    switch (arg.type) {
    case 0:
        return sUnk_710260C550.names27[sead::GlobalRandom::instance()->getU32(27)];
    case 1:
        return sUnk_710260C550.names8[sead::GlobalRandom::instance()->getU32(8)];
    default:
        return sead::SafeStringBase<char>::cEmptyString;
    }
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

// 0x7100f5a390 (CSV getModelUMiiHyliaFaceEditBfresPath; placeholder signature): the Hylia face edit model path.
const char* getModelUMiiHyliaFaceEditBfresPath() {
    return "Model/UMii_Hylia_Face_Edit.Tex.bfres";
}

// 0x7100f5a384 (placeholder name): the Hylia face model path.
const char* getModelUMiiHyliaFaceBfresPath() {
    return "Model/UMii_Hylia_Face.Tex.bfres";
}

namespace ksys::mii {

gsys::Model* ModelCreator::createUmiiModel(const UMii& umii, const sead::SafeString& name, void* part_names,
                                           gsys::Model::CreateArg arg, void* out, sead::Heap* heap) {
    switch (*umii.getBody().race) {
    case UMii::Body::Race_Hylian:
        return createUmiiModelRace0(umii, name, part_names, arg, out, heap);
    case UMii::Body::Race_Korok:
        return createUmiiModelRace1(umii, name, part_names, arg, out, heap);
    case UMii::Body::Race_Goron:
        return createUmiiModelRace2(umii, name, part_names, arg, out, heap);
    case UMii::Body::Race_Sheikah:
        return createUmiiModelRace3(umii, name, part_names, arg, out, heap);
    case UMii::Body::Race_Gerudo:
        return createUmiiModelRace4(umii, name, part_names, arg, out, heap);
    case UMii::Body::Race_Zora:
        return createUmiiModelRace5(umii, name, part_names, arg, out, heap);
    case UMii::Body::Race_Rito:
        return createUmiiModelRace6(umii, name, part_names, arg, out, heap);
    default:
        return nullptr;
    }
}

}  // namespace ksys::mii
