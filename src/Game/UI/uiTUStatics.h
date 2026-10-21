#pragma once

#include <gfx/seadColor.h>
#include <limits>
#include <math/seadVector.h>
#include "KingSystem/Utils/InitTimeInfo.h"

// Every UI TU of the original starts its merged static block (GlobalMerge) with these objects,
// built by its static initializer: the InitConstants pair, a FLT_MAX vector and 19 colors.
// The header that defined them is unknown; the names are guesses.
namespace uking::ui {
namespace {

ksys::util::InitConstants sInitConstants;
sead::Vector3f sMaxVector{std::numeric_limits<f32>::max(), std::numeric_limits<f32>::max(),
                          std::numeric_limits<f32>::max()};
sead::Color4f sColorBlack{0.0f, 0.0f, 0.0f, 1.0f};
sead::Color4f sColorBlackHalf{0.0f, 0.0f, 0.0f, 0.5f};
sead::Color4f sColorGray{0.5f, 0.5f, 0.5f, 1.0f};
sead::Color4f sColorGrayHalf{0.5f, 0.5f, 0.5f, 0.5f};
sead::Color4f sColorWhite{1.0f, 1.0f, 1.0f, 1.0f};
sead::Color4f sColorWhiteHalf{1.0f, 1.0f, 1.0f, 0.5f};
sead::Color4f sColorRed{1.0f, 0.0f, 0.0f, 1.0f};
sead::Color4f sColorRedHalf{1.0f, 0.0f, 0.0f, 0.5f};
sead::Color4f sColorGreen{0.0f, 1.0f, 0.0f, 1.0f};
sead::Color4f sColorGreenHalf{0.0f, 1.0f, 0.0f, 0.5f};
sead::Color4f sColorBlue{0.0f, 0.0f, 1.0f, 1.0f};
sead::Color4f sColorBlueHalf{0.0f, 0.0f, 1.0f, 0.5f};
sead::Color4f sColorYellow{1.0f, 1.0f, 0.0f, 1.0f};
sead::Color4f sColorYellowHalf{1.0f, 1.0f, 0.0f, 0.5f};
sead::Color4f sColorMagenta{1.0f, 0.0f, 1.0f, 1.0f};
sead::Color4f sColorMagentaHalf{1.0f, 0.0f, 1.0f, 0.5f};
sead::Color4f sColorCyan{0.0f, 1.0f, 1.0f, 1.0f};
sead::Color4f sColorCyanHalf{0.0f, 1.0f, 1.0f, 0.5f};
sead::Color4f sColorClear{0.0f, 0.0f, 0.0f, 0.0f};

}  // namespace
}  // namespace uking::ui
