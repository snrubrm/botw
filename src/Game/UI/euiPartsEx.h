#pragma once

#include <nn/ui2d/Parts.h>

namespace eui {

// The resource and copy constructors add only the derived vtable. The SDK
// Parts allocation extent is still unresolved, so this interface does not
// establish an allocation size for PartsEx.
class PartsEx : public nn::ui2d::Parts {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Parts)

    PartsEx(const nn::ui2d::ResParts*, const nn::ui2d::ResParts*,
            const nn::ui2d::BuildArgSet&);
    PartsEx(const PartsEx&);
    ~PartsEx() override = default;
};

}  // namespace eui
