#pragma once

#include <container/seadObjList.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Container/LockFreeQueue.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::mii {
class UMii;
}

namespace ksys::xlink {
class XLink;
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
    bool sub_71012CD880(const sead::SafeString& name, bool is_custom_voice);
    bool sub_71012CDA58(const sead::SafeString& name) const;
    // 0x71012cda30 requests unload on the handle at +0xc0 and clears the state at +8.
    void requestUnloadMaybe();
private:
    friend class Unk_710251b710;
    // XLink 0x7101232084, 0x7101234334 and 0x710123445c use this sound
    // object's state, pending name, timer, handle and critical section directly.
    friend class ksys::xlink::XLink;

    u32 mState = 0;
    sead::FixedSafeString<64> mName;
    sead::FixedSafeString<64> mPendingName;
    res::Handle mHandle;
    f32 mTimer = 0.0f;
    u32 _114 = 0;
    bool mIsCustomVoice = false;
    bool _119 = false;
    bool _11a = false;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b6f0, 0x160);

// 0x7101057c4c constructs this member at ResourceManager +0x110, before the next
// member at +0x828. 0x71012cde40 initializes its queue and lock at these offsets.
class Unk_710251b710 {
public:
    Unk_710251b710();
    virtual ~Unk_710251b710();
    // 0x7101057ed4 passes its heap when initializing ResourceManager +0x110.
    void sub_71012CDF98(sead::Heap* heap);
    // 0x7101232084 passes XLink +0xa8 and uses the result to request unload.
    bool sub_71012CE4D8(Unk_710251b6f0* sound);

    // 0x71012ce100 constructs 64-character strings in the 16 free-list nodes,
    // with each ListNode at +0x58 and each node occupying 0x68 bytes.
    sead::FixedObjList<sead::FixedSafeString<64>, 16> mNames;
    util::LockFreeQueue<Unk_710251b6f0> mQueue;
    u32 mCounter = 0;
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(Unk_710251b710, 0x718);

}  // namespace ksys::snd
