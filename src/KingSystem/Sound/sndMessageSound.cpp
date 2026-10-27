#include "KingSystem/Sound/sndSound.h"
#include <cstring>
#include "KingSystem/Terrain/teraSystem.h"
#include <aal/aalArbiter.h>
#include <aal/aalEmitter.h>
#include <aal/aalSettings.h>
#include <aal/aalGroupMgr.h>
#include <aal/aalSoundSource.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include <aal/aalSystemAccessor.h>
#include <heap/seadHeap.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

// NON_MATCHING: the supplier is statically initialized; timing/string store layout differs.
// 0x7101055f00 uses the established timing model and these message-sound globals.
static util::InitTimeInfoEx sMessageSoundInitTimeInfo;
sead::SafeString sVoiceDefault = "VoiceDefault";
sead::SafeString sDemoDialog = "DemoDialog";
Unk_71025028c0 sMessageSpeakerBalance;


Unk_710105fe78::~Unk_710105fe78() {
    if (_8) {
        _8->freeBuffer();
        delete _8;
    }
}

Unk_SoundMgr48::Unk_SoundMgr48() = default;

Unk_SoundMgr48::~Unk_SoundMgr48() {
    if (_10) {
        if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
            arbiter->freeEmitter(_10);
            _10 = nullptr;
        }
    }
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
}


void Unk_SoundMgr48::sub_710105590C(sead::Heap* heap) {
    _8 = new (heap, 8) Unk_710105fe78;
    if (auto* arbiter = aal::SystemAccessor::getArbiter()) {
        _10 = arbiter->allocEmitter(nullptr, "Emitter");
        if (_10)
            _10->mSpatialSetting.setPositioned(false);
    }
}

// NON_MATCHING: string formatting, handle setup and register scheduling differ.
void Unk_SoundMgr48::sub_710105598C(const sead::SafeString& path,
                                   const sead::SafeString& name, s32 suffix,
                                   ksys::act::Actor* actor) {
    if (!_10)
        return;
    aal::AssetInfo info;
    bool found = false;
    if (suffix <= 0)
        found = _8->sub_7101060D14(&info, path, name);
    if (suffix >= 0 && !found) {
        static sead::FixedSafeString<64> numbered_name;
        numbered_name.format("%s_%d", name.cstr(), suffix);
        found = _8->sub_7101060D14(&info, path, numbered_name);
    }
    if (!found)
        return;
    if (_18.isEnabled())
        _18.stop(0.1f, 0.0f);
    aal::SoundSource::SetupInfo setup{};
    setup.prepare_flags = 3;
    if (auto* groups = aal::SystemAccessor::getGroupMgr())
        setup.sound_group = groups->findSoundGroupOrDefault(sDemoDialog);
    _18 = _10->emit(info, &setup, nullptr);
    sub_7101055B88(&_18, false, 0.0f);
}
// NON_MATCHING: source-state branches and parameter scheduling differ.
void Unk_SoundMgr48::sub_7101055B88(aal::Handle* handle, bool flag, f32 delay) {
    if (!handle->isEnabled())
        return;
    const u8 channels = handle->getAssetInfo()->getChannelNum();
    auto* source = handle->getSoundSource();
    if (source && source->mState != 0 && source->mState != 7) {
        if (channels >= 2) {
            source->setSpeakerBalanceSupplier(&sMessageSpeakerBalance);
        } else {
            source->mSpatialSetting.setPositioned(false);
            source->setInteriorNum(1);
            source->setChannelSpeakerType(0, 0, aal::SpeakerChannel::FrontCenter);
        }
    }
    handle->setVolume(0.708f);
    if (delay > 0.0f)
        handle->setStartDelayTime(delay);
}

}  // namespace ksys::snd

void Unk_7102504470::m7(void* vertices, void* indices) {
    mFlags |= 0x80000000;
    mVertices = vertices;
    mIndices = indices;
}

Unk_71025046d0::~Unk_71025046d0() = default;

Unk_7102504850::~Unk_7102504850() = default;

Unk_71025049d0::~Unk_71025049d0() = default;

s32 Unk_7102504850::m8() {
    return _60 * 10;
}

s32 Unk_7102504850::m9() {
    return _60 * 9;
}

s32 Unk_7102504850::m10() {
    return _20 * 20;
}

s32 Unk_7102504850::m11() {
    return mIndexCount * 4;
}

s32 Unk_71025049d0::m8() {
    return _60 * 10;
}

s32 Unk_71025049d0::m9() {
    return _60 * 9;
}

s32 Unk_71025049d0::m10() {
    return _20 * 20;
}

s32 Unk_71025049d0::m11() {
    return mIndexCount * 4;
}

namespace {
// Two {?, index} pairs shared by the tree draw commands (m21 / m22).
struct BufferPair {
    u32 a;
    u32 b;
};
const BufferPair sTreeBufferPairs[] = {{11, 0}, {12, 1}};

struct VertexAttribute {
    u32 type;
    u32 format;
    u16 offset;
    u32 buffer;
    const char* name;
};
struct Sampler {
    const char* name;
    u32 slot;
};
const Sampler sTreeSamplers[] = {
    {"tera_height", 0},      {"tera_grass", 1}, {"tera_normal", 2},
    {"grass_wind_swell", 3}, {"grass_mow", 4},  {"grass_lie", 5},
};

const VertexAttribute sTreeAttributes[] = {
    {42, 5377, 0, 0, "_p0"},
    {37, 2817, 8, 1, "_n0"},
    {37, 2817, 12, 2, "_t0"},
    {37, 2817, 16, 8, "_u0"},
};
}  // namespace

u32 Unk_7102504850::m14(s32 index) {
    return sTreeAttributes[index].type;
}

u16 Unk_7102504850::m15(s32 index) {
    return sTreeAttributes[index].offset;
}

u32 Unk_7102504850::m16(s32 index) {
    return sTreeAttributes[index].buffer;
}

const char* Unk_7102504850::m17(s32 index) {
    return sTreeAttributes[index].name;
}

u32 Unk_7102504850::m18(s32 index) {
    return sTreeAttributes[index].format;
}

u32 Unk_71025049d0::m14(s32 index) {
    return sTreeAttributes[index].type;
}

u16 Unk_71025049d0::m15(s32 index) {
    return sTreeAttributes[index].offset;
}

u32 Unk_71025049d0::m16(s32 index) {
    return sTreeAttributes[index].buffer;
}

const char* Unk_71025049d0::m17(s32 index) {
    return sTreeAttributes[index].name;
}

u32 Unk_71025049d0::m18(s32 index) {
    return sTreeAttributes[index].format;
}

const char* Unk_7102504850::m24(s32 index) {
    return sTreeSamplers[index].name;
}

u32 Unk_7102504850::m25(s32 index) {
    return sTreeSamplers[index].slot;
}

const char* Unk_71025049d0::m24(s32 index) {
    return sTreeSamplers[index].name;
}

u32 Unk_71025049d0::m25(s32 index) {
    return sTreeSamplers[index].slot;
}

u32 Unk_7102504850::m21(s32 index) {
    return sTreeBufferPairs[index].a;
}

u32 Unk_7102504850::m22(s32 index) {
    return sTreeBufferPairs[index].b;
}

u32 Unk_71025049d0::m21(s32 index) {
    return sTreeBufferPairs[index].a;
}

u32 Unk_71025049d0::m22(s32 index) {
    return sTreeBufferPairs[index].b;
}

const char* Unk_7102504850::m26() {
    return "DrawTree0__Tree0";
}

const char* Unk_7102504850::m27() {
    return "Tree0";
}

const char* Unk_71025049d0::m26() {
    return "DrawTree1__Tree1";
}

const char* Unk_71025049d0::m27() {
    return "Tree1";
}

namespace {
// Per-type count tables of the tree draw commands (bss 0x710261df90): two tables of [type][z][x].
u32 sUnk_710261DF90[2][2][8][10];
// Per-area sub-cell counts (bss 0x7102616760).
u32 sUnk_7102616760[2][8][10][16];
// Per-area sub-cell record offsets: exclusive prefix sums of sUnk_7102616760 (bss 0x7102618f60).
u32 sUnk_7102618F60[2][8][10][16];
// Per-area sub-cell counts of the added records (bss 0x710261b760).
u32 sUnk_710261B760[2][8][10][16];
// Per-area tree count limits of the two tree types (0x7101ec3644).
const u32 sTreeCountLimits[2][8][10] = {
    {
        {61, 24, 33, 22, 11, 269, 29, 67, 333, 389},
        {41, 94, 25, 109, 101, 983, 10, 10, 604, 374},
        {21, 24, 78, 66, 70, 681, 309, 37, 388, 143},
        {10, 43, 232, 157, 519, 429, 166, 60, 13, 53},
        {10, 156, 695, 296, 525, 859, 634, 232, 35, 10},
        {15, 10, 363, 461, 949, 1340, 178, 210, 134, 10},
        {22, 49, 31, 41, 80, 602, 395, 653, 356, 10},
        {10, 32, 10, 12, 188, 531, 453, 80, 27, 35},
    },
    {
        {58, 215, 62, 65, 12, 128, 10, 10, 61, 10},
        {139, 154, 166, 217, 26, 91, 11, 10, 91, 10},
        {47, 383, 165, 315, 283, 94, 10, 68, 10, 53},
        {10, 16, 10, 10, 76, 43, 29, 630, 253, 228},
        {10, 24, 152, 78, 10, 51, 10, 227, 169, 179},
        {17, 54, 37, 46, 21, 10, 10, 30, 264, 92},
        {10, 10, 10, 61, 104, 10, 104, 14, 10, 10},
        {10, 10, 10, 10, 36, 10, 10, 10, 10, 10},
    },
};

// Per-type data of the tree draw commands (0x71025045f0); m36 reads the record stride.
const u32 sUnk_7101EC38CC[] = {4, 2};
const u16 sUnk_7101EC38C4[] = {5, 3};
struct TreeTypeInfo {
    const u32* _0;
    const u16* stride;
};
const TreeTypeInfo sTreeTypes[] = {{sUnk_7101EC38CC, sUnk_7101EC38C4},
                                   {sUnk_7101EC38CC, sUnk_7101EC38C4}};

// A tree instance record in the vertex buffer: 16.16 position fractions in the cell, then a value.
struct TreeRecord {
    u16 x;
    u16 y;
    u16 z;
    u16 value;
    u8 _8[0x14 - 0x8];
};
static_assert(sizeof(TreeRecord) == 0x14);
}  // namespace

Unk_7102504470::Unk_7102504470(s32 type, u32 b) : _30(type), _34(b) {
    const u32 index = _30;
    for (s32 z = 0; z < 8; ++z) {
        for (s32 x = 0; x < 10; ++x) {
            sUnk_710261DF90[0][index][z][x] = 0;
            for (s32 i = 0; i < 16; ++i) {
                sUnk_7102616760[index][z][x][i] = 0;
                sUnk_7102618F60[index][z][x][i] = 0;
                sUnk_710261B760[index][z][x][i] = 0;
            }
        }
    }
    u32 total = 0;
    for (s32 z = 0; z < 8; ++z) {
        for (s32 x = 0; x < 10; ++x) {
            sUnk_710261DF90[1][index][z][x] = total;
            total += sTreeCountLimits[index][z][x];
        }
    }
    _60 = total;
    _5c = *sTreeTypes[type].stride * total;
}

void Unk_71025046d0::sub_7101084D04() {
    const u32 type = m28();
    for (s32 z = 0; z < 8; ++z) {
        for (s32 x = 0; x < 10; ++x) {
            sUnk_710261DF90[0][type][z][x] = 0;
            for (s32 i = 0; i < 16; ++i) {
                sUnk_7102616760[type][z][x][i] = 0;
                sUnk_7102618F60[type][z][x][i] = 0;
                sUnk_710261B760[type][z][x][i] = 0;
            }
        }
    }
}

void Unk_71025046d0::sub_7101084D9C(const sead::Vector3f& pos) {
    const u32 type = m28();
    const s32 ix = ksys::tera::sub_710107F9C4(pos.x);
    const s32 iz = ksys::tera::sub_710107FA0C(pos.z);
    const s32 sub = ksys::tera::sub_710107FA54(pos.x, pos.z);
    if (++sUnk_710261DF90[0][type][iz][ix] <= sTreeCountLimits[type][iz][ix])
        ++sUnk_7102616760[type][iz][ix][sub];
}

void Unk_71025046d0::sub_7101084E78() {
    const u32 type = m28();
    for (s32 z = 0; z < 8; ++z) {
        for (s32 x = 0; x < 10; ++x) {
            u32 offset = 0;
            for (s32 i = 0; i < 16; ++i) {
                sUnk_7102618F60[type][z][x][i] = offset;
                offset += sUnk_7102616760[type][z][x][i];
            }
        }
    }
}

void Unk_71025046d0::sub_7101084F6C() {
    std::memset(sUnk_710261DF90[0][m28()], 0, sizeof(sUnk_710261DF90[0][0]));
    m39();
}

// NON_MATCHING: instruction scheduling (the original loads all three offsets before the two increments).
s32 Unk_71025046d0::sub_7101084FB8(const sead::Vector3f& pos, const sead::Vector3f& a,
                                   const sead::Vector3f& rotate, u32 b, u32 c, f32 scale) {
    const u32 type = m28();
    const s32 ix = ksys::tera::sub_710107F9C4(pos.x);
    const s32 iz = ksys::tera::sub_710107FA0C(pos.z);
    const s32 sub = ksys::tera::sub_710107FA54(pos.x, pos.z);
    if (sUnk_710261DF90[0][type][iz][ix] >= sTreeCountLimits[type][iz][ix])
        return -1;
    const s32 index = sUnk_710261DF90[1][type][iz][ix] + sUnk_7102618F60[type][iz][ix][sub] +
                      sUnk_710261B760[type][iz][ix][sub];
    ++sUnk_710261DF90[0][type][iz][ix];
    ++sUnk_710261B760[type][iz][ix][sub];
    m40(pos, a, rotate, b, c, index, ix, iz, std::max(scale, 0.0f));
    return index;
}

// Discarded call: the original calls slot 28 and drops the result.
void Unk_71025046d0::sub_710108515C(void* arg) {
    m28();
    m41(arg);
}

void Unk_71025046d0::sub_7101085198(s32 value) {
    _58 = value;
    m43();
}

// 0x7101086d60: the value of tree record `index` in the cell at pos, or -1 if the record is not at pos.
// NON_MATCHING: register allocation (the original reloads the record address for the value and
// hoists the constant 2); 12 bytes shorter.
f32 Unk_71025046d0::m36(u32 index, const sead::Vector3f& pos) {
    const u32 type = m28();
    const s32 ix = ksys::tera::sub_710107F9C4(pos.x);
    const s32 iz = ksys::tera::sub_710107FA0C(pos.z);
    if (index >= sUnk_710261DF90[1][type][iz][ix] + sUnk_710261DF90[0][type][iz][ix])
        return -1.0f;

    const f32 fx = pos.x / 1000.0f - (ix - 5);
    const f32 fz = pos.z / 1000.0f - (iz - 4);
    if (fx < 0.0f || fx >= 1.0f || fz < 0.0f || fz >= 1.0f)
        return -1.0f;

    const u32 i = *sTreeTypes[type].stride * index;
    const auto* records = static_cast<const TreeRecord*>(mVertices) + u32(_58 * _5c);
    // Whether a 16.16 fixed-point record coordinate is within 2 of `coord`.
    const auto is_near = [](u16 value, f32 coord) {
        const s32 diff = value - s32(coord * 65536.0f);
        return diff >= -2 && diff <= 2;
    };
    const TreeRecord& record = records[i];
    if (!is_near(record.x, fx) || !is_near(record.y, pos.y / 1000.0f) || !is_near(record.z, fz)) {
        return -1.0f;
    }
    return records[i].value;
}

u32 Unk_71025046d0::m42() {
    return m28();
}

u32 Unk_71025046d0::m28() {
    return _30;
}

u32 Unk_71025046d0::m29() {
    return _34;
}

bool Unk_71025046d0::m30() {
    return _30a8 > 2037;
}

s32 Unk_71025046d0::m31() {
    return 0x800;
}

s32 Unk_71025046d0::m32() {
    return _30a8;
}

// Unk_71025028c0 sits after the Unk_SoundMgr48 functions (0x7101055e48) in the original.
Unk_71025028c0::~Unk_71025028c0() = default;

// NON_MATCHING: clang merges the left / right stores into indexed stores; the original keeps the branches (likely
// named channel members in SpeakerChannelVolume, which lib/aal declares as an array).
void Unk_71025028c0::calcSpeakerBalance(aal::SpeakerChannelVolume* volume, aal::DeviceType device,
                                        s32 index_a, s32 index_b, f32 spread) {
    if (aal::SystemAccessor::getSettings()->mOutputModes[device] == aal::OutputMode::Surround) {
        const f32 rear = _c * ksys::snd::SoundMgr::instance()->sub_71011FC310();
        const f32 front = _8 * spread;
        if (index_b) {
            volume->volume[1] = front;
            volume->volume[3] = rear * spread;
        } else {
            volume->volume[0] = front;
            volume->volume[2] = rear * spread;
        }
    } else if (index_b) {
        volume->volume[1] = spread;
    } else {
        volume->volume[0] = spread;
    }
}
