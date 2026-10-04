#pragma once

#include <container/seadBuffer.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <nn/font/font_ResFont.h>
#include "Game/UI/euiSharcArchive.h"
#include "KingSystem/Utils/Types.h"

namespace eui {

using Font = nn::font::Font;

class ScalableFontMgr {
public:
    // 0x7100be5684: the font of the scalable font set for `name` (null if there is none)
    Font* getFont(const sead::SafeString& name);
    // 0x7100be55a8 (no CSV name): per-frame update of the texture cache (called from ScreenMgr::update)
    void sub_7100BE55A8();
};

// The font manager singleton (CSV: eui::FontMgr::*, object size 0x60 per createInstance 0x7100be332c): the fixed fonts
// come from a font archive (one font per file, in the archive's file order), the others from the ScalableFontMgr.
class FontMgr {
    SEAD_SINGLETON_DISPOSER(FontMgr)
    FontMgr() = default;

public:
    virtual ~FontMgr() = default;

    ScalableFontMgr* getScalableFontMgr() const { return mScalableFontMgr; }

    // 0x7100be38a4
    Font* tryGetFont(const sead::SafeString& name) const;
    // 0x7100be3930 / 0x7100be3914 (const; the same code)
    Font* getFontByMessageIndex(u32 index);
    Font* getFontByMessageIndex(u32 index) const;
    // 0x7100be394c
    void setRubyFont(const sead::SafeString& name);

private:
    /* 0x28 */ SharcArchive mArchive;
    // 0x7100be3420 constructs an array of ResFont objects, with the original 0xa8-byte stride.
    /* 0x30 */ sead::Buffer<nn::font::ResFont> mFonts;
    /* 0x40 */ sead::Buffer<Font*> mFontsByMessageIndex;
    /* 0x50 */ Font* mRubyFont = nullptr;
    /* 0x58 */ ScalableFontMgr* mScalableFontMgr = nullptr;
};

}  // namespace eui
