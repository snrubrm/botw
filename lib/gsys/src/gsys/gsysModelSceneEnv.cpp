#include <gsys/gsysModelSceneEnv.h>

namespace gsys {

// 0x7100c22124
ModelSceneEnv::~ModelSceneEnv() {
    m_b40 = false;
    finalize();
}

ModelSceneEnv::PartsSet::~PartsSet() {}
void ModelSceneEnv::PartsSet::preprocess() const {}
void ModelSceneEnv::PartsSet::postprocess() const {}
void ModelSceneEnv::PartsSet::prepareBinary() const {}
void ModelSceneEnv::PartsSet::releaseBinary() const {}
void ModelSceneEnv::PartsSet::interpolate(const Parts*, const Parts*, f32) const {}
void ModelSceneEnv::PartsSet::setup(const Parts*, const sead::SafeString&) const {}
bool ModelSceneEnv::PartsSet::save(sead::BufferedSafeStringBase<char>*, const Parts*,
                                   const sead::SafeString&) const {
    return false;
}
ModelSceneEnv::PartsSetUserStr::~PartsSetUserStr() {}
ModelSceneEnv::PartsSetUserBin::~PartsSetUserBin() {}


s32 ModelSceneEnv::AreaEnvGetter::getAccessoryKey(u32 a, u32, u32 c) const {
    return (a & ~1u) == 2 ? static_cast<s32>(c) : -1;
}

bool ModelSceneEnv::AreaEnvGetter::isComposite(u32 index) const {
    switch (index) {
    case 0:
    case 1:
    case 4:
        return false;
    case 2:
    case 3:
        return true;
    default:
        return false;
    }
}

bool ModelSceneEnv::AreaEnvGetter::isViewDependence(u32 index) const {
    switch (index) {
    case 0:
    case 1:
    case 2:
        return true;
    case 3:
    case 4:
        return false;
    default:
        return false;
    }
}

void ModelSceneEnv::drawDebug(agl::DrawContext*, const ModelSceneContext&) const {}

// NON_MATCHING: the body is the same, but clang keeps `result` in registers and materialises it in
// one epilogue; the original stores the zeroed record into the sret buffer before the count check,
// so the success-path binary/size stores land before the source-name call.
// 0x7100c29298
ModelSceneEnv::ApplyUserBinarySlotMaybe ModelSceneEnv::getApplyUserBinarySlot(
    s32 slot, s32 data_set) const {
    const DataSet& data = mDataSets[data_set];

    const s32 index = data.mUserBinaryIndex;
    if (index < 0)
        return {};
    ApplyUserBinarySlotMaybe result = {};
    if (data.mUserBinaryCount <= u32(index))
        return result;

    const ApplySlot* apply_slot = data.mApplySlots[slot];
    const EnvSet& env_set = data.mEnvSets[index];
    const UserBinary* binary = env_set.mUserBinaries[apply_slot->mUserBinaryIndex];
    if (!binary)
        return result;

    result.mBinary = binary->mBinary;
    result.mSize = binary->mSize;
    result.mSourceFileName = binary->mSourceFileName.cstr();
    return result;
}

// 0x7100c2546c
void ModelSceneEnv::setSourceFileName(agl::utl::IParameterIO* io, const sead::SafeString& file_name,
                                      u32 data_set) const {
    const DataSet& data = mDataSets[data_set];
    setSourceFileName_(io, data.mSourceDirectory, file_name);
}

}  // namespace gsys
