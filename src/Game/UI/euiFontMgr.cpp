#include "Game/UI/euiFontMgr.h"
#include "Game/UI/euiTypes.h"
#include <nn/font/font_TextureCache.h>
#include <thread/seadThreadUtil.h>
#include <gfx/nin/seadGraphicsNvn.h>

namespace eui {

ScalableFontMgr::InitializeArg::InitializeArg()
    : heap(nullptr), texture_cache_arg(nullptr), font_info(nullptr), num_fonts(0),
      thread_priority(sead::ThreadUtil::ConvertPrioritySeadToPlatform(17)),
      affinity(sead::CoreId::cMain) {}

// D1 is folded into sead::Thread::~Thread (0x7100b18e58) in the original; D0 0x7100be5bc0
ScalableFontMgr::UpdateTextureCacheThread::~UpdateTextureCacheThread() = default;

// 0x7100be5b98
void ScalableFontMgr::UpdateTextureCacheThread::calc_(sead::MessageQueue::Element) {
    mTextureCache->UpdateTextureCache();
    mUpdatePending = false;
}

SEAD_SINGLETON_DISPOSER_IMPL(FontMgr)

// 0x7100be3420
void FontMgr::initialize(sead::Heap* heap, void* data, u32 size,
                         const sead::Buffer<const char*>& names,
                         ScalableFontMgr* scalable_font_mgr) {
    mScalableFontMgr = scalable_font_mgr;
    if (data) {
        mArchive.initialize(heap, data, size);
        mFonts.tryAllocBuffer(mArchive.getResource()->getEntryNum(), heap, 8);
    }
    if (names.size() > 0) {
        mFontsByMessageIndex.tryAllocBuffer(names.size(), heap, 8);
        mFontsByMessageIndex.fill(nullptr);
    }
    if (mArchive.getResource()) {
        sead::Graphics::instance()->lockDrawContext();
        {
            SharcArchive::FileReader reader;
            mArchive.startFileReader(&reader);
            while (reader.readNext()) {
                mFonts[reader.mIndex].SetResource(
                    sead::GraphicsNvn::instance()->getNnDevice(),
                    const_cast<void*>(reader.mDevice.mArchive->getFileFast(reader.mIndex, nullptr)),
                    nullptr, 0, 0);
                mFonts[reader.mIndex].RegisterTextureViewToDescriptorPool(RegisterSlotForTexture,
                                                                         nullptr);
                const s32 count = names.size();
                if (count != 0) {
                    const char* const* names_buffer = names.getBufferPtr();
                    for (s32 i = 0; i != count; ++i) {
                        if (reader.mEntry.name == sead::SafeString(names_buffer[i])) {
                            mFontsByMessageIndex[i] = &mFonts[reader.mIndex];
                            break;
                        }
                    }
                }
            }
        }
        sead::Graphics::instance()->unlockDrawContext();
    }
    if (mScalableFontMgr) {
        s32 index = 0;
        for (const char* name : names) {
            if (auto* font = mScalableFontMgr->getFont(name))
                mFontsByMessageIndex[index] = font;
            ++index;
        }
    }
}

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
