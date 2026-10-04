#include "Game/UI/euiArcResourceMgr.h"
#include <filedevice/seadFileDeviceMgr.h>

namespace eui {

// 0x7101407a14
ArcResourceMgr::ArcResourceMgr() {
    mArchives.initOffset(offsetof(ArcResource, mNode));
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
