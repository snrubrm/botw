#include <gsys/gsysModelSceneEnv.h>
#include <detail/aglFileIO.h>
#include <utility/aglParameterIO.h>

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

// NON_MATCHING: the path, extension and tail string objects occupy different stack slots.
bool ModelSceneEnv::setSourceFileName_(agl::utl::IParameterIO* io,
                                       const sead::SafeString& directory,
                                       const sead::SafeString& file_name) {
    if (directory.isEmpty())
        return false;
    if (file_name.isEmpty())
        return false;

    sead::FixedSafeString<260> path;
    const s32 extension_index = file_name.rfindIndex(".");
    const sead::SafeString extension = file_name.getPart(extension_index + 1);
    char* const buffer = path.getBuffer();
    const s32 buffer_size = path.getBufferSize();
    s32 offset = 0;
    {
        sead::BufferedSafeString tail(buffer, buffer_size);
        offset += tail.copy(directory);
    }
    {
        sead::BufferedSafeString tail(buffer + offset, buffer_size - offset);
        offset += tail.append("/");
    }
    {
        sead::BufferedSafeString tail(buffer + offset, buffer_size - offset);
        offset += tail.copy(file_name, extension_index);
    }
    {
        sead::BufferedSafeString tail(buffer + offset, buffer_size - offset);
        offset += tail.append(".");
    }
    {
        sead::BufferedSafeString tail(buffer + offset, buffer_size - offset);
        tail.copy(extension.getPart(1));
    }
    io->_b0.copy(path);
    return true;
}

s32 ModelSceneEnv::searchEnvSetIndex(const sead::SafeString& name, u32 data_set) const {
    const DataSet& data = mDataSets[data_set];
    const s32 count = data.mEnvSets.size();
    const EnvSet* const env_sets = data.mEnvSets.getBufferPtr();
    for (s32 i = 0; i != count; ++i) {
        const EnvSet& env_set = env_sets[i];
        if (env_set.mEnabled && env_set.mName == name)
            return i;
    }
    return -1;
}

void ModelSceneEnv::setFilenameImpl(DataSet* data_set, const sead::SafeString& file_name) {
    data_set->mSourcePath.copy(file_name);
    agl::detail::ReplaceDirectoryDelimiter(&data_set->mSourcePath, '/', false);
    const s32 slash = data_set->mSourcePath.rfindIndex("/");
    if (slash >= 0) {
        data_set->mSourcePath.getBuffer()[slash] = '\0';
        data_set->mSourceDirectory = data_set->mSourcePath;
        data_set->mSourceFileName = data_set->mSourcePath.cstr() + slash + 1;
    }
}

}  // namespace gsys
