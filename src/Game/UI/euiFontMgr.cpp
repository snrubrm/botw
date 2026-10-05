#include "Game/UI/euiFontMgr.h"
#include <nn/font/font_TextureCache.h>

namespace eui {

// 0x7100be5b98
void ScalableFontMgr::UpdateTextureCacheThread::calc_(sead::MessageQueue::Element) {
    mTextureCache->UpdateTextureCache();
    mUpdatePending = false;
}

SEAD_SINGLETON_DISPOSER_IMPL(FontMgr)

// 0x7100be38a4
Font* FontMgr::tryGetFont(const sead::SafeString& name) const {
    if (auto* archive = mArchive.getResource()) {
        const s32 index = archive->convertPathToEntryID(name);
        if (index >= 0)
            return const_cast<nn::font::ResFont*>(&mFonts[index]);
    }
    if (mScalableFontMgr)
        return mScalableFontMgr->getFont(name);
    return nullptr;
}

// 0x7100be3930
Font* FontMgr::getFontByMessageIndex(u32 index) {
    return mFontsByMessageIndex[index];
}

// 0x7100be3914
Font* FontMgr::getFontByMessageIndex(u32 index) const {
    return mFontsByMessageIndex[index];
}

// 0x7100be394c
void FontMgr::setRubyFont(const sead::SafeString& name) {
    mRubyFont = tryGetFont(name);
}

}  // namespace eui
