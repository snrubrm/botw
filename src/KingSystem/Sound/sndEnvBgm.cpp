#include "KingSystem/Sound/sndEnvBgm.h"
#include <xlink2/xlink2EnumPropertyDefinition.h>
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
    for (auto& property : mProperties)
        delete &property;
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

// NON_MATCHING: written from the original's structure; not compared in detail (3140 B).
void Unk_71024fdb00::sub_7101004A54(sead::Heap* heap, EnvBgmInfo::EnvTimeEnum type, EnvBgmInfo* info) {
    mTimeType = type;
    mInfo = info;
    const auto& params = info->mParamPerTypes[type];

    mProperties.allocBuffer(PropertyType::size(), heap);
    auto* section = new (heap) xlink2::EnumPropertyDefinition(PropertyType::text(0), Section::size(), heap, false);
    for (s32 i = 0; i < Section::size(); ++i)
        section->entry(i, Section::text(i));
    mProperties.pushBack(section);
    auto* part0 = new (heap) xlink2::EnumPropertyDefinition(PropertyType::text(1), 16, heap, false);
    for (s32 i = 0; i < 16; ++i)
        part0->entry(i, sub_7101006E6C(i));
    mProperties.pushBack(part0);

    Unk_SpotBgmHandle::init(heap, type.text(), &mProperties);
    mBpm = params.mBpm.ref();
    mBeatSec = 60.0f / static_cast<f32>(mBpm);
    _1b8 = mInfo->mMasterBeatBase.ref();
    mEntries.tryAllocBuffer(8, heap);
    mNodes.allocBuffer(0x20, heap);

    mPartMachines[0] = new (heap) Unk_71024fdde8;
    if (mPartMachines[0]) {
        auto* intro = new (heap) Unk_71024fdb98(this, "Part0_A0", 0, &params.mPart0FirstWaitCount,
                                                &mInfo->mConstVolume, &mInfo->mConstPan);
        mNodes.pushBack(intro);
        mPartMachines[0]->_8 = intro;
        auto* main = new (heap) Unk_71024fdbe8(this, "Part0", &mInfo->mPart0Volume, &mInfo->mPart0Pan);
        mNodes.pushBack(main);
        intro->setNext(main);
        auto* wait = new (heap) Unk_71024fdcd8(this);
        mNodes.pushBack(wait);
        main->setNext(wait);
        wait->setNext(main);
    }

    mPartMachines[1] = new (heap) Unk_71024fdde8;
    if (mPartMachines[1]) {
        auto* intro = new (heap) Unk_71024fdc38(this, "Part1_A0", 1, &params.mPart1FirstWaitCount,
                                                &mInfo->mConstVolume, &mInfo->mPart1Pan);
        mNodes.pushBack(intro);
        mPartMachines[1]->_8 = intro;
        auto* branch = new (heap) Unk_71024fdd28(this);
        mNodes.pushBack(branch);
        intro->setNext(branch);
        auto* a = new (heap) Unk_71024fdc88(this, "Part1", 1, &mInfo->mPart1SegmentAWaitCountBase,
                                            &mInfo->mPart1SegmentAWaitCountRate, &mInfo->mPart1Volume,
                                            &mInfo->mPart1Pan);
        mNodes.pushBack(a);
        branch->setBranch(a, 0);
        auto* b = new (heap) Unk_71024fdc88(this, "Part1", 1, &mInfo->mPart1SegmentBWaitCountBase,
                                            &mInfo->mPart1SegmentBWaitCountRate, &mInfo->mPart1Volume,
                                            &mInfo->mPart1Pan);
        mNodes.pushBack(b);
        branch->setBranch(b, 1);
        auto* c = new (heap) Unk_71024fdc88(this, "Part1", 1, &mInfo->mPart1SegmentCWaitCountBase,
                                            &mInfo->mPart1SegmentCWaitCountRate, &mInfo->mPart1Volume,
                                            &mInfo->mPart1Pan);
        mNodes.pushBack(c);
        branch->setBranch(c, 2);
        a->setNext(branch);
        b->setNext(branch);
        c->setNext(branch);
    }

    mPartMachines[2] = new (heap) Unk_71024fdde8;
    if (mPartMachines[2]) {
        auto* intro = new (heap) Unk_71024fdc38(this, "Part2_A0", 2, &params.mPart2FirstWaitCount,
                                                &mInfo->mPart2Volume, &mInfo->mConstPan);
        mNodes.pushBack(intro);
        mPartMachines[2]->_8 = intro;
        auto* main = new (heap) Unk_71024fdc88(this, "Part2", 2, &mInfo->mPart2WaitCountBase,
                                               &mInfo->mPart2WaitCountRate, &mInfo->mPart2Volume,
                                               &mInfo->mConstPan);
        mNodes.pushBack(main);
        intro->setNext(main);
        main->setNext(main);
    }

    mPartMachines[3] = new (heap) Unk_71024fdde8;
    if (mPartMachines[3]) {
        auto* intro = new (heap) Unk_71024fdc38(this, "Part3", 3, &params.mPart3FirstWaitCount,
                                                &mInfo->mPart3Volume, &mInfo->mPart3Pan);
        mNodes.pushBack(intro);
        mPartMachines[3]->_8 = intro;
        auto* main = new (heap) Unk_71024fdc88(this, "Part3", 3, &mInfo->mPart3WaitCountBase,
                                               &mInfo->mPart3WaitCountRate, &mInfo->mPart3Volume,
                                               &mInfo->mPart3Pan);
        mNodes.pushBack(main);
        intro->setNext(main);
        main->setNext(main);
    }

    for (auto* machine : mPartMachines) {
        if (machine)
            machine->start();
    }
}

Unk_71024fdde8::~Unk_71024fdde8() = default;

Unk_71024fdb98::Unk_71024fdb98(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                               const agl::utl::Parameter<u32>* wait_count,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : mOwner(owner), mPart(part), mWaitCount(wait_count), mVolume(volume),
      mPan(pan) {
    mName.append(name);
}

Unk_71024fdbe8::Unk_71024fdbe8(Unk_71024fdb00* owner, const sead::SafeString& name,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : mOwner(owner), mVolume(volume), mPan(pan) {
    mName.append(name);
}

Unk_71024fdc38::Unk_71024fdc38(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                               const agl::utl::Parameter<u32>* wait_count,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : mOwner(owner), mPart(part), mWaitCount(wait_count), mVolume(volume),
      mPan(pan) {
    mName.append(name);
}

Unk_71024fdc88::Unk_71024fdc88(Unk_71024fdb00* owner, const sead::SafeString& name, u8 part,
                               const agl::utl::Parameter<u32>* wait_count_base,
                               const MusicInfo::MinMax<u32>* wait_count_rate,
                               const MusicInfo::MinMax<f32>* volume, const MusicInfo::MinMax<f32>* pan)
    : mOwner(owner), mPart(part), mWaitCountBase(wait_count_base),
      mWaitCountRate(wait_count_rate), mVolume(volume), mPan(pan) {
    mName.append(name);
}

}  // namespace ksys::snd
