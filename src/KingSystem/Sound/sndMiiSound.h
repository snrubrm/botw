#pragma once

#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::mii {
class UMii;
}

namespace ksys::snd {

// XLink allocates 0x160 bytes at 0x71012303ec and constructs this object at 0x71012cd2a4.
// Its vtable at 0x710251b6f0 contains only the two destructor entries.
class Unk_710251b6f0 {
public:
    Unk_710251b6f0();
    virtual ~Unk_710251b6f0();

    void sub_71012CD4E8(sead::Heap* heap, mii::UMii* umii);
    void sub_71012CD614();
    void sub_71012CD7A4();
    bool sub_71012CD880(const sead::SafeString& name, bool is_mii);
    // 0x71012cda30 requests unload on the handle at +0xc0 and clears the state at +8.
    void requestUnloadMaybe();
    // inline-only in the original; name is a guess. The handle query repeats in
    // 0x7101230d20, 0x71012cd614 and 0x71012cdac4.
    bool hasRequestedLoad() const { return mHandle.requestedLoad(); }

private:
    u32 mState = 0;
    sead::FixedSafeString<64> mName;
    sead::FixedSafeString<64> mPendingName;
    res::Handle mHandle;
    f32 mTimer = 0.0f;
    u32 _114 = 0;
    bool mIsMii = false;
    bool _119 = false;
    bool _11a = false;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b6f0, 0x160);

}  // namespace ksys::snd
