#include "Game/UI/euiFontMgr.h"

namespace eui {

// 0x7100be5684
Font* ScalableFontMgr::getFont(const sead::SafeString& name) {
    for (auto& entry : mFonts) {
        if (name == entry.name)
            return &entry.font;
    }
    return nullptr;
}

// 0x7100be5b40
const char* ScalableFontMgr::findFontName(const nn::font::ScalableFont* font) const {
    for (auto& entry : mFonts) {
        if (&entry.font == font)
            return entry.name.cstr();
    }
    return nullptr;
}

}  // namespace eui
