#pragma once
#include <basis/seadTypes.h>

namespace nn::g3d {
class ResFile;
}

namespace nn::gfx { class ResTexture; }

namespace ksys::res {

nn::g3d::ResFile* sub_7100FDDB40(void* data);
void sub_7100FDDB70(nn::g3d::ResFile* file);

u32 sub_7100FDDBFC(const nn::gfx::ResTexture* texture);
s32 sub_7100FDDC0C(const nn::gfx::ResTexture* texture);
s32 sub_7100FDDC14(const nn::gfx::ResTexture* texture);
u32 sub_7100FDDC1C(const nn::gfx::ResTexture* texture);

}  // namespace ksys::res
