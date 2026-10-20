#pragma once

#include <common/aglDisplayList.h>
#include "gsys/gsysModelShaderProgram.h"

namespace gsys {

// Constructor 0x7100c7d0e0 and destructor 0x7100c09a94: a shader program, a flag, a pointer and
// three display lists.
class ModelAssignRenderInfo {
public:
    ModelAssignRenderInfo();
    ~ModelAssignRenderInfo();

private:
    ModelShaderProgram mShaderProgram;
    bool _10 = false;
    void* _18 = nullptr;
    agl::DisplayList mDisplayLists[3];
};
static_assert(sizeof(ModelAssignRenderInfo) == 0x740);

}  // namespace gsys
