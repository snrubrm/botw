#pragma once

#include <nn/ui2d/Picture.h>

namespace eui {

// Both original constructors call the Picture base constructor and then
// install this class's vtable. No additional fields are recovered.
class PictureEx : public nn::ui2d::Picture {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Picture)

    PictureEx(const nn::ui2d::ResPicture*, const nn::ui2d::ResPicture*,
              const nn::ui2d::BuildArgSet&);
    PictureEx(const PictureEx&);
    ~PictureEx() override = default;
};

}  // namespace eui
