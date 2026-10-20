#include <nn/atk.h>
#include <gfx/seadTextWriter.h>
#include <prim/seadScopedLock.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Sound/sndMusicInfo.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Sound/Actor/Action/actionSpotBgmTriggerAction.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2SystemSLink.h>
#include "KingSystem/Sound/sndMusicDefinition.h"
#include "KingSystem/World/worldManager.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorSystem.h"

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

// 0x7102610448: debug flag (never written).
KSYS_VISIBILITY_HIDDEN bool sUnk_7102610448;

void Unk_710260f228::m14(sead::TextWriter& writer) {
    if (!sUnk_7102610448)
        return;
    writer.printf("----チュートリアル戦闘BGM----\n");
    writer.printf("処理        :%s\n", mActive ? "有効" : "無効");
    writer.printf("状態        :%s\n", State::text(mState) ? State::text(mState) : "不明");
    writer.printf("再生待ち秒  :%.3f\n", mTimer);
    writer.printf("段階        :%s\n", Lesson::text(mLesson.value) ? Lesson::text(mLesson.value) : "不明");
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
    sub_7101020BB0(fade_sec);
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
        sub_710101D9F4(fade_sec);
    _368 &= ~0x10023u;
}

void Unk_SpotBgmInstance::sub_71010242C8() {
    if (!(_368 & 4))
        return;
    const f32 value = (_368 & 0x8000) ? 1.0f : 0.0f;
    _368 &= ~0xcu;
    _260 = value;
}

Unk_SpotBgmInstanceBase::~Unk_SpotBgmInstanceBase() = default;

// NON_MATCHING: same vtable layout difference (secondary vptr +0x50 vs +0x40, one more live
// register) and the _268 / _290 store order.
Unk_SpotBgmInstance::Unk_SpotBgmInstance(bool a)
    : Unk_71024fc7f8(ksys::snd::Unk_710260f248Type(a)) {
    _368 |= 0x90;
}

// NON_MATCHING: the handle base's hm14 / hm15 overrides also go into our primary vtable, so our
// secondary vptr is stored at +0x50 instead of +0x40; the four destructors are otherwise identical.
Unk_SpotBgmInstance::~Unk_SpotBgmInstance() {
    _188 = 0xdeadca11;
    if (mShape) {
        mShape->destroy();
        mShape = nullptr;
    }
}

void Unk_SpotBgmInstance::hm14() {
    if (mEntries.size() != 0)
        _368 |= 0x10000;
    else
        sub_7101024374();
}

void Unk_SpotBgmInstance::hm15() {
    Unk_SpotBgmInstance::sub_71010246CC();
}

void Unk_SpotBgmInstance::sub_7101024358() {
    if (mEntries.size() != 0)
        _368 |= 0x10000;
    else
        sub_7101024374();
}

void Unk_SpotBgmInstance::sub_7101024280() {
    if (!(_368 & 2))
        return;
    if (_368 & 1)
        sub_710101D9F4(mInfo->mFadeOutSec.ref());
    _368 &= ~0x22u;
}

void Unk_SpotBgmInstance::sub_71010242F0() {
    _308 = 1;
    _368 |= 0x200;
    _310.setValueImmediate(0.0f);
}

// A sub-track's distance and whether it overrides the value computed by Unk_710260f1a8::m5.
struct SubTrackDistance {
    SubTrackDistance() : distance(9999.0f), overridden(false) {}
    SubTrackDistance(f32 d, bool o) : distance(d), overridden(o) {}

    f32 distance;
    bool overridden;
};

// 0x7102610350: the never-written debug distances (both flags stay false, so the computed values
// below are used). 0x7102610360: the distances Unk_710260f1a8::m5 sets from the listener position.
KSYS_VISIBILITY_HIDDEN SubTrackDistance sUnk_7102610350[2];
sead::SafeArray<SubTrackDistance, 2> sUnk_7102610360;

// 0x7101024314 / 0x710102432c: the per-frame distance of sub-track 0 / 1.
void setSubTrack0DistanceMaybe(f32 distance) {
    sUnk_7102610360[0].overridden = true;
    sUnk_7102610360[0].distance = distance;
}

void setSubTrack1DistanceMaybe(f32 distance) {
    sUnk_7102610360[1].overridden = true;
    sUnk_7102610360[1].distance = distance;
}

// 0x7101024344: drops both computed distances again.
void clearSubTrackDistancesMaybe() {
    sUnk_7102610360[0].overridden = false;
    sUnk_7102610360[1].overridden = false;
}

// 0x7101024808: fades the two sub-track faders from the sub-track distances (near distance is
// volume 1, far distance volume 0) and writes the fader values to the playing entry's volumes.
void sub_7101024808(Unk_SpotBgmInstance* instance) {
    for (auto it = Unk_SpotBgmInstance::SubTrack::begin(); it != Unk_SpotBgmInstance::SubTrack::end();
         ++it) {
        const Unk_SpotBgmInstance::SubTrack idx = *it;
        const SubTrackDistance* entry = sUnk_7102610350[idx].overridden
                                            ? &sUnk_7102610350[idx]
                                            : &sUnk_7102610360[idx];
        if (!entry)
            continue;

        f32 value = 0.0f;
        if (entry->overridden) {
            const f32 near = instance->mInfo->mSubTrackNearDistance.ref();
            const f32 far = instance->mInfo->mSubTrackFarDistance.ref();
            if (near < far) {
                value = (entry->distance - far) / (near - far);
                if (value < 0.0f)
                    value = 0.0f;
                else if (value > 1.0f)
                    value = 1.0f;
            } else {
                value = entry->distance < near ? 1.0f : 0.0f;
            }
        }

        instance->mSubTrackFaders[*it].moveToTargetByStep(
            value, instance->mInfo->mSubTrackVolumeMaxDelta.ref());
        instance->mSubTrackFaders[*it].calc();

        if (instance->mEntry && instance->mEntry->sub_7100FF6DF4(instance)) {
            const s32 volume_index = *it + 1;
            instance->mEntry->sub_7100FF6A50(volume_index,
                                             instance->mSubTrackFaders[*it].getValue());
        }
    }
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

// 0x7102610328 / 0x7102500b48 (placeholder names): a debug switch nothing writes and the part count it forces.
KSYS_VISIBILITY_HIDDEN bool sUnk_7102610328;
KSYS_VISIBILITY_HIDDEN s32 sUnk_7102500B48 = -1;

// NON_MATCHING: the clamp of diff - 1 (subs + csel in the original) and the frame setup differ.
void Unk_7102500a00::m12(f32 fade_sec) {
    if (_20c & 3)
        return;
    const s32& count = sUnk_7102610328 ? sUnk_7102500B48 : _198;
    const s32 diff = _19c - count;
    if (diff == 0) {
        _1a0 = 0;
        _1a4 = -1;
    } else if (count >= 1) {
        _1a0 = 1;
        _1a4 = diff - 1 < 0 ? 0 : diff - 1;
    } else {
        _1a0 = 2;
        _1a4 = -1;
    }
    sub_710101D9D8();
    sub_710101D9D8();
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

Unk_7102500e08::Unk_7102500e08(const ksys::snd::BgmInitArg& arg) : Bgm(arg.kind) {
    for (s32 i = 0; i < 3; ++i) {
        mHandles[i] = nullptr;
        _30[i] = 0;
        mFaders[i].setValueImmediate(1.0f);
    }
    sub_7101025840(arg);
}

Unk_7102500e08::~Unk_7102500e08() {
    if (mHandles[0]) {
        mHandles[0]->sub_710101D9A4();
        delete mHandles[0];
    }
    if (mHandles[1]) {
        mHandles[1]->sub_710101D9A4();
        delete mHandles[1];
    }
    if (mHandles[2]) {
        mHandles[2]->sub_710101D9A4();
        delete mHandles[2];
    }
}

namespace {
const char* sTemperatureBgmAssetNames[] = {"Bgm_TemperatureCold", "Bgm_TemperatureHot",
                                           "Bgm_TemperatureBurn"};
}  // namespace

void Unk_7102500e08::m5() {
    if (!mActive)
        return;
    bool ignited = false;
    if (auto* link = ksys::act::ActorSystem::instance()->getPlayerLink()) {
        if (auto* player = link->getPlayer()) {
            const sead::Vector3f pos = player->getMtx().getTranslation();
            _88 = ksys::world::Manager::instance()->getIgnitedLevel(pos);
            ignited = _88 > 0;
        }
    }
    _3c = ignited;
    using ksys::snd::TemperatureBgmInfo;
    sub_7101025CA4(TemperatureBgmInfo::TemperatureEnum::ColdBgm);
    sub_7101025CA4(TemperatureBgmInfo::TemperatureEnum::HotBgm);
    sub_7101025CA4(TemperatureBgmInfo::TemperatureEnum::BurnBgm);
}

void Unk_7102500e08::m12(f32 fade_sec) {
    using ksys::snd::TemperatureBgmInfo;
    for (s32 i = 0; i < TemperatureBgmInfo::TemperatureEnum::size(); ++i) {
        const TemperatureBgmInfo::TemperatureEnum type = i;
        mHandles[type]->sub_7101020BB0(fade_sec);
    }
}

void Unk_7102500e08::m13(f32 fade_sec) {
    using ksys::snd::TemperatureBgmInfo;
    for (s32 i = 0; i < TemperatureBgmInfo::TemperatureEnum::size(); ++i) {
        const TemperatureBgmInfo::TemperatureEnum type = i;
        if (_30[type]) {
            mHandles[type]->sub_710101D9F4(fade_sec);
            mFaders[type].setValueImmediate(1.0f);
            _30[type] = 0;
        }
    }
}

void Unk_7102500e08::sub_7101025840(const ksys::snd::BgmInitArg& arg) {
    using ksys::snd::TemperatureBgmInfo;
    sead::Heap* heap = arg.heap;
    for (s32 i = 0; i < TemperatureBgmInfo::TemperatureEnum::size(); ++i) {
        const char* name = TemperatureBgmInfo::TemperatureEnum::text(i);
        const TemperatureBgmInfo::TemperatureEnum type = i;
        auto* handle = new (heap, 8) Unk_71024fd3a0(arg.handle_type);
        handle->sub_7101022DEC(heap, name, sTemperatureBgmAssetNames[type]);
        handle->sub_710101D970();
        mHandles[type] = handle;
    }
    mInfo = static_cast<TemperatureBgmInfo*>(
        ksys::snd::sub_7100FFD76C()->getInfo(ksys::snd::MusicInfoType::TemperatureBgm));
}

void Unk_71024fd3a0::sub_7101022DEC(sead::Heap* heap, const sead::SafeString& name,
                                    const sead::SafeString& asset) {
    Unk_SpotBgmHandle::init(heap, name, nullptr);
    _180.clear();
    _180.append(asset);
}

// NON_MATCHING: the listener position and flag snapshot use different register allocation.
void Unk_SpotBgmInstance::sub_7101023EC8() {
    if (_368 & 4)
        return;
    auto* listener = ksys::snd::SoundMgr::instance()->sub_71011FC2D0();
    if (_264 <= 0.0f) {
        _248 = 0.0f;
        _24c = 0.0f;
        _250 = 0.0f;
    } else {
        _248 = _254 - listener->getMatrix()(0, 3);
        _24c = _258 - listener->getMatrix()(1, 3);
        _250 = _25c - listener->getMatrix()(2, 3);
    }
    _260 = 0.0f;
    const u32 flags = _368;
    _368 = flags | 4;
    if (flags & 0x4000)
        _368 = flags | 0x8004;
}

void Unk_SpotBgmInstance::sub_71010241D0(bool allow, bool fade_in) {
    if (allow) {
        if (_368 & 0x20)
            return;
        if (fade_in) {
            _278.setValueImmediate(0.0f);
            _278.moveTo(1.0f, mInfo->mAllowFadeInSec.ref());
        } else {
            _278.setValueImmediate(1.0f);
        }
        if (_124 == 0)
            sub_710101D9D8();
        _368 |= 0x20;
    } else {
        if (!(_368 & 0x20))
            return;
        if (_124 != 0)
            sub_710101D9F4(mInfo->mAllowFadeOutSec.ref());
        _368 &= ~0x20u;
    }
}

// NON_MATCHING: entry validation and event handle updates use different scheduling.
void Unk_SpotBgmInstance::sub_71010246CC() {
    if (_368 & 0x10000) {
        if (mEntries.size() == 0) {
            sub_7101024374();
            _368 &= ~0x10000u;
        }
    } else if (mEntry) {
        if (!mEntry->sub_7100FF6DF4(this)) {
            // The native path checks the server connection and discards the result.
            xlink2::SystemSLink::instance()->isServerConnecting();
            sub_7101024374();
        } else {
            mEntry->mHandle.setLpfScale(_2a0.getValue());
            auto* event = static_cast<xlink2::EventSLink*>(mEntry->mHandle.getEvent());
            if (event && event->getCreateId() == mEntry->mHandle.getCreateId()) {
                if (auto* executor = event->getAliveAssetExecutor()) {
                    auto* handle = executor->getHandle();
                    if (handle->isActive())
                        handle->setBiquadFilter(2, _2b8.getValue());
                }
            }
            if (_368 & 0x100)
                sub_7101024808(this);
        }
    }
    if (auto* status = ksys::snd::SoundMgr::instance()->_288)
        status->mPlayingPart[7] = 1;
}

// 0x710102498c (unnamed in the CSV): the stream region callback of a spot BGM instance.
nn::atk::StreamRegionCallbackResult sub_710102498C(nn::atk::StreamRegionCallbackParam* param,
                                                   void* user) {
    auto* instance = static_cast<Unk_SpotBgmInstance*>(user);
    if (instance->_188 != 0xca11bac4)
        return nn::atk::StreamRegionCallbackResult(0);

    if (instance->_368 & 0x80) {
        instance->_2d4 = (instance->_368 >> 4) & 4;
        instance->_368 &= ~0x80u;
    } else {
        switch (param->mRegion) {
        case 1:
            if (instance->_368 & 0x40)
                instance->_2d4 = 8;
            else
                instance->_2d4 = instance->_2d4 + 1;
            break;
        case 2:
            if (instance->_368 & 0x40) {
                instance->_2d4 = 12;
                break;
            }
            [[fallthrough]];
        case 10:
            instance->_2d4 = 1;
            break;
        case 5:
            if (instance->_368 & 0x40)
                instance->_2d4 = instance->_2d4 + 1;
            else
                instance->_2d4 = 10;
            break;
        case 6:
            if (!(instance->_368 & 0x40)) {
                instance->_2d4 = 14;
                break;
            }
            [[fallthrough]];
        case 8:
            instance->_2d4 = 5;
            break;
        case 12:
            instance->_2d4 = 6;
            break;
        case 14:
            instance->_2d4 = 2;
            break;
        default:
            instance->_2d4 = instance->_2d4 + 1;
            break;
        }
    }
    param->mRegion = instance->_2d4;
    return nn::atk::StreamRegionCallbackResult(1);
}
