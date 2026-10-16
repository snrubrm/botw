#include "KingSystem/Sound/sndBgmMgr.h"
#include <resource/seadResource.h>
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Sound/sndSound.h"

namespace ksys::snd {

// The TU after sndResourceManager.cpp's static initialiser (0x7101057c4c onwards: the SoundMgr::_60 resource
// manager).

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
