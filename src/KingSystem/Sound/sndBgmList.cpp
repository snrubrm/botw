#include "KingSystem/Sound/sndBgmMgr.h"
#include <random/seadGlobalRandom.h>
#include <xlink2/xlink2EnumPropertyDefinition.h>
#include "KingSystem/Sound/sndEnvBgm.h"
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <xlink2/xlink2Event.h>
#include <xlink2/xlink2ResourceAccessorSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::snd {

Unk_710260f848::Unk_710260f848(const BgmInitArg& arg) : Unk_71025ce3a0(arg.handle_type, 3) {
    Unk_SpotBgmHandle::init(arg.heap, "RemainsWaterBattleBgm", nullptr);
}

// NON_MATCHING: the original loads the asset call table before calling getResourceAccessor (C++14 argument order).
void Unk_71025ce3a0::hm14() {
    auto* entry = sub_7101020B40();
    _189 = false;
    if (entry && entry->sub_7100FF6DF4(this) && entry->mHandle.isActive()) {
        _189 = mUserInstance->getResourceAccessor().isNeedObserve(
            *entry->mHandle.getEvent()->getAssetCallTable());
    }
}

void Unk_71025ce3a0::hm15() {
    if (mEntries.size() == 0 && mStarted) {
        sub_710101D9F4(0.0f);
        m6(false);
        mStarted = false;
    }
}

Unk_710260f848::~Unk_710260f848() = default;

Unk_710260f2b8::Unk_710260f2b8(const BgmInitArg& arg) : Unk_71025ce3a0(arg.handle_type, 0) {
    Unk_SpotBgmHandle::init(arg.heap, "RemainsWindBattleBgm", nullptr);
}

namespace {
struct RemainsWindBgmParams {
    f32 jump_fade_out_sec;
    f32 jump_fade_in_sec;
    sead::SafeString intro;
    sead::SafeString main;
};
}  // namespace

// 0x71024fe240
static const RemainsWindBgmParams sRemainsWindParams = {0.5, 0.5, "Intro", "Main"};

void Unk_710260f2b8::fadeInMaybe(f32 fade_sec) {
    sub_7101020BB0(fade_sec);
    sub_710101D9D8();
}

void Unk_710260f2b8::sub_7101009040() {
    if (mJumped)
        return;
    if (mEntry && mEntry->sub_7100FF6DF4(this))
        mEntry->sub_7100FF6A64(sRemainsWindParams.jump_fade_out_sec);
    mEntry = sub_71010209FC(sRemainsWindParams.main);
    mFader.setValueImmediate(0.0f);
    mFader.moveTo(1.0f, sRemainsWindParams.jump_fade_in_sec);
    mJumped = true;
}

void Unk_710260f2b8::hm14() {
    mEntry = sub_71010209FC(mJumped ? sRemainsWindParams.main : sRemainsWindParams.intro);
}

void Unk_710260f2b8::hm15() {
    if (!mEntry)
        return;
    if (!mEntry->sub_7100FF6DF4(this))
        hm14();
    if (mEntry && mJumped) {
        mFader.calc();
        mEntry->_20 = sead::Mathf::clampMin(mFader.getValue(), 0.0f);
    }
}

Unk_710260f2b8::~Unk_710260f2b8() = default;

void Unk_710260f2b8::fadeOutMaybe(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
}

Unk_710260ecf8::~Unk_710260ecf8() = default;

// NON_MATCHING: the original loads the asset call table before calling getResourceAccessor (C++14 argument order).
void Unk_710260ecf8::hm14() {
    auto* entry = sub_7101020B40();
    _189 = false;
    if (entry && entry->sub_7100FF6DF4(this) && entry->mHandle.isActive()) {
        _189 = mUserInstance->getResourceAccessor().isNeedObserve(
            *entry->mHandle.getEvent()->getAssetCallTable());
    }
}

void Unk_710260ecf8::hm15() {
    if (mEntries.size() == 0 && mStarted) {
        sub_710101D9F4(0.0f);
        m6(false);
        mStarted = false;
    }
}

}  // namespace ksys::snd

// inline-only in the original; name is a guess (sub_710100AF98 and the section node 0x710100bb6c repeat it).
inline void Unk_71024fe368::setSectionMaybe(Section section) {
    if (int(mSection) == int(section))
        return;
    for (s32 i = 0; i < mEntries4.size(); ++i)
        mEntries4(i)._98 = -1;
    _220 = 0;
    _218 = 0;
    _21c = 0;
    mSection = section;
    if (mUserInstance)
        mUserInstance->setPropertyValue(0, mSection);
    if (mSubHandle->mUserInstance)
        mSubHandle->mUserInstance->setPropertyValue(0, mSection);
}

// inline-only in the original; name is a guess (sub_710100AF98 and the key node 0x710100b9f8 repeat it).
inline void Unk_71024fe368::setKeyMaybe(Key key) {
    mKey = key;
    if (mUserInstance)
        mUserInstance->setPropertyValue(1, mKey);
    if (mSubHandle->mUserInstance)
        mSubHandle->mUserInstance->setPropertyValue(1, mKey);
}

// inline-only in the original; name is a guess (sub_710100AF98 and the key type node 0x710100bac0 repeat it).
inline void Unk_71024fe368::setKeyTypeMaybe(KeyType type) {
    mKeyType = type;
    if (mUserInstance)
        mUserInstance->setPropertyValue(2, mKeyType);
    if (mSubHandle->mUserInstance)
        mSubHandle->mUserInstance->setPropertyValue(2, mKeyType);
}

Unk_71024fe368::~Unk_71024fe368() {
    if (_248) {
        delete _248;
        _248 = nullptr;
    }
    for (auto& node : mNodes)
        delete &node;
    mNodes.freeBuffer();
    mEntries4.freeBuffer();
    for (auto& property : mProperties)
        delete &property;
    mProperties.freeBuffer();
    if (mSubHandle) {
        delete mSubHandle;
        mSubHandle = nullptr;
    }
}

// 0x710260fa58 / 0x710260fa5c / 0x710260fa60 (placeholder names): debug overrides read by m5 (a flag and the
// tension that replace _1d8._0, and a flag that skips the play wait); nothing in the game writes them.
KSYS_VISIBILITY_HIDDEN bool sUnk_710260FA58;
KSYS_VISIBILITY_HIDDEN s32 sUnk_710260FA5C;
KSYS_VISIBILITY_HIDDEN bool sUnk_710260FA60;

void Unk_71024fe368::m5() {
    if (!mActive || !(_68._18 & 1))
        return;

    switch (mState) {
    case 0: {
        const s32* tension = sUnk_710260FA58 == false ? &_1d8._0 : &sUnk_710260FA5C;
        if (*tension >= 1) {
            if (sUnk_710260FA60 || u8(_1d8._c >> 16)) {
                _1e8 = 0.0f;
                sub_710100AF98();
            } else {
                _1e8 += ksys::snd::sub_710105E3A4();
                const f32 wait = *mInfo->mPlayWaitSec;
                if (_1e8 >= wait) {
                    _1e8 = wait;
                    sub_710100AF98();
                }
            }
        } else {
            _1e8 = 0.0f;
        }
        break;
    }
    case 1: {
        sub_710100B130();
        const s32* tension = sUnk_710260FA58 == false ? &_1d8._0 : &sUnk_710260FA5C;
        if (*tension > 0)
            break;
        _1b0.moveTo(0.0f, *mInfo->mFadeOutSec);
        mState = 2;
        break;
    }
    case 2: {
        sub_710100B130();
        const s32* tension = sUnk_710260FA58 == false ? &_1d8._0 : &sUnk_710260FA5C;
        if (*tension >= 1) {
            _1b0.moveTo(1.0f, 1.0f);
            mState = 1;
            break;
        }
        if (_1b0.getValue() != _1b0.getNextValue())
            break;
        sub_710101D9F4(0.0f);
        mSubHandle->sub_7101020C08(0.0f);
        _248->_18 = 0;
        _1e8 = 0.0f;
        mState = 0;
        break;
    }
    case 3:
        if (_124 == 3 || _124 == 4)
            break;
        sub_710101D9F4(0.0f);
        mSubHandle->sub_7101020C08(0.0f);
        _248->_18 = 0;
        _1e8 = 0.0f;
        mState = 0;
        break;
    case 4:
        if (_230 && _230->sub_7100FF6DF4(this))
            break;
        sub_710101D9F4(0.0f);
        mSubHandle->sub_7101020C08(0.0f);
        _248->_18 = 0;
        _1e8 = 0.0f;
        mState = 0;
        break;
    }

    _1b0.calc();
    _a4 = _1b0.getValue();
}

// NON_MATCHING: the original computes the fader address in both arms of the first test and keeps -1 in a
// callee-saved register.
void Unk_71024fe368::sub_710100AF98() {
    _228 = -1;
    if (sUnk_710260FA60 || u8(_1d8._c >> 16)) {
        _1b0.setValueImmediate(1.0f);
        _248->_8 = _268;
        setSectionMaybe(Section::Middle);
        setKeyMaybe(Key::調2);
        setKeyTypeMaybe(KeyType::B);
    } else {
        _1b0.setValueImmediate(0.0f);
        _1b0.moveTo(1.0f, *mInfo->mFadeInSec);
        _248->_8 = _260;
    }
    sub_710101D9D8();
    mState = 1;
}

// 0x710260fa70 (placeholder name): debug request for a hit part (cleared by sub_710100B130; nothing in the game
// sets it).
KSYS_VISIBILITY_HIDDEN u8 sUnk_710260FA70;

void Unk_71024fe368::sub_710100B130() {
    bool request = false;
    if (sUnk_710260FA70 == 1) {
        sUnk_710260FA70 = 0;
        request = true;
    }
    if (_1d8._4 >= 1)
        _1d8._4 = 0;
    else if (!request)
        return;

    if (_124 != 3 && _124 != 4)
        return;
    if (_220 != 0)
        return;
    if (mState != 1 && mState != 2)
        return;

    sead::FormatFixedSafeString<32> name("Hit_Chain%d", _218);
    sub_710100B7E0(name, *mInfo->mReserveHitWaitBeat, false);
    const u32 chain = _218;
    auto* info = mInfo;
    const agl::utl::Parameter<u32>* ignore_grid;
    switch (chain) {
    case 2:
        ignore_grid = &info->mIgnoreReserveHitGrid_Chain2;
        break;
    case 1:
        ignore_grid = &info->mIgnoreReserveHitGrid_Chain1;
        break;
    default:
        ignore_grid = &info->mIgnoreReserveHitGrid_Chain0;
        break;
    }
    _220 = **ignore_grid;
    _21c = *info->mHitChainGridThreshold;
    _218 = chain + 1 > 2 ? 0 : chain + 1;
}

void Unk_71024fe368::calc() {
    Unk_SpotBgmHandle::calc();
    mSubHandle->_a4 = _138.getValue() * _1b0.getValue();
    mSubHandle->calc();
}

void Unk_71024fe368::m13(f32 fade_sec) {
    sub_710101D9F4(fade_sec);
    mSubHandle->sub_7101020C08(fade_sec);
    _248->_18 = 0;
    _1e8 = 0;
    mState = 0;
    mSubHandle->sub_7101020C08(fade_sec);
}

void Unk_71024fe368::sub_710100B30C(const ksys::snd::Unk_BgmControllerM8Arg& arg) {
    _1d8 = arg;
}

bool Unk_71024fe368::m10() {
    if (_124 == 3 || _124 == 4)
        return _160[1] > *mInfo->mFeelPlayingSec;
    return false;
}

void Unk_71024fe368::hm14() {
    _1f8 = 0;
    _1f0 = 0;
    _1f4 = 0;
    _218 = 0;
    _21c = 0;
    _220 = 0;
    _224 = false;
    _228 = -1;
    _230 = nullptr;
    for (s32 i = 0; i < mEntries4.size(); ++i)
        mEntries4(i)._98 = -1;
    mHalfBeatSec = 60.0f / *mInfo->mBpm * 0.5f;
    _248->start();
}

void Unk_71024fe368::sub_710100B7E0(const sead::SafeString& name, s32 value, bool flag) {
    for (s32 i = 0; i < mEntries4.size(); ++i) {
        auto* entry = mEntries4.get(i);
        if (entry->_98 == -1) {
            entry->name.clear();
            entry->name.append(name);
            entry->_98 = value;
            entry->_9c = flag;
            return;
        }
    }
}

void Unk_71024fe368::hm16(s32 arg) {
    if (arg == 2)
        _248->_18 = 0;
    mSubHandle->sub_7101020C08(0.0f);
}

// The field battle BGM nodes (vtables 0x71024fe4d8..0x71024fe748; constructed only inline in
// Unk_71024fe368::sub_71010099F0). Their destructors share the empty 0x71010069cc with the environment nodes.
namespace ksys::snd {

// Debug override of the tension read by Unk_71024fe668 (never written in the original).
KSYS_VISIBILITY_HIDDEN bool sUnk_710260F858;
KSYS_VISIBILITY_HIDDEN s32 sUnk_710260F85C;

// vtable 0x71024fe4d8 (0x30 bytes): picks the key (property 1) from two odds in percent.
class Unk_71024fe4d8 : public Unk_EnvBgmNode {
public:
    Unk_71024fe4d8(Unk_71024fe368* owner, const agl::utl::Parameter<f32>* odds0,
                   const agl::utl::Parameter<f32>* odds1)
        : mOwner(owner), mOdds0(odds0), mOdds1(odds1) {}

    NodeResult isDone() override { return NodeResult::Next; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x710100b9f8
    void start() override {
        const f32 value = sead::GlobalRandom::instance()->getF32() * 100.0f;
        if (value < mOdds0->ref())
            mOwner->setKeyMaybe(Unk_71024fe368::Key::調0);
        else if (value < mOdds1->ref())
            mOwner->setKeyMaybe(Unk_71024fe368::Key::調1);
        else
            mOwner->setKeyMaybe(Unk_71024fe368::Key::調2);
    }

private:
    Unk_71024fe368* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
    const agl::utl::Parameter<f32>* mOdds0;
    const agl::utl::Parameter<f32>* mOdds1;
};

// vtable 0x71024fe528 (0x28 bytes): picks the key type (property 2).
class Unk_71024fe528 : public Unk_EnvBgmNode {
public:
    Unk_71024fe528(Unk_71024fe368* owner, const agl::utl::Parameter<f32>* odds)
        : mOwner(owner), mOdds(odds) {}

    NodeResult isDone() override { return NodeResult::Next; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x710100bac0
    void start() override {
        const f32 value = sead::GlobalRandom::instance()->getF32() * 100.0f;
        if (value < mOdds->ref())
            mOwner->setKeyTypeMaybe(Unk_71024fe368::KeyType::A);
        else
            mOwner->setKeyTypeMaybe(Unk_71024fe368::KeyType::B);
    }

private:
    Unk_71024fe368* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
    const agl::utl::Parameter<f32>* mOdds;
};

// vtable 0x71024fe578 (0x28 bytes): switches to a section (property 0) and clears the queued entries.
class Unk_71024fe578 : public Unk_EnvBgmNode {
public:
    Unk_71024fe578(Unk_71024fe368* owner, Unk_71024fe368::Section section)
        : mOwner(owner), mSection(section) {}

    NodeResult isDone() override { return NodeResult::Next; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x710100bb6c
    void start() override {
        mOwner->setSectionMaybe(mSection);
    }

private:
    Unk_71024fe368* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
    Unk_71024fe368::Section mSection;
};

// vtable 0x71024fe5c8 (0x28 bytes): moves the key on by one or two steps (modulo 3) with the given odds.
class Unk_71024fe5c8 : public Unk_EnvBgmNode {
public:
    Unk_71024fe5c8(Unk_71024fe368* owner, const agl::utl::Parameter<f32>* odds)
        : mOwner(owner), mOdds(odds) {}

    NodeResult isDone() override { return NodeResult::Next; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x710100bc0c
    // NON_MATCHING: clang folds key + 1 > 2 to key > 1 (the original compares key + 1) and loads the key before the
    // random instance.
    void start() override {
        if (sead::GlobalRandom::instance()->getF32() * 100.0f < mOdds->ref())
            return;
        const s32 key = mOwner->mKey + sead::GlobalRandom::instance()->getBool();
        mOwner->setKeyMaybe(key + 1 > 2 ? key - 2 : key + 1);
    }

private:
    Unk_71024fe368* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
    const agl::utl::Parameter<f32>* mOdds;
};

// vtable 0x71024fe618 (0x38 bytes): plays a part and waits its length in beats.
class Unk_71024fe618 : public Unk_EnvBgmNode {
public:
    Unk_71024fe618(Unk_71024fe368* owner, s32 part, const s32* beats)
        : mOwner(owner), mPart(part), mBeats(beats) {}

    // 0x710100bcd4
    NodeResult isDone() override {
        if (mCounter != 0) {
            --mCounter;
            return NodeResult::Running;
        }
        return NodeResult::Next;
    }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x710100bcf8
    void start() override {
        mCounter = *mBeats;
        const s32 part = mPart;
        auto* owner = mOwner;
        owner->sub_71010209FC(Unk_71024fe368::Part::text(part));
        owner->mPart = part;
        owner->_270 = 0;
    }

private:
    Unk_71024fe368* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
    s32 mPart;
    const s32* mBeats;
    s32 mCounter = 0;
};

// vtable 0x71024fe668 (0x30 bytes): branches on the tension (Unk_BgmControllerM8Arg::_0) against a threshold.
class Unk_71024fe668 : public Unk_EnvBgmNode {
public:
    Unk_71024fe668(Unk_71024fe368* owner, const agl::utl::Parameter<s32>* threshold)
        : mOwner(owner), mThreshold(threshold) {}

    NodeResult isDone() override { return NodeResult::Next; }
    // 0x710100bd64
    // NON_MATCHING: the original loads the owner before the flag test and selects the tension address with csel.
    Unk_EnvBgmNode* getNext() override {
        const s32* tension = sUnk_710260F858 == false ? &mOwner->_1d8._0 : &sUnk_710260F85C;
        return mBranches[*tension >= mThreshold->ref()];
    }
    void setNext(Unk_EnvBgmNode* next) override {}
    // 0x710100be34
    void setBranch(Unk_EnvBgmNode* next, s32 index) override { mBranches[index] = next; }
    void start() override {}

private:
    Unk_71024fe368* mOwner;
    sead::SafeArray<Unk_EnvBgmNode*, 2> mBranches;
    const agl::utl::Parameter<s32>* mThreshold;
};

// vtable 0x71024fe748 (0x20 bytes): sets the owner's _1f8 flag.
class Unk_71024fe748 : public Unk_EnvBgmNode {
public:
    explicit Unk_71024fe748(Unk_71024fe368* owner) : mOwner(owner) {}

    NodeResult isDone() override { return NodeResult::Next; }
    Unk_EnvBgmNode* getNext() override { return mNext; }
    void setNext(Unk_EnvBgmNode* next) override { mNext = next; }
    // 0x710100ca60
    void start() override { mOwner->_1f8 = 1; }

private:
    Unk_71024fe368* mOwner;
    Unk_EnvBgmNode* mNext = nullptr;
};

}  // namespace ksys::snd

namespace {
sead::SafeString sStr_FieldBattleBgm = "FieldBattleBgm";
sead::SafeString sStr_FieldBattleBgm_Hit = "FieldBattleBgm_Hit";

// 0x71024fe4a8: the length in beats of each Part.
const s32 sPartBeats[] = {29, 29, 13, 13, 54, 6, 68, 48, 16, 90, 84, 30};
}  // namespace

// NON_MATCHING: written from the original's structure; not compared in detail (4.7 KB).
void Unk_71024fe368::sub_71010099F0(const ksys::snd::BgmInitArg& arg) {
    using namespace ksys::snd;
    auto* heap = arg.heap;
    mInfo = static_cast<FieldBattleBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::FieldBattleBgm));

    mProperties.allocBuffer(PropertyType::size(), heap);
    auto* section = new (heap) xlink2::EnumPropertyDefinition(PropertyType::text(0), Section::size(), heap, false);
    for (s32 i = 0; i < Section::size(); ++i)
        section->entry(i, Section::text(i));
    mProperties.pushBack(section);
    auto* key = new (heap) xlink2::EnumPropertyDefinition(PropertyType::text(1), Key::size(), heap, false);
    for (s32 i = 0; i < Key::size(); ++i)
        key->entry(i, Key::text(i));
    mProperties.pushBack(key);
    auto* key_type = new (heap) xlink2::EnumPropertyDefinition(PropertyType::text(2), KeyType::size(), heap, false);
    for (s32 i = 0; i < KeyType::size(); ++i)
        key_type->entry(i, KeyType::text(i));
    mProperties.pushBack(key_type);

    Unk_SpotBgmHandle::init(heap, sStr_FieldBattleBgm, &mProperties);
    if (auto* instance = mUserInstance) {
        instance->setPropertyValue(0, mSection);
        instance->setPropertyValue(1, mKey);
        instance->setPropertyValue(2, mKeyType);
    }
    mSubHandle = new (heap) Unk_710260f248(Unk_710260f248Type::_0);
    mSubHandle->init(heap, sStr_FieldBattleBgm_Hit, &mProperties);
    if (auto* instance = mSubHandle->mUserInstance) {
        instance->setPropertyValue(0, mSection);
        instance->setPropertyValue(1, mKey);
        instance->setPropertyValue(2, mKeyType);
    }

    mEntries4.tryAllocBuffer(4, heap);
    mNodes.allocBuffer(0x20, heap);
    _248 = new (heap) Unk_71024fdde8;

    Unk_71024fe618* parts[Part::size()];
    for (s32 i = 0; i < Part::size(); ++i) {
        parts[i] = new (heap) Unk_71024fe618(this, i, &sPartBeats[i]);
        mNodes.pushBack(parts[i]);
    }
    auto* skip_easy2 = new (heap) Unk_71024fe668(this, &mInfo->mTension_SkipEasy2);
    mNodes.pushBack(skip_easy2);
    auto* skip_easy5 = new (heap) Unk_71024fe668(this, &mInfo->mTension_SkipEasy5);
    mNodes.pushBack(skip_easy5);
    auto* skip_middle1 = new (heap) Unk_71024fe668(this, &mInfo->mTension_SkipMiddle1);
    mNodes.pushBack(skip_middle1);
    auto* skip_hard = new (heap) Unk_71024fe668(this, &mInfo->mTension_SkipHard);
    mNodes.pushBack(skip_hard);
    auto* first_key = new (heap) Unk_71024fe4d8(this, &mInfo->mEasy1_OddsByKey0, &mInfo->mEasy1_OddsByKey1);
    mNodes.pushBack(first_key);
    auto* key_easy1r = new (heap) Unk_71024fe5c8(this, &mInfo->mEasy1R_OddsBySameKey);
    mNodes.pushBack(key_easy1r);
    auto* key_easy5 = new (heap) Unk_71024fe5c8(this, &mInfo->mEasy5_OddsBySameKey);
    mNodes.pushBack(key_easy5);
    auto* key_middle0 = new (heap) Unk_71024fe5c8(this, &mInfo->mMiddle0_OddsBySameKey);
    mNodes.pushBack(key_middle0);
    auto* key_hard0 = new (heap) Unk_71024fe5c8(this, &mInfo->mHard0_OddsBySameKey);
    mNodes.pushBack(key_hard0);
    auto* key_hard1 = new (heap) Unk_71024fe5c8(this, &mInfo->mHard1_OddsBySameKey);
    mNodes.pushBack(key_hard1);
    auto* key_hard1f = new (heap) Unk_71024fe5c8(this, &mInfo->mHard1F_OddsBySameKey);
    mNodes.pushBack(key_hard1f);
    auto* key_type0 = new (heap) Unk_71024fe528(this, &mInfo->mOddsByKeySubId0);
    mNodes.pushBack(key_type0);
    auto* key_type1 = new (heap) Unk_71024fe528(this, &mInfo->mOddsByKeySubId0);
    mNodes.pushBack(key_type1);
    auto* key_type2 = new (heap) Unk_71024fe528(this, &mInfo->mOddsByKeySubId0);
    mNodes.pushBack(key_type2);
    auto* key_type3 = new (heap) Unk_71024fe528(this, &mInfo->mOddsByKeySubId0);
    mNodes.pushBack(key_type3);
    auto* section_easy = new (heap) Unk_71024fe578(this, Section::Easy);
    mNodes.pushBack(section_easy);
    auto* section_easy2 = new (heap) Unk_71024fe578(this, Section::Easy);
    mNodes.pushBack(section_easy2);
    auto* section_middle = new (heap) Unk_71024fe578(this, Section::Middle);
    mNodes.pushBack(section_middle);
    auto* section_hard = new (heap) Unk_71024fe578(this, Section::Hard);
    mNodes.pushBack(section_hard);
    auto* flag = new (heap) Unk_71024fe748(this);
    mNodes.pushBack(flag);

    first_key->setNext(section_easy);
    section_easy->setNext(parts[Part::Easy1]);
    parts[Part::Easy1]->setNext(skip_easy2);
    skip_easy2->setBranch(parts[Part::Easy2], 0);
    skip_easy2->setBranch(flag, 1);
    parts[Part::Easy2]->setNext(parts[Part::Easy3]);
    flag->setNext(parts[Part::Easy3]);
    parts[Part::Easy3]->setNext(parts[Part::Easy4]);
    parts[Part::Easy4]->setNext(skip_easy5);
    skip_easy5->setBranch(key_easy5, 0);
    skip_easy5->setBranch(parts[Part::Easy6], 1);
    key_easy5->setNext(key_type0);
    key_type0->setNext(parts[Part::Easy5]);
    parts[Part::Easy5]->setNext(parts[Part::Easy6]);
    parts[Part::Easy6]->setNext(key_middle0);
    key_middle0->setNext(key_type1);
    key_type1->setNext(section_middle);
    section_middle->setNext(parts[Part::Middle0]);
    parts[Part::Middle0]->setNext(skip_middle1);
    skip_middle1->setBranch(parts[Part::Middle1], 0);
    skip_middle1->setBranch(parts[Part::Middle2], 1);
    parts[Part::Middle1]->setNext(parts[Part::Middle2]);
    parts[Part::Middle2]->setNext(skip_hard);
    skip_hard->setBranch(key_easy1r, 0);
    key_easy1r->setNext(section_easy);
    skip_hard->setBranch(section_hard, 1);
    section_hard->setNext(key_hard0);
    key_hard0->setNext(parts[Part::Hard0]);
    parts[Part::Hard0]->setNext(key_hard1);
    key_hard1->setNext(key_type2);
    key_type2->setNext(parts[Part::Hard1]);
    parts[Part::Hard1]->setNext(key_hard1f);
    key_hard1f->setNext(key_type3);
    key_type3->setNext(section_easy2);
    section_easy2->setNext(parts[Part::Easy5]);
    parts[Part::QuickIntro]->setNext(parts[Part::Middle0]);

    _260 = first_key;
    _268 = parts[Part::QuickIntro];
}
