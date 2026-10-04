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
};
