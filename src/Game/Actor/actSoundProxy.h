#pragma once

#include <thread/seadCriticalSection.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace aal { class Shape; }
namespace xlink2 { class HandleSLink; }

namespace uking::act {

// CSV SoundProxy. 2026-10-07: factory 0x7101059d08 allocates 0x8d0 bytes;
// RTTI static 0x710260ef68 uses Derive<ksys::act::Actor>. Vtable 0x7102502bf8.
// The manager registration and destructor helpers remain undecompiled.
class SoundProxy : public ksys::act::Actor {
    SEAD_RTTI_OVERRIDE(SoundProxy, ksys::act::Actor)
public:
    explicit SoundProxy(const CreateArg& arg);
    ~SoundProxy() override;
    bool prepareInit_(sead::Heap* heap, PrepareArg& arg) override;
    void onPreDeleteStart_(PrepareArg& arg) override;
    void calcMaybe() override;
    static ksys::act::BaseProc* construct(const CreateArg& arg, sead::Heap* heap);

    // 2026-10-07: original 0x710105a10c writes the emitted handle through x2 and returns void.
    void sub_710105A10C(const sead::SafeString& name, xlink2::HandleSLink* handle = nullptr);
    void sub_710105A254(xlink2::HandleSLink* handle, s32 fade_frames);
    void sub_710105A0D0(aal::Shape* shape);
    void sub_710105A0D8(const sead::Vector3f& a, const sead::Vector3f& b);
    void sub_710105A3F8();
    void sub_710105A510();
    void sub_710105A4FC();

    /* 0x840 */ aal::Shape* mShape;
    /* 0x848 */ sead::Vector3f _848;
    /* 0x854 */ sead::Vector3f _854;
    /* 0x860 */ sead::Vector3f _860;
    // SoundProxyRootAction::enter_ copies the source actor's map object here.
    /* 0x870 */ ksys::map::Object* mSourceMapObject;
    /* 0x878 */ sead::CriticalSection mLock;
    /* 0x8b8 */ bool _8b8;
    /* 0x8bc */ s32 _8bc;
    /* 0x8c0 */ u8 _8c0[0x8d0 - 0x8c0];
};
KSYS_CHECK_SIZE_NX150(SoundProxy, 0x8d0);

}  // namespace uking::act
