#include "KingSystem/Resource/resResourceFileUtil.h"
#include <g3d/aglNW4FToNN.h>
#include <nn/g3d/ResFile.h>
#include <nn/g3d/ResMaterialAnim.h>
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

s32 sub_7100FDDBA4(const nn::g3d::ResFile* file) {
    return file->mMatAnimCount;
}

nn::g3d::ResMaterialAnim* sub_7100FDDBAC(nn::g3d::ResFile* file, s32 index) {
    return &file->mMatAnims[index];
}

void sub_7100FDDBD0(nn::gfx::ResTexture* texture) {
    agl::g3d::ResTexture::sub_7100B3378C(texture);
}

void sub_7100FDDBD4(nn::gfx::ResTexture* texture) {
    agl::g3d::ResTexture::Finalize(texture);
}

const nn::util::BinaryBlockHeader* sub_7100FDDBD8(const nn::gfx::ResTexture* texture) {
    return texture->ToData().pResTextureContainerData.Get()->pTextureData.Get();
}

const void* sub_7100FDDBE4(const nn::gfx::ResTexture* texture) {
    return texture->ToData().pMipPtrArray.Get()[0].Get();
}

void sub_7100FDDBF0(nn::gfx::ResTexture* texture, nn::util::BinaryBlockHeader* data) {
    texture->ToData().pResTextureContainerData.Get()->pTextureData.Set(data);
}

u32 sub_7100FDDC04(const nn::gfx::ResTexture* texture) {
    return 0;
}

nn::gfx::ResTexture* sub_7100FDDC24(nn::gfx::ResTexture* texture) {
    return texture;
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
