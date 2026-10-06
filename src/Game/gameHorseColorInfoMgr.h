#pragma once

// Partial declaration: name from CSV HorseColorInfoMgr::createInstance (0x710094c374).
// Source namespace remains unknown; global spelling preserves the CSV placeholder.
// No instance layout or construction is modeled here.
class HorseColorInfoMgr {
public:
    // Original instance pointer 0x71025d6708 (GOT 0x71025824d0).
    static HorseColorInfoMgr* instance() { return sInstance; }
    static HorseColorInfoMgr* sInstance;

    // 0x710094d018: declaration-only model creation request.
    void sub_710094D018();
    // 0x710094d0f8 (declared only; called after the horse layout is unloaded)
    void sub_710094D0F8();

    u8 _0[0x28];
    /* 0x28 */ u8 _28;  // bit 1: the horse layout is already available
    u8 _29[3];
    /* 0x2c */ s32 _2c;  // 2: the layout resource is loaded on request
};
