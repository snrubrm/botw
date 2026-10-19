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

// ResourceBars construction/destruction notifications: empty in the release build.
void Unk_SoundMgr60::sub_7101059450(aal::AudioResource* resource) {}

void Unk_SoundMgr60::sub_7101059454(aal::AudioResource* resource) {}

}  // namespace ksys::snd
