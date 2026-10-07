#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

// Placeholder name (vtable 0x7102502138, a sead singleton of size 0xfa8 created by 0x710103af1c and
// initialised from Sound::init (0x710103b1d4); instance pointer at 0x71026108e0, GOT 0x25924b0). Part of the
// sound system (it forwards small requests to a sub-object at +0x68, reads a map-static byml and keeps
// 0x168-byte records). Only what the callers use is declared so far.
class Unk_7102502138 {
    SEAD_SINGLETON_DISPOSER(Unk_7102502138)
    Unk_7102502138();

public:
    virtual ~Unk_7102502138();

    // 0x710103b41c (declared only): forwards `flag` to the sub-object at +0x68 (0x710104d398). Called with false by
    // SetPlayerDrawingSword::oneShot_.
    void sub_710103B41C(bool flag);
    // 0x710103b430 (lane4 s49): forwards `flag` to the sub-object at +0x68 (0x710104d620). Called with false by
    // Player::sub_710088A854.
    void sub_710103B430(bool flag);
    // 0x710103b414 / 0x710103b428 (declared only): forward to the sub-object at +0x68 (0x710104d068 / 0x710104d3b0).
    void sub_710103B414();
    void sub_710103B428();

    // Placeholder (the sub-object at +0x68; declaration only).
    struct Unk68 {
        // 0x710104d398: `_15c = flag` and bit 3 of the dirty flags `_56c`.
        void sub_710104D398(bool flag);
        // 0x710104d620: `_bc = flag` and bit 3 of the dirty flags `_56c`.
        void sub_710104D620(bool flag);
        // 0x710104d068 / 0x710104d3b0 (declared only).
        void sub_710104D068();
        void sub_710104D3B0();

        u8 _0[0xbc];
        /* 0xbc */ bool _bc;
        u8 _bd[0x15c - 0xbd];
        /* 0x15c */ bool _15c;
        u8 _15d[0x56c - 0x15d];
        /* 0x56c */ u16 _56c;
    };

private:
    u8 _28[0x68 - 0x28];
    /* 0x68 */ Unk68* _68;
    u8 _70[0xfa8 - 0x70];
};
KSYS_CHECK_SIZE_NX150(Unk_7102502138, 0xfa8);

}  // namespace ksys::snd
