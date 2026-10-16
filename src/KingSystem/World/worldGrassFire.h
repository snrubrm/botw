#pragma once

#include <common/aglUniformBlock.h>
#include <container/seadBuffer.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::world {

// Placeholder names for three small classes {vptr, sead::Buffer} whose destructors only free the buffer
// (vtables 0x7102503c88, 0x710251ced0, 0x710251cef0; no RTTI). The element types are unknown (trivial).
class Unk_7102503c88 {
public:
    virtual ~Unk_7102503c88() { mBuffer.freeBuffer(); }

    sead::Buffer<u8> mBuffer;
};
KSYS_CHECK_SIZE_NX150(Unk_7102503c88, 0x18);

class Unk_710251ced0 {
public:
    virtual ~Unk_710251ced0() { mBuffer.freeBuffer(); }

    sead::Buffer<u8> mBuffer;
};
KSYS_CHECK_SIZE_NX150(Unk_710251ced0, 0x18);

class Unk_710251cef0 {
public:
    virtual ~Unk_710251cef0() { mBuffer.freeBuffer(); }

    sead::Buffer<u8> mBuffer;
};
KSYS_CHECK_SIZE_NX150(Unk_710251cef0, 0x18);

// Placeholder name (vtable 0x710251cea8, ctor 0x71012e1d5c, size 0x4fde8): created next to the grass objects by
// 0x710114eab0, in the GrassFire element area of the binary. Only the members the destructor tears down are
// modelled.
class Unk_710251cea8 {
public:
    virtual ~Unk_710251cea8();

    void* _8;
    sead::CriticalSection _10;
    sead::Buffer<agl::UniformBlock> _50;
    u8 _60[0x70 - 0x60];
    Unk_7102503c88 _70;
    Unk_710251ced0 _88;
    Unk_710251cef0 _a0;
};

}  // namespace ksys::world
