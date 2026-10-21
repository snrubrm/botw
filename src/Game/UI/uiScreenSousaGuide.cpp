#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiTUStatics.h"

namespace uking::ui {

// The TU's statics (static initializer 0x7100a539a4), merged into the block at 0x71025f34f0 after the
// uiTUStatics.h objects.
static sead::SafeString sLayoutName = "SousaGuide_00";

// A controls guide entry: a value (placeholder name) and its message label.
struct SousaGuideEntry {
    s32 type;
    sead::SafeString label;
};

static SousaGuideEntry sUnk_71025F3658[] = {
    {6, "0003"},
    {20, "0002"},
    {25, "0001"},
    {26, "0000"},
    {13, "0026"},
    {13, "0025"},
    {28, "0009"},
    {29, "0008"},
    {28, "0030"},
    {29, "0010"},
    {2, "0012"},
    {10, "0013"},
    {18, "0011"},
    {28, "0027"},
    {29, "0015"},
    {28, "0016"},
    {13, "0018"},
    {14, "0017"},
    {2, "0028"},
    {13, "0019"},
    {13, "0020"},
    {20, "0022"},
    {28, "0024"},
    {27, "0023"},
    {25, "0029"},
    {9, "0031"},
    {6, "0032"},
    {28, "0034"},
    {25, "0033"},
    {6, "0004"},
    {1, "0005"},
    {28, "0007"},
    {28, "0021"},
};
static sead::Buffer<SousaGuideEntry> sUnk_71025F3648(sUnk_71025F3658);

// 0x7100a5400c
const char* ScreenSousaGuide::getLayoutName_() const {
    return sLayoutName.cstr();
}

}  // namespace uking::ui
