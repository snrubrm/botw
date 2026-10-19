#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Sound/sndBarslistArchive.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/OverlayArena.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x7101057c2c (`_GLOBAL__sub_I_sndResourceManager.cpp`).
static util::InitTimeInfo sInitTimeInfo;

// 0x71010581d8: frees the bars pool, destroys the default heap and the overlay arena. The three base
// destructors are empty.
Unk_SoundMgr60::~Unk_SoundMgr60() {
    mBars.freeBuffer();
    if (mHeap)
        mHeap->destroy();
    if (mArena) {
        delete mArena;
        mArena = nullptr;
    }
}

// 0x7101058348 (placeholder name): removes the overlay arena from the resource manager task.
void Unk_SoundMgr60::sub_7101058348() {
    if (mArena)
        res::ResourceMgrTask::instance()->removeOverlayArena(mArena);
}

// 0x7101058364 (placeholder name): loads the four UI bars files into the SLink reader's buffer and the
// three handle members.
void Unk_SoundMgr60::sub_7101058364() {
    mSlinkResources.sub_71010571A4(1, mHeap);
    sub_710105844C(&mSlinkResources.mHandles[0], "M_UI.bars", true, false);
    mSlinkResources._18 |= 1;
    sub_710105844C(&_15f8, "M_UI_DLC1.bars", false, false);
    sub_710105844C(&_1648, "M_UI_DLC2.bars", false, false);
    sub_710105844C(&_1458, "M_StaticPrefetch.bars", false, false);
}

// ResourceBars construction/destruction notifications: empty in the release build.
void Unk_SoundMgr60::sub_7101059450(aal::AudioResource* resource) {}

void Unk_SoundMgr60::sub_7101059454(aal::AudioResource* resource) {}

}  // namespace ksys::snd
