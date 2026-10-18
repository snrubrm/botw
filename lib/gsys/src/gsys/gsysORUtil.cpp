#include <gsys/gsysORUtil.h>
#include <prim/seadSafeString.h>

namespace gsys::ORUtil {
// Original table names unknown; entries and ordering are native-backed.
const char* const sUnk_71024D09C0[] = {
    "appli", "detail", "editor", "model", "rndr", "rsrc", "scene", "ss",
    "terminal", "rndr", "top",
};
const char* const sUnk_71024D0A18[] = {"debug", "folder", "setting", "debug"};
const char* const sUnk_71024D0A38[] = {
    "appli", "detail", "editor", "model", "renderer", "resource", "scene", "screenshot",
    "terminal", "renderer", "top",
};

// NON_MATCHING: branch-local string storage and formatting call setup differ.
// Retail retains the icon formatting calls but does not use the Node argument.
void setNodeMeta(sead::hostio::Node*, Category category, Attribute attr, sead::Heap* heap) {
    if (!heap)
        return;
    if (static_cast<unsigned>(attr) == 4) {
        sead::FixedSafeString<1024> icon;
        const sead::FormatFixedSafeString<1024> path(
            "top\\top_%s", sUnk_71024D0A38[static_cast<unsigned>(category)]);
        icon.format("Icon=%%AGL_ROOT%%\\..\\gsys\\tools\\icons\\%s.png", path.cstr());
    } else {
        const sead::FormatFixedSafeString<1024> item(
            "%s_%s", sUnk_71024D09C0[static_cast<unsigned>(category)],
            sUnk_71024D0A18[static_cast<unsigned>(attr)]);
        sead::FixedSafeString<1024> icon;
        const sead::FormatFixedSafeString<1024> path(
            "%s\\%s", sUnk_71024D0A38[static_cast<unsigned>(category)], item.cstr());
        icon.format("Icon=%%AGL_ROOT%%\\..\\gsys\\tools\\icons\\%s.png", path.cstr());
    }
}
}  // namespace gsys::ORUtil
