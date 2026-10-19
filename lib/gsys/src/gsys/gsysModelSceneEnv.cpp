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


void ModelSceneEnv::drawDebug(agl::DrawContext*, const ModelSceneContext&) const {}

}  // namespace gsys
