#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/Actor/Action/actionSpotBgmTriggerAction.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndMusicDefinition.h"

namespace ksys::snd {


namespace {
const char* sLessonNames[] = {"Lesson1", "Lesson2", "Lesson3", "Lesson4"};
}  // namespace

Unk_710260f228::Unk_710260f228(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, "DungeonTutorialBgm", nullptr);
    mInfo = static_cast<TutorialDungeonBattleBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::TutorialDungeonBattleBgm));
}

bool Unk_710260f228::m10() {
    return mState != 0;
}

void Unk_710260f228::sub_71010267A8(const Unk_71010267A8& state) {
    if (state.value != 0) {
        mState = 2;
        mTimer = 0;
        mLesson = state;
        return;
    }
    if (mEntry && mEntry->sub_7100FF6DF4(this))
        mEntry->sub_7100FF6A64(0.1);
    mEntry = sub_71010209FC(sLessonNames[state.value]);
    if (mEntry && mEntry->sub_7100FF6DF4(this))
        sub_710101D9D8();
    mState = 1;
    mLesson = state;
    m8(true);
}

void Unk_710260f228::sub_7101026888() {
    mState = 3;
    mTimer = 0;
}

void Unk_710260f228::hm14() {
    if (mState != 1)
        return;
    sub_710101D9D8();
    sub_71010267A8(mLesson);
}

void Unk_710260f228::hm15() {
    switch (mState) {
    case 4:
        if (mEntries.size() == 0) {
            sub_710101D9F4(0.1);
            mState = 0;
        }
        break;
    case 3:
        mTimer += sub_710105E3A4();
        if (mTimer > *mInfo->mOutroDelaySec) {
            mTimer = *mInfo->mOutroDelaySec;
            if (mEntry && mEntry->sub_7100FF6DF4(this))
                mEntry->sub_7100FF6A64(0.1);
            mEntry = sub_71010209FC("Outro");
            if (mEntry && mEntry->sub_7100FF6DF4(this))
                mState = 4;
        }
        break;
    case 2:
        mTimer += sub_710105E3A4();
        if (mTimer > *mInfo->mTransitionDelaySec) {
            mTimer = *mInfo->mTransitionDelaySec;
            if (mEntry && mEntry->sub_7100FF6DF4(this))
                mEntry->sub_7100FF6A64(0.1);
            mEntry = sub_71010209FC(sLessonNames[mLesson.value]);
            if (mEntry && mEntry->sub_7100FF6DF4(this))
                mState = 1;
        }
        break;
    default:
        break;
    }
}

void Unk_710260f228::m12(f32 fade_sec) {
    if (mState == 1)
        sub_710101D9D8();
}

void Unk_710260f228::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    if (mState == 3 || mState == 4)
        mState = 0;
}

}  // namespace ksys::snd

void Unk_SpotBgmInstance::sub_710102413C(f32 fade_sec) {
    if (_368 & 1)
        return;
    _8.sub_7101020BB0(fade_sec);
    if (_368 & 4)
        _368 |= 8;
    else
        _260 = 0;
    _368 |= 0x4001;
}

void Unk_SpotBgmInstance::sub_710102418C(f32 fade_sec) {
    if (!(_368 & 1))
        return;
    if (_368 & 2)
        _8.sub_710101D9F4(fade_sec);
    _368 &= ~0x10023u;
}

void Unk_SpotBgmInstance::sub_71010242C8() {
    if (!(_368 & 4))
        return;
    const f32 value = (_368 & 0x8000) ? 1.0f : 0.0f;
    _368 &= ~0xcu;
    _260 = value;
}

void Unk_SpotBgmInstance::sub_71010242F0() {
    _308 = 1;
    _368 |= 0x200;
    _310.setValueImmediate(0.0f);
}

Unk_71025008d0::~Unk_71025008d0() = default;

Unk_7102500a00::~Unk_7102500a00() {
    mFaders.freeBuffer();
    if (mPartNames.isBufferReady()) {
        for (s32 i = 0; i < mPartNames.size(); ++i) {
            delete mPartNames[i];
            mPartNames[i] = nullptr;
        }
        mPartNames.freeBuffer();
    }
}

namespace {
// 0x7102500b30: the part names for _1a0 != 1 (_1a0 == 1 plays mPartNames[_1a4]).
const char* const sUnk_7102500B30[] = {"A", "B", "Z"};
}  // namespace

// NON_MATCHING: the address of _20c is computed once for both flag branches here (as Unk_71024fe970::hm14).
void Unk_7102500a00::hm14() {
    if (mType == ksys::snd::Unk_710260f248Type::_3 || (_68._18 & 3))
        _20c &= ~8;
    else
        _20c |= 8;
    if (_20c & 8)
        return;
    if (_1a0 == 1)
        _1b8 = sub_71010209FC(*mPartNames[_1a4]);
    else
        _1b8 = sub_71010209FC(sUnk_7102500B30[_1a0]);
    _20c &= ~4;
    _1e0.setValueImmediate(1.0f);
}

Unk_7102500e08::~Unk_7102500e08() {
    if (_18) {
        _18->sub_710101D9A4();
        delete _18;
    }
    if (_20) {
        _20->sub_710101D9A4();
        delete _20;
    }
    if (_28) {
        _28->sub_710101D9A4();
        delete _28;
    }
}
