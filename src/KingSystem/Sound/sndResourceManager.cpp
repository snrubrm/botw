#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU's static initialiser is 0x7101057c2c (`_GLOBAL__sub_I_sndResourceManager.cpp`).
static util::InitTimeInfo sInitTimeInfo;

Unk_7102502950::~Unk_7102502950() {
    mHandles.freeBuffer();
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
