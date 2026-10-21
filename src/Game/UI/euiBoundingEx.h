#pragma once

#include <basis/seadTypes.h>
#include <nn/ui2d/Bounding.h>

namespace eui {

// A ui2d bounding control (CSV name; only the constructors and the deleting destructor are decompiled). It adds no
// members to nn::ui2d::Bounding.
class BoundingEx : public nn::ui2d::Bounding {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Bounding)

    // 0x7100bf1180
    BoundingEx(const nn::ui2d::ResBounding* res, const nn::ui2d::ResBounding* res2,
               const nn::ui2d::BuildArgSet& arg);
    // 0x7100bf11b0
    BoundingEx(const BoundingEx& other);
    // 0x7100bf11e0
    ~BoundingEx() override;
};

}  // namespace eui
