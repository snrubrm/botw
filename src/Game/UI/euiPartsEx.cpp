#include "Game/UI/euiPartsEx.h"

namespace eui {

// 0x7100be1688
PartsEx::PartsEx(const nn::ui2d::ResParts* resource, const nn::ui2d::ResParts* override_resource,
                 const nn::ui2d::BuildArgSet& args)
    : nn::ui2d::Parts(resource, override_resource, args) {}

// 0x7100be16b8
PartsEx::PartsEx(const PartsEx& other) : nn::ui2d::Parts(other) {}

}  // namespace eui
