#include "Game/AI/Action/actionSpotBgmTriggerAction.h"
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndMusicDefinition.h"

namespace ksys::snd {

namespace {
const char* sLessonNames[] = {"Lesson1", "Lesson2", "Lesson3", "Lesson4"};
}  // namespace

Unk_710260f228::Unk_710260f228(const BgmInitArg& arg) : Unk_71025ce380(arg) {
    Unk_SpotBgmHandle::init(arg.heap, "DungeonTutorialBgm", nullptr);
    mInfo = static_cast<TutorialDungeonBattleBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::_23));
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

// NON_MATCHING: placeholder destructor; the original (0x7101021db8) also destroys members or bases
// this class does not declare yet.
Unk_7102500a00::~Unk_7102500a00() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101025acc) also destroys members or bases
// this class does not declare yet.
Unk_7102500e08::~Unk_7102500e08() = default;
