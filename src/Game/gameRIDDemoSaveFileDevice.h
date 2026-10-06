#pragma once

#include <filedevice/seadFileDevice.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

// A file device that forwards every operation to another device after prefixing the path with `mPath`
// (the save device of the RID demo build). Global namespace; the name comes from the CSV / RTTI.
class RIDDemoSaveFileDevice : public sead::FileDevice {
    SEAD_RTTI_OVERRIDE(RIDDemoSaveFileDevice, sead::FileDevice)
public:
    RIDDemoSaveFileDevice(const sead::SafeString& name, sead::FileDevice* device,
                          const sead::SafeString& path);
    ~RIDDemoSaveFileDevice() override;

    void traceFilePath(const sead::SafeString& path) const override;
    void traceDirectoryPath(const sead::SafeString& path) const override;
    void resolveFilePath(sead::BufferedSafeString* out, const sead::SafeString& path) const override;
    void resolveDirectoryPath(sead::BufferedSafeString* out,
                              const sead::SafeString& path) const override;
    bool isMatchDevice_(const sead::HandleBase* handle) const override;

protected:
    bool doIsAvailable_() const override;
    FileDevice* doOpen_(sead::FileHandle* handle, const sead::SafeString& path,
                        FileOpenFlag flag) override;
    bool doClose_(sead::FileHandle* handle) override;
    bool doFlush_(sead::FileHandle* handle) override;
    bool doRemove_(const sead::SafeString& path) override;
    bool doRead_(u32* bytes_read, sead::FileHandle* handle, u8* buffer, u32 size) override;
    bool doWrite_(u32* bytes_written, sead::FileHandle* handle, const u8* buffer,
                  u32 size) override;
    bool doSeek_(sead::FileHandle* handle, s32 offset, SeekOrigin origin) override;
    bool doGetCurrentSeekPos_(u32* seek_pos, sead::FileHandle* handle) override;
    bool doGetFileSize_(u32* file_size, const sead::SafeString& path) override;
    bool doGetFileSize_(u32* file_size, sead::FileHandle* handle) override;
    bool doIsExistFile_(bool* exists, const sead::SafeString& path) override;
    bool doIsExistDirectory_(bool* exists, const sead::SafeString& path) override;
    FileDevice* doOpenDirectory_(sead::DirectoryHandle* handle,
                                 const sead::SafeString& path) override;
    bool doCloseDirectory_(sead::DirectoryHandle* handle) override;
    bool doReadDirectory_(u32* entries_read, sead::DirectoryHandle* handle,
                          sead::DirectoryEntry* entries, u32 num_entries) override;
    bool doMakeDirectory_(const sead::SafeString& path, u32 mode) override;
    s32 doGetLastRawError_() const override;

private:
    sead::FileDevice* mDevice;
    sead::FixedSafeString<256> mPath;
};
KSYS_CHECK_SIZE_NX150(RIDDemoSaveFileDevice, 0x1a0);
