#pragma once

#include <basis/seadTypes.h>

namespace uking {
class Unk_710243b770;
}  // namespace uking

// Placeholder name (CSV NFPThread; ctor 0xf45e58; NFP::_30): the thread object NFP forwards to. Only `_195` (flag byte) and
// the four forwarded methods are declared (names after their addresses; declaration only).
class NFPThread {
public:
    void sub_F48478(uking::Unk_710243b770* listener);  // insertFunctions
    void sub_F484CC(uking::Unk_710243b770* listener);  // eraseFunctions
    void sub_F4851C(const s32* amiibo_id);
    void sub_F48570(const s32* amiibo_id);

    u8 _0[0xd4];
    /* 0xd4 */ s32 _d4;
    u8 _d8[0x195 - 0xd8];
    /* 0x195 */ u8 _195;
};

// Name from the CSV (NFP::createInstance 0xf45988, NFP::init, NFP::quitThread, NFPThread::*): the
// amiibo (nn::nfp) manager singleton in the NFP TU 0xf458b8-0xf48478 (instance pointer 0x710260c120).
// Only the small methods AmiiboMgr uses are declared, and only declared: they read the NFPThread
// at +0x30 and forward to it.
class NFP {
public:
    static NFP* instance() { return sInstance; }

    // 0xf45e0c (CSV NFP::insertFunctions) / 0xf45e14 (CSV NFP::eraseFunctions): add / remove a
    // listener to / from the NFP thread's listener list.
    void insertFunctions(uking::Unk_710243b770* listener);
    void eraseFunctions(uking::Unk_710243b770* listener);

    // 0xf45e1c (CSV NFP::__auto0) / 0xf45e24 (unnamed): AmiiboMgr's constructor / destructor pass
    // the address of a TU-local static int (0x71025bf500: an index into an amiibo id enum).
    void sub_F45E1C(const s32* amiibo_id);
    void sub_F45E24(const s32* amiibo_id);

    // 0xf45ce8 (CSV NFP::returnFalse).
    bool returnFalse() const;
    // 0xf45cf0 (CSV NFP::c) / 0xf45d5c: queue a request (2 / 3) on the NFP thread.
    void sub_F45CF0();
    void sub_F45D5C();
    // 0xf45bb8 (placeholder name): false without a thread, else whether the thread's `_d4` is outside 3-4.
    bool sub_F45BB8() const;
    // 0xf45dc8 / 0xf45dfc: bits 1 / 3 of the thread's flag byte +0x195.
    bool sub_F45DC8() const;
    bool sub_F45DFC() const;

private:
    static NFP* sInstance;

    u8 _0[0x30];
    /* 0x30 */ NFPThread* _30;
};
