#pragma once

#include <nn/ui2d/ResourceAccessor.h>

namespace eui {

// The original constructor and RTTI prove this ResourceAccessor derivation.
// Its instance layout and remaining virtual interface are not modelled here.
class MultiArcResourceAccessor : public nn::ui2d::ResourceAccessor {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::ResourceAccessor)

    // 0x7100be022c: archive animation lookup; writes the byte size when requested.
    const void* sub_7100BE022C(const char* layout_name, const char* animation_name, u32* size);
};

}  // namespace eui
