#pragma once

#include <prim/seadSafeString.h>

// Partial declaration: name from the CSV EventMgr1::createInstance (0x7100e48658).
// Source namespace remains unknown; global spelling follows the scene placeholders.
// No instance layout or construction is modeled here.
class EventMgr1 {
public:
    // Original instance pointer 0x7102602d30 (GOT 0x710257d5d8).
    static EventMgr1* instance() { return sInstance; }
    static EventMgr1* sInstance;

    // 0x7100e48c44 / 0x7100e4908c: declaration-only counter unregister operations.
    void sub_7100E48C44(const sead::SafeString& name);
    void sub_7100E4908C(const sead::SafeString& name);
};
