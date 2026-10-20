#pragma once

#include <basis/seadTypes.h>

namespace nn::g3d {
class ResShaderProgram;
}

namespace gsys {

class G3dResShaderProgramEx;

// The 0x10-byte shader program pair: the constructor 0x7100c3d480 and clear 0x7100c3d488
// zero both pointers, set 0x7100c3d494 stores the resource and its extension, and copyTo
// 0x7100c3d49c copies exactly 0x10 bytes.
class ModelShaderProgram {
public:
    ModelShaderProgram();
    ~ModelShaderProgram();

    void clear();
    void set(const nn::g3d::ResShaderProgram* res, G3dResShaderProgramEx* ex);
    void copyTo(ModelShaderProgram* out) const;

private:
    const nn::g3d::ResShaderProgram* mResShaderProgram;
    G3dResShaderProgramEx* mEx;
};
static_assert(sizeof(ModelShaderProgram) == 0x10);

}  // namespace gsys
