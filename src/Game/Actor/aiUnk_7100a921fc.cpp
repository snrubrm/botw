#include <random/seadGlobalRandom.h>
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
