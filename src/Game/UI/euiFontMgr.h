#pragma once

#include "KingSystem/Utils/Types.h"

namespace eui {

// Only the parts that other code calls are declared so far.
class ScalableFontMgr {
public:
    // 0x7100be55a8 (no CSV name): per-frame update of the texture cache (called from ScreenMgr::update)
    void sub_7100BE55A8();
};

// The font manager singleton (CSV: eui::FontMgr::*, object size 0x60 per createInstance 0x7100be332c).
class FontMgr {
public:
    ScalableFontMgr* getScalableFontMgr() const { return mScalableFontMgr; }

private:
    u8 _0[0x58];
    /* 0x58 */ ScalableFontMgr* mScalableFontMgr;
};

}  // namespace eui
