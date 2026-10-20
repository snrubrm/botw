#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Sound/sndBarslistArchive.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/Thread/LowPrioThreadMgr.h"
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

// NON_MATCHING: the original stores user_data / remove_callback as two separate words, ours merges them
// into one stp (4 bytes shorter).
// 0x7101058b74 (placeholder name): submits the low-priority request that runs mDelegate's function
// 0x7101057e74 (clear the ".bars" cache and load the title BGM pack voices).
bool Unk_SoundMgr60::sub_7101058B74(TaskPostRunCallback* callback) {
    LowPrioThreadMgr::Request request;
    request.lane_id = 1;
    request.flags = 6;
    request.delegate = &mDelegate;
    request.post_callback = callback;
    return LowPrioThreadMgr::instance()->submitRequest(request);
}

// 0x7101058bf4 (placeholder name): runs the +0x48 entry work and the Mii voice queue hook.
void Unk_SoundMgr60::sub_7101058BF4() {
    _48.sub_71012C917C();
    mMiiSoundRequests.sub_71012CE054();
}

// 0x7101058c1c (placeholder name): the same pair of hooks with the other entry and queue methods.
void Unk_SoundMgr60::sub_7101058C1C() {
    _48.sub_71012CABB4();
    mMiiSoundRequests.sub_71012CE058();
}

// 0x710105936c (placeholder name): unloads the SLink reader's handle and the scene static bars handle, then
// the +0x48 member's handles.
void Unk_SoundMgr60::sub_710105936C() {
    mSlinkResources.mHandles[0].requestUnload();
    _1408.requestUnload();
    _48.sub_71012CBB90();
}

// 0x71010593a0 (placeholder name): loads the UI bars into the SLink reader and the scene static bars into
// _1408, then the +0x48 member's bars.
void Unk_SoundMgr60::sub_71010593A0() {
    sub_710105844C(&mSlinkResources.mHandles[0], "M_UI.bars", true, false);
    sub_710105844C(&_1408, "M_SceneStatic.bars", true, false);
    _48.sub_71012CBC3C();
}

// 0x7101059420 (placeholder name): runs the +0x48 entry work, the Mii voice queue reset and the +0x828
// entry loads.
void Unk_SoundMgr60::sub_7101059420() {
    _48.sub_71012CACD4();
    mMiiSoundRequests.sub_71012CE100();
    _828.sub_710105BD04();
}

// 0x7101057e74 (placeholder name): mDelegate's function: clears the "bars" cache and loads the title BGM
// pack voices.
bool Unk_SoundMgr60::sub_7101057E74(void*) {
    res::ResourceMgrTask::instance()->clearCacheWithFileExtension("bars");
    loadVoiceFromTitleBGPack(this);
    return true;
}

// 0x7101058650 (placeholder name): reloads the scene static bars, the voice cache and the expression sound
// bars, then the title BGM pack voices.
void Unk_SoundMgr60::sub_7101058650() {
    _48.sub_71012C911C();
    if (!_1408.isSuccess())
        sub_710105844C(&_1408, "M_SceneStatic.bars", true, false);
    auto* cache = SoundMgr::instance()->_48->_8;
    if (!cache->_8)
        StaticVoicePackStuff(cache, mHeap, true);
    if (!(_13e8._18 & 1))
        sub_7101058734("ExpressionSound", &_13e8, mHeap, false);
    loadVoiceFromTitleBGPack(this);
}

// ResourceBars construction/destruction notifications: empty in the release build.
void Unk_SoundMgr60::sub_7101059450(aal::AudioResource* resource) {}

void Unk_SoundMgr60::sub_7101059454(aal::AudioResource* resource) {}

}  // namespace ksys::snd
