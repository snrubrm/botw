#include <random/seadGlobalRandom.h>
#include <prim/seadStringUtil.h>
#include "Game/Actor/aiUnk_71023f18e8.h"
#include "Game/gameUnkRttiPlaceholders.h"

Unk_7100a921fc::Unk_7100a921fc() = default;

void Unk_7100a921fc::sub_7100A92208(s32 count) {
    _8 = count;
    _0 = _4 = sead::GlobalRandom::instance()->getU32(count);
}

// NON_MATCHING: the original computes `count - 1` before the modulo (kept in a callee-saved register);
// `const s32 last = count - 1;` as a local would match (borderline, not applied)
bool Unk_7100a921fc::sub_7100A92248() {
    const s32 start = _0;
    const s32 prev = _4;
    const s32 count = _8;
    _4 = (prev + 1) % count;
    if (_4 == start)
        _0 = _4 = sead::GlobalRandom::instance()->getU32(count);
    return prev == count - 1;
}

Unk_710251d160::~Unk_710251d160() = default;

Unk_710249d608::~Unk_710249d608() = default;

// 0x7100a926b4
const void* Unk_710249d608::getFileImpl_(const sead::SafeString& file_path,
                                         sead::ArchiveRes::FileInfo* file_info) SEAD_ARCHIVERES_CONST_TOKEN {
    s32 id = convertPathToEntryIDImpl_(file_path);
    if (id < 0)
        return nullptr;
    return getFileFastImpl_(id, file_info);
}

// 0x7100a93b20
bool Unk_710249d608::setCurrentDirectoryImpl_(const sead::SafeString&) {
    return false;
}

Unk_710251d0e0::~Unk_710251d0e0() = default;

// NON_MATCHING: placeholder destructor; the original (0x71012e906c) also destroys members or bases
// this class does not declare yet.
Unk_710251d010::~Unk_710251d010() = default;

Unk_710251cfa0::~Unk_710251cfa0() = default;

namespace {

// POSIX USTAR header, followed by file data padded to a 512-byte boundary.
struct TarHeader {
    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char checksum[8];
    char type;
    char link_name[100];
    char magic[6];
    char version[2];
    char user_name[32];
    char group_name[32];
    char device_major[8];
    char device_minor[8];
    char prefix[155];
    char padding[12];
};
static_assert(sizeof(TarHeader) == 512);

}  // namespace

// NON_MATCHING: the end-marker scan uses bytes rather than word pairs; stack layout and branch merging differ.
// 0x7100a9238c
bool Unk_710249d608::sub_7100A9238C(Entry* entry, const void* data, s32 remaining) const {
    const auto fail = [this](u32 error) {
        mError = error;
        return false;
    };
    if (remaining < 512 || (remaining & 511) != 0)
        return fail(1);
    const auto* bytes = static_cast<const u8*>(data);
    if (remaining >= 1024) {
        s32 i = 0;
        while (i < 1024 && bytes[i] == 0)
            ++i;
        if (i == 1024) {
            entry->kind = Entry::Kind::End;
            return true;
        }
    }
    const auto* header = static_cast<const TarHeader*>(data);
    if (header->name[99] != '\0')
        return fail(2);
    if (header->mode[7] != '\0')
        return fail(3);
    u32 mode;
    if (!sead::StringUtil::tryParseU32(&mode, header->mode, sead::StringUtil::CardinalNumber::Base8))
        return fail(4);
    if (header->uid[7] != '\0' || header->gid[7] != '\0' || header->size[11] != '\0')
        return fail(3);
    u32 size;
    if (!sead::StringUtil::tryParseU32(&size, header->size, sead::StringUtil::CardinalNumber::Base8))
        return fail(4);
    if (header->mtime[11] != '\0' || header->checksum[7] != '\0')
        return fail(3);
    u32 checksum;
    if (!sead::StringUtil::tryParseU32(&checksum, header->checksum, sead::StringUtil::CardinalNumber::Base8))
        return fail(4);
    if (header->link_name[0] != '\0')
        return fail(5);
    if (sead::SafeString(header->magic) != "ustar")
        return fail(6);
    if (header->version[0] != '0' || header->version[1] != '0')
        return fail(7);
    if (header->prefix[0] != '\0')
        return fail(8);
    u32 sum = 0;
    for (s32 i = 0; i < 512; ++i)
        sum += i >= 148 && i < 156 ? 32 : bytes[i];
    if (checksum != sum)
        return fail(9);
    if ((mode & 0xc000) == 0x4000) {
        if (header->type != '5')
            return fail(12);
        if (size != 0)
            return fail(13);
        entry->name = header->name;
        entry->kind = Entry::Kind::Directory;
        entry->size = 0;
        entry->next_header = bytes + 512;
        return true;
    }
    if ((mode & 0xc000) == 0x8000) {
        if (header->type != '\0' && header->type != '0')
            return fail(10);
        const s32 step = (size + 1023) & ~511u;
        if (step >= remaining)
            return fail(11);
        entry->name = header->name;
        entry->kind = Entry::Kind::File;
        entry->size = size;
        entry->next_header = bytes + step;
        return true;
    }
    return fail(14);
}

// NON_MATCHING: remaining-size tests are if-converted and the end-marker return shares a different tail.
// 0x7100a922b8
bool Unk_710249d608::prepareArchive_(const void*) {
    const s32 size = mRawSize;
    if (size < 1)
        return false;
    const u8* const archive = mRawData;
    const u8* header = archive;
    do {
        Entry entry;
        const auto offset = header - archive;
        s32 remaining = size;
        if (offset >= 0)
            remaining = offset > size ? 0 : size - offset;
        if (!sub_7100A9238C(&entry, header, remaining))
            return false;
        if (entry.kind == Entry::Kind::End)
            return true;
        if (entry.next_header <= header)
            return false;
        header = entry.next_header;
    } while (true);
}

// NON_MATCHING: output offset/length stores are separate and the return tail is laid out differently.
// 0x7100a9270c
const void* Unk_710249d608::getFileFastImpl_(s32 entry_id, sead::ArchiveRes::FileInfo* info)
    SEAD_ARCHIVERES_CONST_TOKEN {
    const s32 size = mRawSize;
    if (size < 1 || u32(entry_id) >= u32(size) >> 9)
        return nullptr;
    const u8* const archive = mRawData;
    const s32 header_offset = entry_id * 512;
    const u8* header = archive + header_offset;
    if (!header)
        return nullptr;
    s32 remaining = size;
    if (header_offset >= 0)
        remaining = header_offset > size ? 0 : size - header_offset;
    Entry entry;
    if (!sub_7100A9238C(&entry, header, remaining))
        return nullptr;
    const u8* data = header + 512;
    const auto offset = data - archive;
    if (offset < 0 || s32(offset) != offset)
        return nullptr;
    if (info) {
        info->mStartOffset = offset;
        info->mLength = entry.size;
    }
    return data;
}

// NON_MATCHING: remaining-size checks and SafeString comparison schedule differently.
// 0x7100a927c4
s32 Unk_710249d608::convertPathToEntryIDImpl_(const sead::SafeString& file_path)
    SEAD_ARCHIVERES_CONST_TOKEN {
    const s32 size = mRawSize;
    if (size < 1)
        return -1;
    const u8* const archive = mRawData;
    const u8* header = archive;
    do {
        const auto offset = header - archive;
        s32 remaining = size;
        if (offset >= 0)
            remaining = offset > size ? 0 : size - offset;
        Entry entry;
        if (!sub_7100A9238C(&entry, header, remaining))
            return -1;
        if (entry.kind == Entry::Kind::End || entry.next_header <= header)
            return -1;
        header = entry.next_header;
        if (entry.kind == Entry::Kind::File && entry.name == file_path) {
            if (offset < 0 || s32(offset) != offset || (offset & 511) != 0)
                return -1;
            return s32(offset) / 512;
        }
    } while (true);
}

s32 Unk_710251cfa0::m8() {
    return _34 * 4;
}

s32 Unk_710251cfa0::m9() {
    return _38 * 4;
}

s32 Unk_710251cfa0::m10() {
    return _30;
}

s32 Unk_710251cfa0::m11() {
    return _30;
}

s32 Unk_710251d160::m8() {
    return (_30 + 1) * (_34 + 1);
}

s32 Unk_710251d160::m10() {
    return _30;
}

s32 Unk_710251d160::m11() {
    return _34;
}

s32 Unk_710251d0e0::m8() {
    return (m10() + 1) * (m11() + 1);
}

s32 Unk_710251d010::m8() {
    const u32 cols = m10() + 1;
    const u32 rows = m11() + 1;
    return cols * rows + (cols - 1) * (rows - 1);
}
