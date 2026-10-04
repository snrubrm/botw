#include "Game/UI/euiPictureEx.h"
#include <gfx/nin/seadGraphicsNvn.h>

namespace eui {

// 0x7100be17dc
PictureEx::PictureEx(const nn::ui2d::ResPicture* resource,
                     const nn::ui2d::ResPicture* replacement, const nn::ui2d::BuildArgSet& args)
    : Picture(nullptr, sead::GraphicsNvn::instance()->getNnDevice(), resource, replacement, args) {}

// 0x7100be1838
PictureEx::PictureEx(const PictureEx& other)
    : Picture(other, sead::GraphicsNvn::instance()->getNnDevice()) {}

}  // namespace eui
