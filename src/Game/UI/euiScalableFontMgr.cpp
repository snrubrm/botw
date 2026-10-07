#include "Game/UI/euiFontMgr.h"

namespace eui {

SEAD_SINGLETON_DISPOSER_IMPL(ScalableFontMgr)

ScalableFontMgr::ScalableFontMgr() = default;

ScalableFontMgr::~ScalableFontMgr() {
    mUpdateThread->quit(false);
    mUpdateThread->waitDone();
    delete mUpdateThread;
}

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

// NON_MATCHING: the cache-generation and pending-flag stores have different scheduling.
void ScalableFontMgr::sub_7100BE55A8() {
    if (mCacheUpdatePending) {
        if (!mUpdateThread->mUpdatePending) {
            mTextureCache->CompleteTextureCache();
            ++mCacheGeneration;
            mCacheUpdatePending = false;
        }
    } else if (mCacheResetPending) {
        mTextureCache->ResetTextureCache();
        for (auto& entry : mFonts)
            entry.font.RegisterAlternateCharGlyph();
        ++mCacheGeneration;
        mCacheResetPending = false;
    } else if (_8c) {
        auto* thread = mUpdateThread;
        thread->mUpdatePending = true;
        if (thread->sendMessage(1, sead::MessageQueue::BlockType::NonBlocking)) {
            _8c = 0;
            mCacheUpdatePending = true;
        } else {
            thread->mUpdatePending = false;
        }
    }
}

}  // namespace eui
