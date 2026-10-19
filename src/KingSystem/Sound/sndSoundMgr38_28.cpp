#include "KingSystem/Sound/sndSound.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <aal/aalDebugDrawUtil.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

Unk_SoundMgr38_28::~Unk_SoundMgr38_28() {
    sub_71010375CC();
}

void Unk_SoundMgr38_28::sub_7101037ED8(const sead::Vector3f* pos, const sead::Vector3f* size) {
    const sead::Vector3f half = *size * 0.5f;
    mBoxMin = *pos - half;
    mBoxMax = half + *pos;
    mBoxCenter = *pos;
    mBoxSize = *size;
}

void Unk_SoundMgr38_28::sub_7101037F5C(u8 value) {
    _344 = value;
}

void Unk_SoundMgr38_28::sub_7101037F64(bool enabled) {
    _328 = enabled;
    if (!enabled) {
        _3c8 = nullptr;
        _3c0 = nullptr;
    }
}

void Unk_SoundMgr38_28::sub_7101037F7C(bool value) {
    _39c = value;
}

void Unk_SoundMgr38_28::sub_7101039208() {}

Unk_SoundMgr38_38::~Unk_SoundMgr38_38() = default;

// Empty in the release build.
void Unk_SoundMgr38_38::sub_710103A034(sead::Heap* heap) {}

// Empty in the release build.
void Unk_SoundMgr38_38::sub_710103A294() {}

// NON_MATCHING: the box centre loads are scheduled in a different order (the compiler pairs
// mMin.y with mMax.x first); every value and the draw argument are the same.
// 0x7101039dd8 (placeholder name): draws the occlusion box in blue when _3d0 bit 0 is set.
void Unk_SoundMgr38_28::sub_7101039DD8(sead::DrawContext* context, const sead::Camera& camera,
                                       const sead::Projection& projection) {
    if (_3d0 == 0)
        return;
    if (_3d4) {
        sead::GraphicsContext gfx;
        gfx.setCullFace(2);
        gfx.setDepthTestEnable(true);
        gfx.setDepthWriteEnable(true);
        gfx.apply(context);
    }
    sead::PrimitiveDrawer drawer(context);
    aal::DebugDrawUtil::initializePrimitiveDrawer(&drawer, camera, projection);
    drawer.begin();
    if ((_3d0 & 1) != 0 && _328) {
        const sead::BoundBox3f box(mBoxMin, mBoxMax);
        const sead::Vector3f center = box.getCenter();
        const sead::Vector3f size(box.getSizeX(), box.getSizeY(), box.getSizeZ());
        drawer.drawWireCube(sead::PrimitiveDrawer::CubeArg(center, size, sead::Color4f::cBlue));
    }
    drawer.end();
}

// 0x710103920c (placeholder name): fades the four sound handles.
void Unk_SoundMgr38_28::sub_710103920C() {
    for (s32 i = 0; i < 2; ++i) {
        _1c0[i].fade();
        _1e0[i].fade();
    }
}

// 0x71010391ac (placeholder name): requests the "WaterObjSound" actor once and clears the
// occlusion state.
void Unk_SoundMgr38_28::sub_71010391AC(sead::Heap* heap, act::ActorCreator* creator) {
    if (!_18)
        creator->requestCreateActor("WaterObjSound", heap, &mProcHandle, nullptr, nullptr, 1);
    _39c = false;
    _3b8 = nullptr;
    _3b0 = nullptr;
    _3a8 = nullptr;
}

// 0x710103a038 (placeholder name): resets the handle, the three vectors and the unit scales.
// NON_MATCHING: the zero-vector stores are paired and scheduled differently (0x2c / 0x30 / 0x34
// are stored before 0x14 in ours); the value of every store is the same.
void Unk_SoundMgr38_38::sub_710103A038() {
    _8 = nullptr;
    _10 = 0;
    _14 = _20 = _2c = sead::Vector3f::zero;
    _38 = sead::Vector3f::zero;
    _44.set(1.0f, 1.0f, 1.0f);
    _50.reset();
    _cc = 0;
}

// 0x710103a084 (placeholder name): fades the three effect handles.
void Unk_SoundMgr38_38::sub_710103A084() {
    _60.fade();
    _70.fade();
    _80.fade();
}

}  // namespace ksys::snd
