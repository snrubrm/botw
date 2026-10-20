#pragma once

#include <basis/seadTypes.h>
#include <gfx/seadColor.h>
#include <prim/seadSafeString.h>

// The material colors and texture names copied by 0x710094c8cc, after initialization at
// 0x7100a5090c. ScreenShopHorse consumes the four colors and both 64-character names.
struct HorseColorInfo {
    HorseColorInfo();
    sead::Color4f mColors[4];
    sead::FixedSafeString<64> mTextureName;
    sead::FixedSafeString<64> mTextureName2;
};
static_assert(sizeof(HorseColorInfo) == 0xf0);

// Partial declaration: name from CSV HorseColorInfoMgr::createInstance (0x710094c374).
// Source namespace remains unknown; global spelling preserves the CSV placeholder.
// No instance layout or construction is modeled here.
class HorseColorInfoMgr {
public:
    // Original instance pointer 0x71025d6708 (GOT 0x71025824d0).
    static HorseColorInfoMgr* instance() { return sInstance; }
    static HorseColorInfoMgr* sInstance;

    // 0x710094c638 (placeholder name): clears the flag byte `_28`.
    void sub_710094C638();
    // 0x710094d018: declaration-only model creation request.
    void sub_710094D018();
    // 0x710094d0f8 (declared only; called after the horse layout is unloaded)
    void sub_710094D0F8();

    // 0x710094cdcc: selects the material animations from the three input values.
    void sub_710094CDCC(const s32* kind, const s32* variant, const s32* frame);
    // 0x710094c8cc: copies colors and texture names from the horse models.
    void sub_710094C8CC(HorseColorInfo* info);

    u8 _0[0x28];
    /* 0x28 */ u8 _28;  // bit 1: the horse layout is already available
    u8 _29[3];
    /* 0x2c */ s32 _2c;  // 2: the layout resource is loaded on request
};
