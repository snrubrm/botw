#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <thread/seadCriticalSection.h>

namespace ksys::act {

class Chemical;

// Name from the CSV (ActorChemicals::*). Actor::mChemical (+0x6a8). ctor 0x7100e36ebc, vtable
// 0x71024e63f0 (getNodeClassType, D1 0x7100e36f0c, D0 0x7100e37168).
// Holds two arrays of 0x2d8-byte elements (ctor 0x7100e399c0) whose second base (+0x40) is a
// Chemical; the first _58 entries live in _60, the following _80 entries in _78.
// TODO: incomplete.
class ActorChemicals : public sead::hostio::Node {
public:
    ActorChemicals();
    virtual ~ActorChemicals();

    Chemical* getStuff(int idx);

    /* 0x08 */ sead::CriticalSection mCS;
    /* 0x48 */ bool _48 = false;
    /* 0x50 */ void* _50 = nullptr;
    /* 0x58 */ s32 _58 = 0;
    /* 0x60 */ void* _60 = nullptr;
    /* 0x68 */ u32 _68 = 0;
    /* 0x6c */ u32 _6c = 0;
    /* 0x70 */ s32 _70 = 0;
    /* 0x78 */ void* _78 = nullptr;
    /* 0x80 */ s32 _80 = 0;
};

}  // namespace ksys::act
