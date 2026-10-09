#include "Game/UI/euiArcResourceMgr.h"
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <new>
#include <gfx/nin/seadGraphicsNvn.h>
#include <nn/gfx/gfx_ResTexture.h>

namespace eui {

// 0x71014085d0
sead::DirectResource* ArcResourceMgr::OneTimeBinaryResourceFactory::newResource_(sead::Heap*, s32) {
    mUsed = true;
    return new (mStorage) sead::DirectResource;
}

// 0x7101407a14
ArcResourceMgr::ArcResourceMgr() {
    mArchives.initOffset(offsetof(ArcResource, mNode));
}

// 0x7101407a38 / 0x7101407a3c
ArcResourceMgr::~ArcResourceMgr() = default;

// 0x7101407bf0
void ArcResourceMgr::loadArchive(sead::Heap* heap, const sead::SafeString& path) {
    sead::ResourceMgr::LoadArg arg;
    OneTimeBinaryResourceFactory factory;
    bool tried_decompression = false;
    arg.path = path;
    arg.instance_heap = heap;
    arg.load_data_heap = heap;
    arg.instance_alignment = 4;
    arg.load_data_alignment = 0x1000;
    arg.factory = &factory;
    arg.has_tried_create_with_decomp = &tried_decompression;
    auto* resource = sead::DynamicCast<sead::DirectResource>(
        sead::ResourceMgr::instance()->tryLoad(arg, "", nullptr));
    if (resource) {
        sead::FixedSafeString<64> name;
        sead::Path::getBaseFileName(&name, path);
        auto* archive = new (heap, 8) ArcResource(this, name, resource->getRawData());
        mArchives.pushBack(archive);
    }
}

ArcResourceMgr::ArcResource::~ArcResource() {
    if (mTextureResource) {
        auto& texture = mTextureResource->ToData().textureContainerData;
        if (texture.pCurrentMemoryPool.Get() == texture.pTextureMemoryPool.Get())
            texture.pCurrentMemoryPool.Get()->Finalize(sead::GraphicsNvn::instance()->getNnDevice());
        texture.pCurrentMemoryPool.Set(nullptr);
    }
    if (mData)
        finalizeInitializedShaderResource(mData);
    mMgr->eraseArchiveFromList(this);
}

// 0x7101407a40
void ArcResourceMgr::loadArchivesInDirectory(sead::Heap* heap, const sead::SafeString& path) {
    sead::FixedSafeString<256> path_no_drive;
    sead::FileDevice* device = sead::FileDeviceMgr::instance()->findDeviceFromPath(path, &path_no_drive);
    sead::DirectoryHandle handle;
    if (device->tryOpenDirectory(&handle, path_no_drive)) {
        sead::DirectoryEntry entry;
        while (handle.read(&entry, 1)) {
            if (!entry.is_directory)
                loadArchive(heap, sead::FormatFixedSafeString<256>("%s/%s", path_no_drive.cstr(),
                                                                 entry.name.cstr()));
        }
    }
}

// 0x7101407e4c
u8* ArcResourceMgr::findArchiveData(const sead::SafeString& name) const {
    for (const auto& archive : mArchives) {
        if (archive.mName == name)
            return archive.mData;
    }
    return nullptr;
}

// 0x7101407f78
ArcResourceMgr::ArcResource* ArcResourceMgr::findArcResource(const sead::SafeString& name) const {
    for (auto& archive : mArchives) {
        if (archive.mName == name)
            return &archive;
    }
    return nullptr;
}

// 0x71014080a0
void ArcResourceMgr::unloadAllArchives() {
    for (auto& archive : mArchives.robustRange()) {
        u8* data = archive.mData;
        delete &archive;
        sead::FileDeviceMgr::instance()->unload(data);
    }
}

// 0x7101408120
void ArcResourceMgr::addArchiveToList(ArcResource* archive) {
    mArchives.pushBack(archive);
}

// 0x7101408158
void ArcResourceMgr::eraseArchiveFromList(ArcResource* archive) {
    mArchives.erase(archive);
}

}  // namespace eui
