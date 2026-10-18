#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <mc/seadCoreInfo.h>
#include <prim/seadSafeString.h>
#include <thread/seadThread.h>
#include <nn/font/font_ResFont.h>
#include <nn/font/font_ScalableFont.h>
#include <nn/font/font_TextureCache.h>
#include "Game/UI/euiSharcArchive.h"
#include "KingSystem/Utils/Types.h"

namespace nn::font {
class ScalableFont;
class TextureCache;
}

namespace eui {

using Font = nn::font::Font;
class FontMgr;

class ScalableFontMgr {
    SEAD_SINGLETON_DISPOSER(ScalableFontMgr)
public:
    ScalableFontMgr();
    virtual ~ScalableFontMgr();
    // One font of the initialize argument: the name and its size (0x10 bytes; read by initialize).
    struct FontInfo {
        /* 0x00 */ const char* name;
        /* 0x08 */ s32 font_size;
        /* 0x0c */ u16 _c;
        /* 0x0e */ u8 _e;
        /* 0x0f */ u8 _f;
    };
    struct InitializeArg {
        InitializeArg();

        /* 0x00 */ sead::Heap* heap;
        /* 0x08 */ const nn::font::TextureCache::InitializeArg* texture_cache_arg;
        /* 0x10 */ const FontInfo* font_info;
        /* 0x18 */ s32 num_fonts;
        /* 0x1c */ s32 thread_priority;
        /* 0x20 */ sead::CoreIdMask affinity;
    };

    // Only the worker's update and borrowed cache pointer are recovered here.
    // Its construction and the manager's full layout remain undeclared.
    class UpdateTextureCacheThread : public sead::Thread {
    public:
        // The original's constructor is inline (no CSV row): initialize passes a name, the heap, the priority and
        // the queue settings straight to sead::Thread.
        UpdateTextureCacheThread(const sead::SafeString& name, sead::Heap* heap, s32 priority,
                                 sead::MessageQueue::BlockType block_type,
                                 sead::MessageQueue::Element quit_msg, s32 stack_size,
                                 s32 message_queue_size)
            : sead::Thread(name, heap, priority, block_type, quit_msg, stack_size, message_queue_size) {}
        ~UpdateTextureCacheThread() override;

        /* 0x100 */ nn::font::TextureCache* mTextureCache;
        /* 0x108 */ bool mUpdatePending;

    protected:
        void calc_(sead::MessageQueue::Element message) override;
    };

    // A font of the manager together with its name (0x48 bytes).
    struct FontEntry {
        sead::SafeString name;
        nn::font::ScalableFont font;
    };

    // 0x7100be5684: the font of the scalable font set for `name` (null if there is none)
    Font* getFont(const sead::SafeString& name);
    // 0x7100be5b40: the name of the font (null if it does not belong to the manager)
    const char* findFontName(const nn::font::ScalableFont* font) const;
    // 0x7100be5328: creates the texture cache, the scalable fonts and the cache update thread.
    void initialize(const InitializeArg& arg);
    // 0x7100be55a8 (no CSV name): per-frame update of the texture cache (called from ScreenMgr::update)
    void sub_7100BE55A8();

    // 0x7100be57a4: registers printable glyphs, including the fonts selected by tags.
    bool sub_7100BE57A4(const u16* string, u32 length, const nn::font::ScalableFont* font,
                        const FontMgr* font_mgr);

    /* 0x28 */ nn::font::TextureCache* mTextureCache = nullptr;
    /* 0x30 */ sead::Buffer<FontEntry> mFonts;
    /* 0x40 */ sead::CriticalSection mCriticalSection;
    /* 0x80 */ UpdateTextureCacheThread* mUpdateThread = nullptr;
    /* 0x88 */ u32 mCacheGeneration = 0;
    /* 0x8c */ u8 _8c = 0;
    /* 0x8d */ bool mCacheUpdatePending = false;
    /* 0x8e */ bool mCacheResetPending = false;
};
KSYS_CHECK_SIZE_NX150(ScalableFontMgr, 0x90);

// The font manager singleton (CSV: eui::FontMgr::*, object size 0x60 per createInstance 0x7100be332c): the fixed fonts
// come from a font archive (one font per file, in the archive's file order), the others from the ScalableFontMgr.
class FontMgr {
    SEAD_SINGLETON_DISPOSER(FontMgr)
    FontMgr() = default;

public:
    virtual ~FontMgr() = default;

    ScalableFontMgr* getScalableFontMgr() const { return mScalableFontMgr; }

    // 0x7100be3420
    void initialize(sead::Heap* heap, void* data, u32 size,
                    const sead::Buffer<const char*>& names, ScalableFontMgr* scalable_font_mgr);

    // 0x7100be38a4
    Font* tryGetFont(const sead::SafeString& name) const;
    // 0x7100be3930 / 0x7100be3914 (const; the same code)
    Font* getFontByMessageIndex(u32 index);
    Font* getFontByMessageIndex(u32 index) const;
    // 0x7100be394c
    void setRubyFont(const sead::SafeString& name);

private:
    friend class TagProcessor;

    /* 0x28 */ SharcArchive mArchive;
    // 0x7100be3420 constructs an array of ResFont objects, with the original 0xa8-byte stride.
    /* 0x30 */ sead::Buffer<nn::font::ResFont> mFonts;
    /* 0x40 */ sead::Buffer<Font*> mFontsByMessageIndex;
    /* 0x50 */ Font* mRubyFont = nullptr;
    /* 0x58 */ ScalableFontMgr* mScalableFontMgr = nullptr;
};

}  // namespace eui
