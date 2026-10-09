#pragma once
#include <basis/seadTypes.h>

namespace nn::g3d {
class ResFile;
class ResMaterialAnim;
}

namespace nn::gfx { class ResTexture; }
namespace nn::util { struct BinaryBlockHeader; }

namespace ksys::res {

nn::g3d::ResFile* sub_7100FDDB40(void* data);
void sub_7100FDDB70(nn::g3d::ResFile* file);

s32 sub_7100FDDBA4(const nn::g3d::ResFile* file);
nn::g3d::ResMaterialAnim* sub_7100FDDBAC(nn::g3d::ResFile* file, s32 index);
void sub_7100FDDBD0(nn::gfx::ResTexture* texture);
void sub_7100FDDBD4(nn::gfx::ResTexture* texture);
const nn::util::BinaryBlockHeader* sub_7100FDDBD8(const nn::gfx::ResTexture* texture);
const void* sub_7100FDDBE4(const nn::gfx::ResTexture* texture);
void sub_7100FDDBF0(nn::gfx::ResTexture* texture, nn::util::BinaryBlockHeader* data);
u32 sub_7100FDDC04(const nn::gfx::ResTexture* texture);
nn::gfx::ResTexture* sub_7100FDDC24(nn::gfx::ResTexture* texture);
u32 sub_7100FDDBFC(const nn::gfx::ResTexture* texture);
s32 sub_7100FDDC0C(const nn::gfx::ResTexture* texture);
s32 sub_7100FDDC14(const nn::gfx::ResTexture* texture);
u32 sub_7100FDDC1C(const nn::gfx::ResTexture* texture);

}  // namespace ksys::res
