#pragma once

#include <filedevice/seadArchiveFileDevice.h>
#include <filedevice/seadFileDevice.h>
#include <resource/seadSharcArchiveRes.h>

namespace sead {
class Heap;
}

namespace eui {

// A SARC archive loaded through the sead resource manager (the layouts' resources: ArcResourceMgr, MessageMgr::Archive).
class SharcArchive {
public:
    // Iterates over the root directory of the archive (an ArchiveFileDevice for it).
    class FileReader : public sead::ArchiveFileDevice {
    public:
        FileReader() : ArchiveFileDevice(nullptr) {}
        ~FileReader() override;

        // 0x7100beccec: reads the next directory entry into `mEntry` (false at the end)
        bool readNext();

        void setArchive(sead::ArchiveRes* archive) { mArchive = archive; }

        s32 mIndex = -1;
        sead::DirectoryHandle mDirectory;
        sead::DirectoryEntry mEntry;
    };

    // 0x7100beca2c / 0x7100beca34
    SharcArchive();
    ~SharcArchive();


    // 0x7100becaa4
    void initialize(sead::Heap* heap, void* data, u32 size);
    // 0x7100beca6c: unloads the archive resource (the destructor does the same)
    void unload();
    // inline-only in the original; name is a guess (MessageMgr::getMessageSet calls a virtual of the resource directly)
    sead::SharcArchiveRes* getResource() const { return mArchive; }
    // 0x7100becc34
    void startFileReader(FileReader* reader) const;

private:
    sead::SharcArchiveRes* mArchive;
};

}  // namespace eui
