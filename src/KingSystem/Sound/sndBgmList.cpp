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

namespace {
sead::SafeString sStr_MazeForestBgm = "MazeForestBgm";
sead::SafeString sStr_MazeForestBgmMain = "main";
}  // namespace

Unk_710260f288::Unk_710260f288(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, sStr_MazeForestBgm, nullptr);
    mInfo = static_cast<MazeForestBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_4));
}

void Unk_710260f288::m13(f32 fade_sec) {
    sub_710101DA34();
    sub_7101020C08(fade_sec);
    mFader.setValueImmediate(0.0);
    mState = 0;
}

void Unk_710260f288::hm14() {
    if (mEntries.size() != 0)
        return;
    sub_71010209FC(sStr_MazeForestBgmMain);
}

}  // namespace ksys::snd
