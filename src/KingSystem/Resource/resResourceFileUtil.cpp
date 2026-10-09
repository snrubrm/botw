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

u32 sub_7100FDDBFC(const nn::gfx::ResTexture* texture) {
    return texture->ToData().textureDataSize;
}

s32 sub_7100FDDC0C(const nn::gfx::ResTexture* texture) {
    return texture->GetTextureInfo()->GetWidth();
}

s32 sub_7100FDDC14(const nn::gfx::ResTexture* texture) {
    return texture->GetTextureInfo()->GetHeight();
}

u32 sub_7100FDDC1C(const nn::gfx::ResTexture* texture) {
    return texture->ToData().alignment;
}

}  // namespace ksys::res
