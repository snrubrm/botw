#include "KingSystem/Resource/resResourceFileUtil.h"
#include <g3d/aglNW4FToNN.h>
#include <nn/g3d/ResFile.h>
#include <nn/gfx/gfx_ResTexture.h>

namespace ksys::res {

nn::g3d::ResFile* sub_7100FDDB40(void* data) {
    auto* file = nn::g3d::ResFile::ResCast(data);
    if (file)
        agl::g3d::ResFile::getResTextureFile(file);
    return file;
}

void sub_7100FDDB70(nn::g3d::ResFile* file) {
    if (auto* texture = agl::g3d::ResFile::getResTextureFile(file)) {
        if (auto* table = texture->ToData().fileHeader.GetRelocationTable())
            table->Unrelocate();
    }
    file->Unrelocate();
}

}  // namespace ksys::res
