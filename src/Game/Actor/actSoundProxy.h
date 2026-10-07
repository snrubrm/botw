#pragma once

#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

// CSV SoundProxy. 2026-10-07: factory 0x7101059d08 allocates 0x8d0 bytes;
// RTTI static 0x710260ef68 uses Derive<ksys::act::Actor>. Vtable 0x7102502bf8.
// The manager registration and destructor helpers remain undecompiled.
class SoundProxy : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(SoundProxy, ksys::act::Actor)
public:
    explicit SoundProxy(const CreateArg& arg);
    ~SoundProxy() override;
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

private:
    u8 _840[0x8d0 - 0x840];
};
KSYS_CHECK_SIZE_NX150(SoundProxy, 0x8d0);

}  // namespace uking::act
