#include "KingSystem/Sound/sndBgmMgr.h"
#include <resource/seadResource.h>
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/OverlayArenaSystem.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The TU after sndResourceManager.cpp's static initialiser (0x7101057c4c onwards: the SoundMgr::_60 resource
// manager).

// The TU statics at 0x71026150d0 (static initialiser 0x71010597a0, m: the original stores 0x8004ef in the first
// word of the constants and zero in the second). Names are guesses.
namespace {
util::InitConstants sInitConstants;
util::InitTimeInfo sInitTimeInfo;
sead::SafeString sResourceDirectory = "Sound/Resource/";
sead::SafeString sSLinkDatabasePath = "SLink2/SLink2DB.bslnk";
sead::SafeString sResourceListDirectory = "Sound/ResourceList/";
sead::SafeString sCustomVoiceNoActorBars = "NV_Custom_NoActor.bars";
sead::SafeString sUiBars = "M_UI.bars";
sead::SafeString sTestArchivePath = "Sound/test.sarc";
}  // namespace

// NON_MATCHING: the status local sits at a frame-pointer offset in the original.
Unk_7102502978* Unk_SoundMgr60::sub_710105844C(res::Handle* handle, const sead::SafeString& name,
                                               bool use_audio_arena, bool lane2) {
    sead::FixedSafeString<128> path;
    path.format("%s%s", sResourceDirectory.cstr(), name.cstr());
    res::LoadRequest request;
    request.mRequester = "Sound";
    request.mLoadDataAlignment = 0x80;
    request.mBufferSize = 0;
    request._22 = true;
    request.mArena = use_audio_arena ? OverlayArenaSystem::instance()->getAudioArena() : mArena;
    if (lane2)
        request.mLaneId = 2;
    res::Handle::Status status;
    auto* resource = handle->load(path, &request, &status);
    auto* bars = sead::DynamicCast<Unk_7102502978>(resource);
    if (bars && status == res::Handle::Status::_4) {
        bars->sub_7101057588(name);
        return bars;
    }
    return bars;
}

void Unk_SoundMgr60::sub_7101059354(Unk_7102502950* reader) {
    delete reader;
}

sead::DirectResource* Unk_SoundMgr60::tryLoadResource(const sead::SafeString& path, sead::Heap* heap,
                                                      s32 alignment) {
    sead::DirectResource* resource = nullptr;
    loadDirectResource(&resource, path, heap, alignment);
    return resource;
}

// NON_MATCHING: the heap and alignment registers are swapped (x20 / x21).
bool Unk_SoundMgr60::loadDirectResource(sead::DirectResource** out, const sead::SafeString& path,
                                        sead::Heap* heap, s32 alignment) {
    if (!heap)
        heap = mHeap;

    res::ResourceMgrTask::DirectLoadArg arg{};
    arg.req.mPath = path;
    arg.req.mLoadDataAlignment = alignment;
    arg.heap = heap;
    arg.req._22 = true;
    auto* resource = sead::DynamicCast<sead::DirectResource>(res::ResourceMgrTask::instance()->load(arg));
    if (!resource)
        return false;
    *out = resource;
    return true;
}

}  // namespace ksys::snd
