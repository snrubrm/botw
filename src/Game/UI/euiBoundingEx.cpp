#include "Game/UI/euiBoundingEx.h"

namespace eui {

// 0x7100bf1180
BoundingEx::BoundingEx(const nn::ui2d::ResBounding* res, const nn::ui2d::ResBounding* res2,
                       const nn::ui2d::BuildArgSet& arg)
    : nn::ui2d::Bounding(res, res2, arg) {}

// 0x7100bf11b0
BoundingEx::BoundingEx(const BoundingEx& other) : nn::ui2d::Bounding(other) {}

// 0x7100bf11e0
BoundingEx::~BoundingEx() = default;

}  // namespace eui
