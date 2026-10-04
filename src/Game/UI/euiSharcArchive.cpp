#include "Game/UI/euiSharcArchive.h"
#include <resource/seadResourceMgr.h>

namespace eui {

// 0x7100beca2c
SharcArchive::SharcArchive() : mArchive(nullptr) {}

// 0x7100beca34
SharcArchive::~SharcArchive() {
    unload();
}

// 0x7100beca6c
void SharcArchive::unload() {
    if (mArchive) {
        sead::ResourceMgr::instance()->unload(mArchive);
        mArchive = nullptr;
    }
}

// 0x7100becaa4
void SharcArchive::initialize(sead::Heap* heap, void* data, u32 size) {
    sead::ResourceMgr::CreateArg arg;
    sead::DirectResourceFactory<sead::SharcArchiveRes> factory;

    arg.buffer = static_cast<u8*>(data);
    arg.file_size = size;
    arg.buffer_size = size;
    arg.factory = &factory;
    arg.heap = heap;
    mArchive = sead::DynamicCast<sead::SharcArchiveRes>(sead::ResourceMgr::instance()->create(arg));
}

// 0x7100becc34
void SharcArchive::startFileReader(FileReader* reader) const {
    reader->mIndex = -1;
    reader->setArchive(mArchive);
    reader->tryOpenDirectory(&reader->mDirectory, "");
}

// NON_MATCHING: the original does not store FileReader's (nor ArchiveFileDevice's) vtable pointer: everything else is
// identical (close the directory, DirectoryHandle's inlined destructor, tail call to ~FileDevice).
// 0x7100becc8c
SharcArchive::FileReader::~FileReader() {
    if (mArchive)
        tryCloseDirectory(&mDirectory);
}

// 0x7100beccec
bool SharcArchive::FileReader::readNext() {
    u32 count = 0;
    tryReadDirectory(&count, &mDirectory, &mEntry, 1);
    if (count != 1)
        return false;
    ++mIndex;
    return true;
}

}  // namespace eui
