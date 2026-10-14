#include "KingSystem/Sound/sndBgmMgr.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicInfo.h"

namespace ksys::snd {

Unk_71010073f4::Unk_71010073f4() {
    mList.initOffset(0x190);
}

Unk_71010073f4::~Unk_71010073f4() = default;

}  // namespace ksys::snd

// NON_MATCHING: placeholder destructor; the original (0x710100ac6c) also destroys members or bases
// this class does not declare yet.
Unk_71024fe368::~Unk_71024fe368() = default;

// NON_MATCHING: placeholder destructor; the original (0x710100d2f4) also destroys members or bases
// this class does not declare yet.
Unk_71024fe808::~Unk_71024fe808() = default;

// NON_MATCHING: placeholder destructor; the original (0x710100df48) also destroys members or bases
// this class does not declare yet.
Unk_71024fe970::~Unk_71024fe970() = default;

// NON_MATCHING: placeholder destructor; the original (0x710100f3f4) also destroys members or bases
// this class does not declare yet.
Unk_71024feae8::~Unk_71024feae8() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101010340) also destroys members or bases
// this class does not declare yet.
Unk_71024fec18::~Unk_71024fec18() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101010d68) also destroys members or bases
// this class does not declare yet.
Unk_71024fed48::~Unk_71024fed48() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101011694) also destroys members or bases
// this class does not declare yet.
Unk_71024fee78::~Unk_71024fee78() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101011d4c) also destroys members or bases
// this class does not declare yet.
Unk_71024fefe8::~Unk_71024fefe8() = default;

Unk_71024ff268::~Unk_71024ff268() = default;

namespace ksys::snd {

Unk_710260f278::Unk_710260f278(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    _1c0.setCurveType(aal::FadeCurveType::Square);
    auto* heap = arg.heap;
    mInfo = static_cast<HorseBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_1));
    Unk_SpotBgmHandle::init(heap, "HorseBgm", nullptr);
}

}  // namespace ksys::snd
