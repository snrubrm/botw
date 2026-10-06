#include "Game/gameRIDDemoSaveFileDevice.h"

RIDDemoSaveFileDevice::RIDDemoSaveFileDevice(const sead::SafeString& name, sead::FileDevice* device,
                                             const sead::SafeString& path)
    : FileDevice(name), mDevice(device) {
    if (device)
        mPath.copy(path);
}

// The original keeps this class's vtable store before calling sead::FileDevice::~FileDevice(), which a defaulted
// destructor drops; written like upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; } (commit 96101229).
RIDDemoSaveFileDevice::~RIDDemoSaveFileDevice() { ; }

void RIDDemoSaveFileDevice::traceFilePath(const sead::SafeString& path) const {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    mDevice->traceFilePath(full_path);
}

void RIDDemoSaveFileDevice::traceDirectoryPath(const sead::SafeString& path) const {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    mDevice->traceDirectoryPath(full_path);
}

void RIDDemoSaveFileDevice::resolveFilePath(sead::BufferedSafeString* out,
                                            const sead::SafeString& path) const {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    mDevice->resolveFilePath(out, full_path);
}

void RIDDemoSaveFileDevice::resolveDirectoryPath(sead::BufferedSafeString* out,
                                                 const sead::SafeString& path) const {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    mDevice->resolveDirectoryPath(out, full_path);
}

bool RIDDemoSaveFileDevice::isMatchDevice_(const sead::HandleBase* handle) const {
    return mDevice->isMatchDevice_(handle);
}

bool RIDDemoSaveFileDevice::doIsAvailable_() const {
    return mDevice->isAvailable();
}

sead::FileDevice* RIDDemoSaveFileDevice::doOpen_(sead::FileHandle* handle,
                                                 const sead::SafeString& path, FileOpenFlag flag) {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    return mDevice->tryOpen(handle, full_path, flag, handle->getDivSize());
}

bool RIDDemoSaveFileDevice::doClose_(sead::FileHandle* handle) {
    return mDevice->tryClose(handle);
}

bool RIDDemoSaveFileDevice::doFlush_(sead::FileHandle* handle) {
    return mDevice->tryFlush(handle);
}

bool RIDDemoSaveFileDevice::doRemove_(const sead::SafeString& path) {
    return mDevice->tryRemove(path);
}

bool RIDDemoSaveFileDevice::doRead_(u32* bytes_read, sead::FileHandle* handle, u8* buffer,
                                    u32 size) {
    return mDevice->tryRead(bytes_read, handle, buffer, size);
}

bool RIDDemoSaveFileDevice::doWrite_(u32* bytes_written, sead::FileHandle* handle,
                                     const u8* buffer, u32 size) {
    return mDevice->tryWrite(bytes_written, handle, buffer, size);
}

bool RIDDemoSaveFileDevice::doSeek_(sead::FileHandle* handle, s32 offset, SeekOrigin origin) {
    return mDevice->trySeek(handle, offset, origin);
}

bool RIDDemoSaveFileDevice::doGetCurrentSeekPos_(u32* seek_pos, sead::FileHandle* handle) {
    return mDevice->tryGetCurrentSeekPos(seek_pos, handle);
}

bool RIDDemoSaveFileDevice::doGetFileSize_(u32* file_size, const sead::SafeString& path) {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    return mDevice->tryGetFileSize(file_size, full_path);
}

bool RIDDemoSaveFileDevice::doGetFileSize_(u32* file_size, sead::FileHandle* handle) {
    return mDevice->tryGetFileSize(file_size, handle);
}

bool RIDDemoSaveFileDevice::doIsExistFile_(bool* exists, const sead::SafeString& path) {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    return mDevice->tryIsExistFile(exists, full_path);
}

bool RIDDemoSaveFileDevice::doIsExistDirectory_(bool* exists, const sead::SafeString& path) {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    return mDevice->tryIsExistDirectory(exists, full_path);
}

sead::FileDevice* RIDDemoSaveFileDevice::doOpenDirectory_(sead::DirectoryHandle* handle,
                                                          const sead::SafeString& path) {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    return mDevice->tryOpenDirectory(handle, full_path);
}

bool RIDDemoSaveFileDevice::doCloseDirectory_(sead::DirectoryHandle* handle) {
    return mDevice->tryCloseDirectory(handle);
}

bool RIDDemoSaveFileDevice::doReadDirectory_(u32* entries_read, sead::DirectoryHandle* handle,
                                             sead::DirectoryEntry* entries, u32 num_entries) {
    return mDevice->tryReadDirectory(entries_read, handle, entries, num_entries);
}

bool RIDDemoSaveFileDevice::doMakeDirectory_(const sead::SafeString& path, u32 mode) {
    sead::FixedSafeString<512> full_path;
    full_path.copy(mPath);
    full_path.append(path);
    return mDevice->tryMakeDirectory(full_path, mode);
}

s32 RIDDemoSaveFileDevice::doGetLastRawError_() const {
    return mDevice->getLastRawError();
}
