#include "Game/UI/euiFontMgr.h"
#include "Game/UI/euiNwAllocator.h"
#include "Game/UI/euiTypes.h"
#include <gfx/seadGraphics.h>
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/font/font_TextureCache.h>

namespace eui {

SEAD_SINGLETON_DISPOSER_IMPL(ScalableFontMgr)

ScalableFontMgr::ScalableFontMgr() = default;

ScalableFontMgr::~ScalableFontMgr() {
    mUpdateThread->quit(false);
    mUpdateThread->waitDone();
    delete mUpdateThread;
}

// NON_MATCHING: the update-thread block is scheduled differently (the original loads the texture cache before the
// thread constructor and stores the thread's fields before its vtable), and the SDK InitializeArg header merges the
// original's two byte fields _e / _f, so the flag store is 16-bit here.
// 0x7100be5328
void ScalableFontMgr::initialize(const InitializeArg& arg) {
    sead::Graphics::instance()->lockDrawContext();

    {
        nn::font::TextureCache::InitializeArg texture_cache_arg = *arg.texture_cache_arg;
        texture_cache_arg.allocate = NwAllocator::ui2dAllocateFunction;
        texture_cache_arg.allocateUserData = arg.heap;

        mTextureCache = new (arg.heap, 8) nn::font::TextureCache;
        mTextureCache->Initialize(sead::GraphicsNvn::instance()->getNnDevice(), texture_cache_arg,
                                  nullptr, 0, 0);
        mTextureCache->RegisterTextureViewToDescriptorPool(RegisterSlotForTexture, nullptr);
    }

    if (arg.num_fonts >= 1)
        mFonts.tryAllocBuffer(arg.num_fonts, arg.heap);

    s32 index = 0;
    for (auto& entry : mFonts) {
        const FontInfo& info = arg.font_info[index];
        entry.name = info.name;

        nn::font::ScalableFont::InitializeArg font_arg;
        font_arg.SetDefault();
        font_arg.pTextureCache = mTextureCache;
        font_arg.fontSize = info.font_size;
        font_arg._c = info._c;
        // The original's InitializeArg has two byte fields here (_e, _f); our SDK header merges them.
        font_arg._e = 0x100;
        entry.font.Initialize(font_arg);
        ++index;
    }

    mUpdateThread = new (arg.heap, 8) UpdateTextureCacheThread(
        "UpdateTextureCacheThread", arg.heap, arg.thread_priority, sead::MessageQueue::BlockType::Blocking,
        0x7fffffff, 0x8000, 0x20);
    mUpdateThread->mTextureCache = mTextureCache;
    mUpdateThread->mUpdatePending = false;
    mUpdateThread->setAffinity(arg.affinity);
    mUpdateThread->start();

    sead::Graphics::instance()->unlockDrawContext();
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
