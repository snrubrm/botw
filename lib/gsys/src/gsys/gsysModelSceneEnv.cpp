#include <gsys/gsysModelSceneEnv.h>

namespace gsys {

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

}  // namespace gsys
