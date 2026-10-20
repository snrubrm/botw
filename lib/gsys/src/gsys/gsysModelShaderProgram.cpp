#include <gsys/gsysModelShaderProgram.h>

namespace gsys {

ModelShaderProgram::ModelShaderProgram() : mResShaderProgram(nullptr), mEx(nullptr) {}

ModelShaderProgram::~ModelShaderProgram() = default;

void ModelShaderProgram::clear() {
    mResShaderProgram = nullptr;
    mEx = nullptr;
}

void ModelShaderProgram::set(const nn::g3d::ResShaderProgram* res, G3dResShaderProgramEx* ex) {
    mResShaderProgram = res;
    mEx = ex;
}

void ModelShaderProgram::copyTo(ModelShaderProgram* out) const {
    out->mResShaderProgram = mResShaderProgram;
    out->mEx = mEx;
}

}  // namespace gsys
