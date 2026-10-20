#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/System/StarterPackMgr.h"
#include <resource/seadResource.h>
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/System/OverlayArena.h"
#include <resource/seadResourceMgr.h>
#include <heap/seadExpHeap.h>
#include "KingSystem/Sound/sndBarslistArchive.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/System/OverlayArenaSystem.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
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

// NON_MATCHING: factory and overlay-arena temporaries have different stack placement
// and initialization scheduling.
void ResourceManager::initBarsFactoryAndHeap(sead::Heap* heap) {
    mBars.allocBuffer(16, heap);
    if (sead::ResourceMgr::instance())
        res::registerEntryFactory(new (heap) Unk_7102502b50, "bars");
    sead::DirectResource* database = nullptr;
    loadDirectResource(&database, sSLinkDatabasePath, heap, 32);
    _15e0 = database;
    _15e8 = new (heap) BarslistArchive;
    _15e8->loadRes(heap);
    mMiiSoundRequests.sub_71012CDF98(heap);
    mHeap = sead::ExpHeap::create(0x20000, "ResourceManagerWork", heap, 8,
                                  sead::Heap::cHeapDirection_Forward, true);
    OverlayArena::InitArg arg;
    arg.set_flag_8 = true;
    arg.name = "Audio";
    arg.heap = SoundResource::instance()->mSoundResourceHeap;
    arg.min_free_percentage = 5.0f;
    arg.heap2 = SoundResource::instance()->getSoundDebugHeap();
    mArena = new (heap) OverlayArena;
    mArena->init(arg);
}

// NON_MATCHING: the status local sits at a frame-pointer offset in the original.
ResourceBars* ResourceManager::sub_710105844C(res::Handle* handle, const sead::SafeString& name,
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
    auto* bars = sead::DynamicCast<ResourceBars>(resource);
    if (bars && status == res::Handle::Status::_4) {
        bars->sub_7101057588(name);
        return bars;
    }
    return bars;
}

void ResourceManager::sub_7101059354(Unk_7102502950* reader) {
    delete reader;
}

// NON_MATCHING: request temporaries occupy different stack slots, and filename access is
// scheduled differently around the dynamic cast.
void loadVoiceFromTitleBGPack(ResourceManager* resource_manager) {
    sead::ScopedLock<sead::CriticalSection> lock(&resource_manager->_1568);
    const char* locale = sub_710105E7B4(nullptr);
    auto* handle = &resource_manager->_14a8;
    if (handle->isSuccess() && resource_manager->_15a8 == locale)
        return;
    if (handle->isSuccess())
        handle->requestUnload();
    if (!handle->isSuccess()) {
        sead::FixedSafeString<128> path;
        path.format("Voice/%s/%s", locale, sCustomVoiceNoActorBars.cstr());
        res::LoadRequest request;
        request.mRequester = "Sound";
        request.mLoadDataAlignment = 0x80;
        request.mBufferSize = 0;
        request._22 = true;
        request.mArena = resource_manager->mArena;
        auto* pack = StarterPackMgr::instance()->getTitleBGLangPack();
        if (pack && pack->isSuccess())
            request.mPackHandle = pack;
        request._26 = false;
        res::Handle::Status status;
        auto* bars = sead::DynamicCast<ResourceBars>(handle->load(path, &request, &status));
        if (bars && status == res::Handle::Status::_4) {
            bars->sub_7101057588(sCustomVoiceNoActorBars);
            resource_manager->_15a8.copy(locale);
        }
    }
}

// 0x7101058734: loads every entry of the bars list `name` into `reader` as a direct resource load and
// marks the reader as loaded.
void ResourceManager::sub_7101058734(const sead::SafeString& name, Unk_7102502950* reader,
                                    sead::Heap* heap, bool flag) {
    if (!reader)
        return;
    al::ByamlIter iter = _15e8->getIter(name);
    const s32 count = _15e8->getSize(iter);
    if (count >= 1) {
        reader->sub_71010571A4(count, heap);
        for (s32 i = 0; i < count; ++i) {
            res::Handle* handle = &reader->mHandles[i];
            const char* entry_name = _15e8->getEntryName(iter, i);
            sub_710105844C(handle, entry_name, flag, false);
        }
    }
    reader->_18 |= 1;
}

// NON_MATCHING: every local sits 0x10 higher than the original's (the request, the path string and the reused
// status / requester temporary); the instructions are otherwise the same.
// 0x7101058f20 (placeholder name): loads "<dir>/<name>.bars" into `handle` and returns it as a bars resource.
ResourceBars* ResourceManager::sub_7101058F20(res::Handle* handle, const sead::SafeString& name,
                                               const sead::SafeString& dir, bool use_audio_arena,
                                               bool lane2) {
    sead::FixedSafeString<128> path;
    path.format("%s/%s.bars", dir.cstr(), name.cstr());
    res::Handle::Status status;
    res::LoadRequest request;
    request.mRequester = "Sound";
    request.mLoadDataAlignment = 0x80;
    request._22 = true;
    request.mArena = use_audio_arena ? OverlayArenaSystem::instance()->getAudioArena() : mArena;
    if (lane2)
        request.mLaneId = 2;
    auto* resource = handle->load(path, &request, &status);
    auto* bars = sead::DynamicCast<ResourceBars>(resource);
    if (bars && status == res::Handle::Status::_4)
        bars->sub_7101057588(name);
    return bars;
}

// 0x7101059120 (placeholder name): loads `name` into `handle` with `pack` as the pack handle, then sets the
// bars file name when the result is a loaded ResourceBars.
void ResourceManager::sub_7101059120(res::Handle* handle, res::Handle* pack, const sead::SafeString& name) {
    res::LoadRequest request;
    request.mRequester = "Sound";
    request.mLoadDataAlignment = 0x80;
    request.mPackHandle = pack;
    request.mArena = mArena;
    request._26 = false;
    res::Handle::Status status;
    auto* resource = handle->load(name, &request, &status);
    auto* bars = sead::DynamicCast<ResourceBars>(resource);
    if (bars && status == res::Handle::Status::_4)
        bars->sub_7101057588(name);
}

// 0x7101058c44: loads every entry of the bars list `name` into `reader`, requesting each asset.
bool ResourceManager::loadBars(const sead::SafeString& name, Unk_7102502950* reader, sead::Heap* heap,
                              bool a4, bool a5, res::Handle* pack) {
    if (!reader)
        return false;
    al::ByamlIter iter = _15e8->getIter(name);
    reader->_18 = 0;
    if (!iter.isValid()) {
        reader->_18 |= 2;
        return false;
    }
    const s32 count = _15e8->getSize(iter);
    if (count <= 0) {
        reader->_18 |= 1;
        return true;
    }
    reader->sub_71010571A4(count, heap);
    for (s32 i = 0; i < count; ++i) {
        res::Handle* handle = &reader->mHandles[i];
        const char* entry_name = _15e8->getEntryName(iter, i);
        requestLoadBars(handle, entry_name, a4, a5, 0, pack);
    }
    return true;
}

// NON_MATCHING: the requester temporary uses a different stack slot.
bool ResourceManager::requestLoadBars(res::Handle* handle, const sead::SafeString& name,
                                    bool use_audio_arena, bool lane2, u32 buffer_size,
                                    res::Handle* pack) {
    sead::FixedSafeString<128> path;
    path.format("%s%s", sResourceDirectory.cstr(), name.cstr());
    res::LoadRequest request;
    request.mRequester = "Sound";
    request.mLoadDataAlignment = 0x80;
    request._22 = true;
    request.mBufferSize = buffer_size;
    request.mArena = use_audio_arena ? OverlayArenaSystem::instance()->getAudioArena() : mArena;
    if (buffer_size != 0)
        request._27 = false;
    if (lane2)
        request.mLaneId = 2;
    if (pack)
        request.mPackHandle = pack;
    return handle->requestLoad(path, &request, nullptr);
}

sead::DirectResource* ResourceManager::tryLoadResource(const sead::SafeString& path, sead::Heap* heap,
                                                      s32 alignment) {
    sead::DirectResource* resource = nullptr;
    loadDirectResource(&resource, path, heap, alignment);
    return resource;
}

// NON_MATCHING: the heap and alignment registers are swapped (x20 / x21).
bool ResourceManager::loadDirectResource(sead::DirectResource** out, const sead::SafeString& path,
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

sead::DirectResource* Unk_7102502b50::newResource_(sead::Heap* heap_, s32 alignment) {
    sead::Heap* heap = ksys::util::getHeapOrCurrentHeap(heap_);
    sead::ScopedCurrentHeapSetter setter{heap};
    return new (heap, alignment, std::nothrow_t{}) ResourceBars;
}
