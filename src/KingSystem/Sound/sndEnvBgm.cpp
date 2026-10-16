#include "KingSystem/Sound/sndEnvBgm.h"
#include <cmath>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtManagerInline.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/World/worldTimeMgr.h"

// The environment BGM TU (0x7101003df4..0x71010073b0): the node constructors; the nodes' inline virtuals are
// emitted at its end (0x7101006940..).

namespace ksys::snd {

// NON_MATCHING: the flag value is tested with `cmp #0` in the original (`tst #1` here).
Unk_71025ce350::Unk_71025ce350(const BgmInitArg& arg) : Bgm(arg.kind) {
    mInfo = static_cast<EnvBgmInfo*>(sub_7100FFD76C()->getInfo(MusicInfoType::EnvBgm));
    bool value = false;
    _3e = !(gdt::getBoolByName(gdt::Manager::instance(), &value, "FirstTouchdown") && value);
}

Unk_71025ce350::~Unk_71025ce350() {
    for (auto*& handle : mHandles) {
        if (handle) {
            handle->sub_710101D9A4();
            delete handle;
            handle = nullptr;
        }
    }
}

// NON_MATCHING: the original converts the spilled time type to an integer once (one reload for the compare and
// the store); this version reloads it for the store.
void Unk_71025ce350::m12(f32 fade_sec) {
    EnvBgmInfo::EnvTimeEnum type = EnvBgmInfo::EnvTimeEnum::EnvDayBgm;
    if (mHandles[type])
        mHandles[type]->sub_7101020BB0(fade_sec);
    type = EnvBgmInfo::EnvTimeEnum::EnvNightBgm;
    if (mHandles[type])
        mHandles[type]->sub_7101020BB0(fade_sec);

    const f32 hour = world::Manager::instance()->getTimeMgr()->getTime() / 15.0f;
    EnvBgmInfo::EnvTimeEnum time_type;
    if (hour >= mInfo->mTimeDay.ref() && hour < mInfo->mTimeNight.ref())
        time_type = EnvBgmInfo::EnvTimeEnum::EnvDayBgm;
    else
        time_type = EnvBgmInfo::EnvTimeEnum::EnvNightBgm;
    if (mTimeType != time_type) {
        sub_710100454C();
        mTimeType = time_type;
    }
    _3c = false;
    _3d = 0;
    _34 = 0;
    _38 = 0;
    _2c = 1;
}

void Unk_71025ce350::m13(f32 fade_sec) {
    EnvBgmInfo::EnvTimeEnum type = EnvBgmInfo::EnvTimeEnum::EnvDayBgm;
    if (mHandles[type])
        mHandles[type]->sub_710101D9F4(fade_sec);
    type = EnvBgmInfo::EnvTimeEnum::EnvNightBgm;
    if (mHandles[type])
        mHandles[type]->sub_710101D9F4(fade_sec);
    _2c = 0;
}

// NON_MATCHING: the original deletes the properties with the same pointer loop as the nodes (a range-for), but
// sead::PtrArray<const T> cannot be iterated here (PtrArray::data() casts away const), so an index loop is used.
Unk_71024fdb00::~Unk_71024fdb00() {
    for (auto*& machine : mPartMachines) {
        if (machine) {
            delete machine;
            machine = nullptr;
        }
    }
    for (auto& node : mNodes)
        delete &node;
    mNodes.freeBuffer();
    mEntries.freeBuffer();
    for (s32 i = 0; i < mProperties.size(); ++i)
        delete mProperties[i];
    mProperties.freeBuffer();
}

// NON_MATCHING: wait_count and part are kept in swapped callee-saved registers (regalloc).
void Unk_71024fdb00::sub_7101005874(const sead::SafeString& name, s32 wait_count, u8 part, f32 volume,
                                    f32 pan) {
    if (!_1ac)
        return;

    if (wait_count == 0) {
        auto* entry = sub_71010209FC(name);
        if (!entry)
            return;
        entry->_20 = std::fmax(volume, 0.0f);
        if (pan != 0.0f)
            entry->mPan = sead::Mathf::clamp(pan, -1.0f, 1.0f);
        return;
    }

    for (s32 i = 0; i < mEntries.size(); ++i) {
        auto* entry = mEntries.get(i);
        if (entry->wait_count == 0) {
            entry->name.clear();
            entry->name.append(name);
            entry->part = part;
            entry->wait_count = wait_count;
            entry->wait_count_init = wait_count;
            entry->volume = volume;
            entry->pan = pan;
            break;
        }
    }
}

Unk_71024fdb98::Unk_71024fdb98(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                               const agl::utl::Parameter<u32>* wait_count,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mPart(part), mWaitCount(wait_count), mVolume(volume),
      mPan(pan) {
    mName.append(name);
}

Unk_71024fdbe8::Unk_71024fdbe8(Unk_71024fdb00* owner, const sead::SafeString& name,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mVolume(volume), mPan(pan) {
    mName.append(name);
}

Unk_71024fdc38::Unk_71024fdc38(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                               const agl::utl::Parameter<u32>* wait_count,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mPart(part), mWaitCount(wait_count), mVolume(volume),
      mPan(pan) {
    mName.append(name);
}

Unk_71024fdc88::Unk_71024fdc88(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                               const agl::utl::Parameter<u32>* wait_count_base,
                               const MusicInfo::MinMax<u32>* wait_count_rate,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : Unk_EnvBgmNode(owner), mPart(part), mWaitCountBase(wait_count_base),
      mWaitCountRate(wait_count_rate), mVolume(volume), mPan(pan) {
    mName.append(name);
}

}  // namespace ksys::snd
