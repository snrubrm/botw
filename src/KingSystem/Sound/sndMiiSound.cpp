#include "KingSystem/Sound/sndMiiSound.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Mii/miiUMii.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/System/Timer.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySphere.h"
#include "KingSystem/Physics/RigidBody/Shape/physSphereShape.h"
#include "Game/gameNavMeshSystem.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::snd {

// Initialized by 0x71012ce620, followed by the four SafeString objects below.
// NON_MATCHING: the compiler places the initialization record after the strings in GlobalMerge.
static util::InitTimeInfoEx sMiiSoundInitTimeInfo;
static sead::SafeString sVoiceDirectory = "Voice/";
static sead::SafeString sCommonVoiceDirectory = "Voice/Common/";
static sead::SafeString sVoicePrefix = "NV_";
static sead::SafeString sCustomVoicePrefix = "Custom_";

Unk_710251b6f0::Unk_710251b6f0() {
    mPendingName.clear();
}

Unk_710251b6f0::~Unk_710251b6f0() {
    auto& requests = SoundMgr::instance()->_60->mMiiSoundRequests;
    auto lock = sead::makeScopedLock(requests.mCS);
    requests.mQueue.erase(this);
}

void Unk_710251b6f0::sub_71012CD614() {
    if (mHandle.requestedLoad() && mHandle.isReadyOrNeedsParse() && mHandle.parseResource(nullptr)) {
        auto* resource = sead::DynamicCast<ResourceBars>(mHandle.getResource());
        if (mHandle.isSuccess() && resource) {
            sead::FixedSafeString<64> path;
            path.format("%s.bars", mName.cstr());
            resource->sub_7101057588(path);
            if (!mPendingName.isEmpty())
                mState = 1;
        }
    }
    Timer::update(&mTimer, 1.0f);
}

void Unk_710251b6f0::sub_71012CD7A4() {
    mTimer = 0.0f;
    _119 = false;
    _11a = false;
    mPendingName.clear();
    if (sub_71012CD880(mName, mIsCustomVoice)) {
        auto& requests = SoundMgr::instance()->_60->mMiiSoundRequests;
        requests.mQueue.push(this);
        _114 = requests.mCounter;
        if (mHandle.isSuccess())
            mState = 0;
    }
}

// NON_MATCHING: the static prefix string has a different GlobalMerge offset.
void Unk_710251b6f0::sub_71012CD4E8(sead::Heap*, mii::UMii* umii) {
    mName.clear();
    if (umii->getPersonal().voice_type.ref() == "None") {
        mState = 2;
    } else {
        mName.appendWithFormat("NV_%s", umii->getPersonal().voice_type.ref().cstr());
        mIsCustomVoice = umii->getPersonal().voice_type.ref().startsWith(sCustomVoicePrefix);
    }
}

// NON_MATCHING: the directory strings have different GlobalMerge offsets.
bool Unk_710251b6f0::sub_71012CD880(const sead::SafeString& name, bool is_custom_voice) {
    sead::FixedSafeString<128> path;
    if (is_custom_voice) {
        const char* directory = sVoiceDirectory.cstr();
        const char* locale = sub_710105E7B4(nullptr);
        path.format("%s%s/%s.bars", directory, locale, name.cstr());
    } else {
        path.format("%s%s.bars", sCommonVoiceDirectory.cstr(), name.cstr());
    }
    res::LoadRequest request;
    request.mLoadDataAlignment = 0x1000;
    request.mRequester = "Sound";
    request._22 = true;
    request.mLaneId = 2;
    request.mArena = SoundMgr::instance()->_60->mArena;
    return mHandle.requestLoad(path, &request);
}

// NON_MATCHING: the static prefix string has a different GlobalMerge offset.
bool Unk_710251b6f0::sub_71012CDA58(const sead::SafeString& name) const {
    if (mState == 2)
        return false;
    return name.startsWith(sVoicePrefix);
}

void Unk_710251b6f0::requestUnloadMaybe() {
    mHandle.requestUnload();
    mState = 0;
}

Unk_710251b710::Unk_710251b710() = default;

Unk_710251b710::~Unk_710251b710() {
    mQueue.freeBuffer();
}

void Unk_710251b710::sub_71012CDF98(sead::Heap* heap) {
    mQueue.alloc(16, heap);
}

void Unk_710251b710::sub_71012CE054() {}

void Unk_710251b710::sub_71012CE058() {
    mQueue.clear();
}

// NON_MATCHING: the list sentinel and sound name addresses are scheduled in a different order.
bool Unk_710251b710::sub_71012CE4D8(Unk_710251b6f0* sound) {
    if (sound->_114 == mCounter)
        return false;
    sound->_114 = mCounter;
    for (const auto& name : mNames) {
        if (name == sound->mName)
            return false;
    }
    return true;
}

}  // namespace ksys::snd

Unk_710251ba58::~Unk_710251ba58() = default;

// NON_MATCHING: the original zeroes the last buffer with one 16-byte store (stp xzr, xzr at 0x78).
// NON_MATCHING: the original clears the last buffer with one 16-byte store (its size field may be 64-bit).
Unk_710251bb98::~Unk_710251bb98() {
    _38.freeBuffer();
    _48.freeBuffer();
    _58.freeBuffer();
    _68.freeBuffer();
    _78.freeBuffer();
}

Unk_710251bf80::~Unk_710251bf80() = default;

Unk_710251c0b8::~Unk_710251c0b8() = default;

Unk_710251c1f0::~Unk_710251c1f0() = default;

Unk_710251c328::~Unk_710251c328() = default;

Unk_710251c460::~Unk_710251c460() = default;

Unk_710251c598::~Unk_710251c598() = default;

Unk_710251c6d0::~Unk_710251c6d0() = default;

Unk_710251c808::~Unk_710251c808() = default;

Unk_710251c940::~Unk_710251c940() = default;

Unk_710251ca78::~Unk_710251ca78() = default;

namespace {
// Per-part vertex / index counts of the draw commands (two parts each).
struct PartCounts {
    u16 vertices;
    u16 indices;
};
const PartCounts sBf80Parts[] = {{3, 1}, {3, 1}};

// Two {?, index} pairs shared by the grass draw commands (m21 / m22).
struct BufferPair {
    u32 a;
    u32 b;
};
const BufferPair sGrassBufferPairs[] = {{4, 0}, {5, 1}};

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
const Sampler sGrassSamplers[] = {
    {"grass_wind_swell", 0}, {"grass_mow", 1},      {"grass_mow_wide", 2},
    {"grass_lie", 3},        {"grass_summary0", 4}, {"_a0", 5},
};

const VertexAttribute sTurfAttributes[] = {
    {37, 2817, 0, 0, "_p0"},
    {38, 2818, 4, 1, "_n0"},
};
const VertexAttribute sStoneAttributes[] = {
    {37, 2817, 0, 0, "_p0"},
    {37, 2817, 4, 1, "_n0"},
    {38, 2818, 8, 2, "_t0"},
};
const VertexAttribute sGrassAttributes[] = {
    {37, 2817, 0, 0, "_p0"},
    {38, 2818, 4, 1, "_n0"},
    {37, 2817, 8, 2, "_t0"},
};
const PartCounts sC0b8Parts[] = {{4, 2}, {4, 2}};
const PartCounts sC1f0Parts[] = {{5, 4}, {5, 4}};
const PartCounts sC328Parts[] = {{4, 2}, {4, 2}};
const PartCounts sC460Parts[] = {{4, 2}, {4, 2}};
const PartCounts sC598Parts[] = {{12, 20}, {12, 20}};
const PartCounts sC6d0Parts[] = {{5, 3}, {6, 4}};
const PartCounts sC808Parts[] = {{5, 3}, {6, 4}};
const PartCounts sC940Parts[] = {{5, 4}, {5, 4}};
const PartCounts sCa78Parts[] = {{8, 6}, {8, 6}};
}  // namespace

// NON_MATCHING: the original loads the part's vertex count before the m29() call.
s32 Unk_710251bf80::m8() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i) {
        const s32 type = m29();
        total += sBf80Parts[i].vertices * (type == 7 || type == 0 ? 2 : 1) * 6400;
    }
    return total;
}

s32 Unk_710251bf80::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sBf80Parts[i].indices * 19200;
    return total;
}

s32 Unk_710251c0b8::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC0b8Parts[i].indices * 1728;
    return total;
}

s32 Unk_710251c1f0::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC1f0Parts[i].indices * 3072;
    return total;
}

s32 Unk_710251c328::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC328Parts[i].indices * 3072;
    return total;
}

s32 Unk_710251c460::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC460Parts[i].indices * 3072;
    return total;
}

s32 Unk_710251c598::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC598Parts[i].indices * 768;
    return total;
}

s32 Unk_710251c6d0::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC6d0Parts[i].indices * 3072;
    return total;
}

s32 Unk_710251c808::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC808Parts[i].indices * 3072;
    return total;
}

s32 Unk_710251c940::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sC940Parts[i].indices * 192;
    return total;
}

s32 Unk_710251ca78::m9() {
    s32 total = 0;
    for (s32 i = 0; i < m13(); ++i)
        total += sCa78Parts[i].indices * 768;
    return total;
}

// Grass draw commands: shader and model names, and the inverse of the vertex budget.
const char* Unk_710251bf80::m26() {
    return "DrawTurf__Turf";
}

const char* Unk_710251bf80::m27() {
    return "Turf";
}

f32 Unk_710251bf80::m28() {
    return 1.0f / 6400.0f;
}

const char* Unk_710251c0b8::m26() {
    return "DrawCross__Cross";
}

const char* Unk_710251c0b8::m27() {
    return "Cross";
}

f32 Unk_710251c0b8::m28() {
    return 1.0f / 576.0f;
}

const char* Unk_710251c1f0::m26() {
    return "DrawPetal__Petal";
}

const char* Unk_710251c1f0::m27() {
    return "Petal";
}

f32 Unk_710251c1f0::m28() {
    return 1.0f / 1024.0f;
}

const char* Unk_710251c328::m26() {
    return "DrawNormal__Normal";
}

const char* Unk_710251c328::m27() {
    return "Normal";
}

f32 Unk_710251c328::m28() {
    return 1.0f / 1024.0f;
}

const char* Unk_710251c460::m26() {
    return "DrawLong__Long";
}

const char* Unk_710251c460::m27() {
    return "Long";
}

f32 Unk_710251c460::m28() {
    return 1.0f / 1024.0f;
}

const char* Unk_710251c598::m26() {
    return "DrawStone__Stone";
}

const char* Unk_710251c598::m27() {
    return "Stone";
}

f32 Unk_710251c598::m28() {
    return 1.0f / 256.0f;
}

const char* Unk_710251c6d0::m26() {
    return "DrawFallenLeaves__FallenLeaves";
}

const char* Unk_710251c6d0::m27() {
    return "FallenLeaves";
}

f32 Unk_710251c6d0::m28() {
    return 1.0f / 1024.0f;
}

const char* Unk_710251c808::m26() {
    return "DrawFallenLeavesWater__FallenLeavesWater";
}

const char* Unk_710251c808::m27() {
    return "FallenLeavesWater";
}

f32 Unk_710251c808::m28() {
    return 1.0f / 1024.0f;
}

const char* Unk_710251c940::m26() {
    return "DrawShell__Shell";
}

const char* Unk_710251c940::m27() {
    return "Shell";
}

f32 Unk_710251c940::m28() {
    return 1.0f / 64.0f;
}

const char* Unk_710251ca78::m26() {
    return "DrawChips__Chips";
}

const char* Unk_710251ca78::m27() {
    return "Chips";
}

f32 Unk_710251ca78::m28() {
    return 1.0f / 256.0f;
}

u32 Unk_710251bf80::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251bf80::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c0b8::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c0b8::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c1f0::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c1f0::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c328::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c328::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c460::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c460::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c598::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c598::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c6d0::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c6d0::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c808::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c808::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251c940::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251c940::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251ca78::m21(s32 index) {
    return sGrassBufferPairs[index].a;
}

u32 Unk_710251ca78::m22(s32 index) {
    return sGrassBufferPairs[index].b;
}

u32 Unk_710251bf80::m15(s32 index) {
    return sTurfAttributes[index].type;
}

u16 Unk_710251bf80::m16(s32 index) {
    return sTurfAttributes[index].offset;
}

u32 Unk_710251bf80::m17(s32 index) {
    return sTurfAttributes[index].buffer;
}

const char* Unk_710251bf80::m18(s32 index) {
    return sTurfAttributes[index].name;
}

u32 Unk_710251bf80::m19(s32 index) {
    return sTurfAttributes[index].format;
}

const char* Unk_710251c0b8::m18(s32 index) {
    return "_p0";
}

u32 Unk_710251c1f0::m15(s32 index) {
    return sGrassAttributes[index].type;
}

u16 Unk_710251c1f0::m16(s32 index) {
    return sGrassAttributes[index].offset;
}

u32 Unk_710251c1f0::m17(s32 index) {
    return sGrassAttributes[index].buffer;
}

const char* Unk_710251c1f0::m18(s32 index) {
    return sGrassAttributes[index].name;
}

u32 Unk_710251c1f0::m19(s32 index) {
    return sGrassAttributes[index].format;
}

u32 Unk_710251c328::m15(s32 index) {
    return sGrassAttributes[index].type;
}

u16 Unk_710251c328::m16(s32 index) {
    return sGrassAttributes[index].offset;
}

u32 Unk_710251c328::m17(s32 index) {
    return sGrassAttributes[index].buffer;
}

const char* Unk_710251c328::m18(s32 index) {
    return sGrassAttributes[index].name;
}

u32 Unk_710251c328::m19(s32 index) {
    return sGrassAttributes[index].format;
}

u32 Unk_710251c460::m15(s32 index) {
    return sGrassAttributes[index].type;
}

u16 Unk_710251c460::m16(s32 index) {
    return sGrassAttributes[index].offset;
}

u32 Unk_710251c460::m17(s32 index) {
    return sGrassAttributes[index].buffer;
}

const char* Unk_710251c460::m18(s32 index) {
    return sGrassAttributes[index].name;
}

u32 Unk_710251c460::m19(s32 index) {
    return sGrassAttributes[index].format;
}

u32 Unk_710251c598::m15(s32 index) {
    return sStoneAttributes[index].type;
}

u16 Unk_710251c598::m16(s32 index) {
    return sStoneAttributes[index].offset;
}

u32 Unk_710251c598::m17(s32 index) {
    return sStoneAttributes[index].buffer;
}

const char* Unk_710251c598::m18(s32 index) {
    return sStoneAttributes[index].name;
}

u32 Unk_710251c598::m19(s32 index) {
    return sStoneAttributes[index].format;
}

u32 Unk_710251c6d0::m15(s32 index) {
    return sGrassAttributes[index].type;
}

u16 Unk_710251c6d0::m16(s32 index) {
    return sGrassAttributes[index].offset;
}

u32 Unk_710251c6d0::m17(s32 index) {
    return sGrassAttributes[index].buffer;
}

const char* Unk_710251c6d0::m18(s32 index) {
    return sGrassAttributes[index].name;
}

u32 Unk_710251c6d0::m19(s32 index) {
    return sGrassAttributes[index].format;
}

u32 Unk_710251c808::m15(s32 index) {
    return sGrassAttributes[index].type;
}

u16 Unk_710251c808::m16(s32 index) {
    return sGrassAttributes[index].offset;
}

u32 Unk_710251c808::m17(s32 index) {
    return sGrassAttributes[index].buffer;
}

const char* Unk_710251c808::m18(s32 index) {
    return sGrassAttributes[index].name;
}

u32 Unk_710251c808::m19(s32 index) {
    return sGrassAttributes[index].format;
}

u32 Unk_710251c940::m15(s32 index) {
    return sGrassAttributes[index].type;
}

u16 Unk_710251c940::m16(s32 index) {
    return sGrassAttributes[index].offset;
}

u32 Unk_710251c940::m17(s32 index) {
    return sGrassAttributes[index].buffer;
}

const char* Unk_710251c940::m18(s32 index) {
    return sGrassAttributes[index].name;
}

u32 Unk_710251c940::m19(s32 index) {
    return sGrassAttributes[index].format;
}

u32 Unk_710251ca78::m15(s32 index) {
    return sGrassAttributes[index].type;
}

u16 Unk_710251ca78::m16(s32 index) {
    return sGrassAttributes[index].offset;
}

u32 Unk_710251ca78::m17(s32 index) {
    return sGrassAttributes[index].buffer;
}

const char* Unk_710251ca78::m18(s32 index) {
    return sGrassAttributes[index].name;
}

u32 Unk_710251ca78::m19(s32 index) {
    return sGrassAttributes[index].format;
}

const char* Unk_710251bf80::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251bf80::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c0b8::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c0b8::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c1f0::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c1f0::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c328::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c328::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c460::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c460::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c598::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c598::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c6d0::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c6d0::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c808::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c808::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251c940::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251c940::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

const char* Unk_710251ca78::m24(s32 index) {
    return sGrassSamplers[index].name;
}

u32 Unk_710251ca78::m25(s32 index) {
    return sGrassSamplers[index].slot;
}

// NON_MATCHING: the original sign-extends `part` before the 0 / 1 test (64-bit compare).
void Unk_710251bf80::m33(u16* indices, s32 part, u16 base) {
    if (part == 0 || part == 1) {
        u32 i = 0;
        do {
            *indices++ = base + i;
            *indices++ = base + i + 1;
            *indices++ = base + i + 2;
        } while (++i < sBf80Parts[part].indices);
    }
}

// NON_MATCHING: same as Unk_710251bf80::m33 (64-bit part test).
void Unk_710251ca78::m33(u16* indices, s32 part, u16 base) {
    if (part == 0 || part == 1) {
        u32 i = 0;
        do {
            *indices++ = base + i;
            *indices++ = base + i + 1;
            *indices++ = base + i + 2;
        } while (++i < sCa78Parts[part].indices);
    }
}

// Draw-command counts: m10 is the vertex count times the per-vertex count of slot 12,
// m11 twice the index count.
s32 Unk_710251bf80::m10() {
    return m12() * _20;
}

s32 Unk_710251bf80::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c0b8::m10() {
    return m12() * _20;
}

s32 Unk_710251c0b8::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c1f0::m10() {
    return m12() * _20;
}

s32 Unk_710251c1f0::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c328::m10() {
    return m12() * _20;
}

s32 Unk_710251c328::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c460::m10() {
    return m12() * _20;
}

s32 Unk_710251c460::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c598::m10() {
    return m12() * _20;
}

s32 Unk_710251c598::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c6d0::m10() {
    return m12() * _20;
}

s32 Unk_710251c6d0::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c808::m10() {
    return m12() * _20;
}

s32 Unk_710251c808::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251c940::m10() {
    return m12() * _20;
}

s32 Unk_710251c940::m11() {
    return mIndexCount * 2;
}

s32 Unk_710251ca78::m10() {
    return m12() * _20;
}

s32 Unk_710251ca78::m11() {
    return mIndexCount * 2;
}


Unk_710251cbf0::~Unk_710251cbf0() {
    if (_50) {
        delete _50;
        _50 = nullptr;
    }
    _60.fade();
    if (auto* nav_mesh_system = uking::NavMeshSystem::instance())
        nav_mesh_system->sub_7100E8F1C0(&_48->_c, _58, 1.5f);
}

f32 Unk_710251cbf0::m13(f32* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) {
    *out = 1.0f;
    return mHolder->_30;
}

// Fire strength: rises with the burn progress, peaks at 1.6 and falls off again.
f32 Unk_710251cbf0::m16() {
    f32 t = sead::Mathf::clamp(_48->_30 - 1.0f, 0.0f, 1.0f) / 0.6f;
    t = t < 1.0f ? t : 2.0f - t;
    return (1.0f - _48->_34) * t;
}

void Unk_710251cbf0::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

f32 Unk_710251cd38::m13(f32* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) {
    const f32 distance = (pos - m6()).length() - 1.0f;
    f32 value = 1.0f;
    if (distance > 1.0f)
        value = 1.0f / (distance * distance);
    *out = value;
    return mHolder->_30;
}

f32 Unk_710251cd38::m14(sead::Vector3f* out, const sead::Vector3f& pos, ksys::act::Chemical* chemical) {
    out->e = mHolder->_1c.e;
    return mHolder->_3c;
}

Unk_710251cd38::~Unk_710251cd38() {
    if (_50) {
        delete _50;
        _50 = nullptr;
    }
}

// NON_MATCHING: scheduling of the matrix stores (same as ElementLightningFire::m29).
bool Unk_710251cd38::m29(const ElementName& name, sead::Heap* heap) {
    ksys::phys::SphereParam param;
    param.name = "GrassFireWarm(Sphere)";
    param.contact_layer = ksys::phys::ContactLayer::SensorChemicalElement;
    param.radius = 6.0f;
    param.motion_type = ksys::phys::MotionType::Keyframed;
    _50 = ksys::phys::SphereRigidBody::make(&param, heap);
    if (!_50)
        return false;
    sead::Matrix34f mtx;
    mtx.makeT(_48->_c);
    _50->setTransform(mtx, ksys::phys::PropagateToLinkedMotions(true));
    setRigidBody(_50, true);
    return true;
}

void Unk_710251cd38::m35(f32 delta_frame) {
    if (!_50)
        return;
    f32 t = sead::Mathf::clamp(_48->_30 - 1.0f, 0.0f, 1.0f) / 0.6f;
    t = t < 1.0f ? t : 2.0f - t;
    f32 radius = std::max((1.0f - _48->_34) * t, 0.3f) * 6.0f;
    radius = std::max(radius, 0.01f);
    static_cast<ksys::phys::SphereRigidBody*>(_50)->setRadius(radius);
}

void Unk_710251cd38::m33(bool a, bool fixed) {
    if (_50)
        _50->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
}

// NON_MATCHING: the original passes the address of the (not yet constructed) local `name` to the base
// constructor, so no temporary ElementName is built there.
Unk_710251cbf0::Unk_710251cbf0(void* arg, sead::Heap* heap) : Unk_7102518688(ElementName(), heap, false) {
    _48 = static_cast<Unk_710251cbf0Arg*>(arg);
    ElementName name;
    name.mName = "grass_fire";
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());
}

Unk_710251cbf0* ksys::act::Unk_71024dd490::sub_71012DF1A0(void* arg) {
    auto* chemical = ksys::chm::Chemical::instance();
    if (!chemical)
        return nullptr;
    sead::Heap* parent = chemical->_78;
    if (!parent)
        return nullptr;

    sead::ScopedLock<sead::CriticalSection> lock(&chemical->_28);
    auto* heap = sead::ExpHeap::tryCreate(0x2000, "ElementHolder", parent, 8,
                                          sead::Heap::cHeapDirection_Forward, true);
    if (!heap) {
        if (!(chemical->_84 & 4))
            elementEmitMaybe();
        return nullptr;
    }
    auto* element = new (parent, std::nothrow_t()) Unk_710251cbf0(arg, heap);
    if (!element) {
        elementEmitMaybe();
        heap->destroy();
        return nullptr;
    }
    if (mMaxElementHeapSize < heap->getSize())
        mMaxElementHeapSize = heap->getSize();
    if (!element->mHolder) {
        elementEmitMaybe();
        element->m32();
        delete element;
        return nullptr;
    }
    return element;
}

// NON_MATCHING: the original passes the address of the (not yet constructed) local `name` to the base
// constructor, so no temporary ElementName is built there.
Unk_710251cd38::Unk_710251cd38(void* arg, sead::Heap* heap) : Unk_7102518688(ElementName(), heap, false) {
    _48 = static_cast<Unk_710251cbf0Arg*>(arg);
    ElementName name;
    name.mName = "grass_fire_warm";
    name._28 = 2;
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());
}

Unk_710251cd38* ksys::act::Unk_71024dd490::sub_71012DF384(void* arg) {
    auto* chemical = ksys::chm::Chemical::instance();
    if (!chemical)
        return nullptr;
    sead::Heap* parent = chemical->_78;
    if (!parent)
        return nullptr;

    sead::ScopedLock<sead::CriticalSection> lock(&chemical->_28);
    auto* heap = sead::ExpHeap::tryCreate(0x2000, "ElementHolder", parent, 8,
                                          sead::Heap::cHeapDirection_Forward, true);
    if (!heap) {
        if (!(chemical->_84 & 4))
            elementEmitMaybe();
        return nullptr;
    }
    auto* element = new (parent, std::nothrow_t()) Unk_710251cd38(arg, heap);
    if (!element) {
        elementEmitMaybe();
        heap->destroy();
        return nullptr;
    }
    if (mMaxElementHeapSize < heap->getSize())
        mMaxElementHeapSize = heap->getSize();
    if (!element->mHolder) {
        elementEmitMaybe();
        element->m32();
        delete element;
        return nullptr;
    }
    return element;
}

// NON_MATCHING: placeholder destructor; the original (0x71012e86e8) also destroys members or bases
// this class does not declare yet.
Unk_710251cf40::~Unk_710251cf40() = default;

namespace {
struct ShapeCounts {
    s32 vertices;
    s32 _4;
    s32 indices;
};
const ShapeCounts sShapeCounts[] = {{3, 1, 3}, {4, 2, 6}, {4, 2, 6}, {5, 3, 9}, {6, 4, 12}};
}  // namespace

s32 Unk_710251cf40::m8() {
    return _30 * _30 * sShapeCounts[_34].vertices;
}

s32 Unk_710251cf40::m9() {
    return _30 * _30 * sShapeCounts[_34].indices * 10;
}

Unk_710251b810::~Unk_710251b810() = default;

Unk_710251b888::~Unk_710251b888() = default;

Unk_710251b900::~Unk_710251b900() = default;

Unk_710251b978::~Unk_710251b978() = default;

Unk_710251b9f0::~Unk_710251b9f0() = default;
