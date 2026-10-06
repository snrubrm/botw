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

    // Placeholder (the sub-object at +0x68; declaration only).
    struct Unk68 {
        void sub_710104D398(bool flag);
        void sub_710104D620(bool flag);
    };

private:
    u8 _28[0x68 - 0x28];
    /* 0x68 */ Unk68* _68;
    u8 _70[0xfa8 - 0x70];
};
KSYS_CHECK_SIZE_NX150(Unk_7102502138, 0xfa8);

}  // namespace ksys::snd
