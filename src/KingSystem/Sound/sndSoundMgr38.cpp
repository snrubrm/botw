#include "KingSystem/Sound/sndSound.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Utils/InitTimeInfo.h"
#include "Game/Actor/actEnvSeEmitPoint.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Terrain/teraSystem.h"
#include <prim/seadScopedLock.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include "Game/gameUnkRttiPlaceholders.h"

namespace ksys::snd {

Unk_SoundMgr38::Unk_SoundMgr38() = default;

Unk_SoundMgr38::~Unk_SoundMgr38() {
    if (_8) {
        delete _8;
        _8 = nullptr;
    }
    if (_10) {
        delete _10;
        _10 = nullptr;
    }
    if (_18) {
        delete _18;
        _18 = nullptr;
    }
    if (_20) {
        delete _20;
        _20 = nullptr;
    }
    if (_80) {
        SoundMgr::instance()->_60->sub_7101059354(_80);
        if (_68)
            _68->setAssetInfoReader(nullptr);
        _80 = nullptr;
        _88 = 0;
    }
    if (_68) {
        _68->destroy();
        _68 = nullptr;
    }
    if (_28) {
        delete _28;
        _28 = nullptr;
    }
    if (_30) {
        delete _30;
        _30 = nullptr;
    }
    if (_38) {
        delete _38;
        _38 = nullptr;
    }
    if (_40) {
        delete _40;
        _40 = nullptr;
    }
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    if (_50) {
        delete _50;
        _50 = nullptr;
    }
    if (_58) {
        delete _58;
        _58 = nullptr;
    }
    if (_60) {
        delete _60;
        _60 = nullptr;
    }
    _138 = nullptr;
}

void Unk_SoundMgr38::init(sead::Heap* heap) {
    _8 = new (heap) Unk_SoundMgr38_8;
    _8->sub_710102C388(heap);
    _10 = new (heap) Unk_SoundMgr38_10;
    _10->sub_71010317B4(heap);
    _18 = new (heap) Unk_SoundMgr38_18;
    _18->sub_710102D9C0(heap);
    _20 = new (heap) Unk_SoundMgr38_20;
    _20->sub_7101029958(heap);
    _30 = new (heap) SpeakerBalanceUnifierMgr;
    _30->sub_71010276F0(heap);
    _38 = new (heap) Unk_SoundMgr38_38;
    _38->sub_710103A034(heap);
    _40 = new (heap) Unk_SoundMgr38_40;
    _40->sub_71012BE5F4(heap);
    _70 = false;
}

void Unk_SoundMgr38::sub_710102AE50() {
    if (_70) {
        if (_8)
            _8->sub_710102C810();
        if (_10)
            _10->sub_71010333E0();
        if (_18)
            _18->sub_710102EE40();
    }
    if (_28)
        _28->sub_7101039208();
    if (_30)
        _30->sub_7101027BF4();
    if (_48)
        _48->sub_7101035A50();
}

void Unk_SoundMgr38::sub_710102AEC4() {
    if (_70) {
        if (_8)
            _8->sub_710102C81C();
        if (_10)
            _10->sub_71010333F0();
        if (_18)
            _18->sub_710102EE60();
    }
    if (_20)
        _20->sub_7101029BA0();
    if (_28)
        _28->sub_710103920C();
    if (_30)
        _30->sub_7101027BF8();
    if (_68)
        _68->stopAllEvent(30);
    if (_38)
        _38->sub_710103A084();
    if (_40)
        _40->sub_71012BEC28();
    if (_50)
        _50->sub_7101036840();
    if (_58)
        _58->sub_71010289CC();
    if (_60)
        _60->sub_71012C17B4();
}

void Unk_SoundMgr38::sub_710102AF84() {
    if (_70) {
        if (_8)
            _8->sub_710102C8F8();
        if (_10)
            _10->sub_710103362C();
        if (_18)
            _18->sub_710102EFFC();
    }
    if (_20)
        _20->sub_7101029BA8();
    if (_28)
        _28->sub_710103937C();
    if (_30)
        _30->sub_7101027CE8();
    if (_38)
        _38->sub_710103A294();
    if (_40)
        _40->sub_71012BED18();
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    if (_50) {
        _50->sub_7101036A68();
        delete _50;
        _50 = nullptr;
    }
    if (_58) {
        _58->sub_7101028690();
        delete _58;
        _58 = nullptr;
    }
    if (_60) {
        _60->sub_71012C167C();
        delete _60;
        _60 = nullptr;
    }
    if (_28) {
        _28->sub_710103937C();
        _28->sub_71010375CC();
        delete _28;
        _28 = nullptr;
    }
    if (_80) {
        SoundMgr::instance()->_60->sub_7101059354(_80);
        if (_68)
            _68->setAssetInfoReader(nullptr);
        _80 = nullptr;
        _88 = 0;
    }
    if (_68) {
        _68->destroy();
        _68 = nullptr;
    }
    _98 = 0;
    _a0 = 0;
    _138 = nullptr;
}

// NON_MATCHING: local vector and terrain-height stack layout differs.
void Unk_SoundMgr38::sub_710102B4B8() {
    sead::Vector3f position = sead::Vector3f::zero;
    f32 distance = 0.0f;
    if (ksys::act::ActorSystem::instance()->getPlayerPosition(&position) &&
        ksys::act::ActorSystem::instance()->getPlayer() &&
        ksys::act::ActorSystem::instance()->getPlayerLink()->m200()) {
        if (auto* placement = ksys::map::PlacementMgr::instance()) {
            if (auto* terrain = placement->mTeraSystem) {
                f32 height = 0.0f;
                const sead::Vector2f xz{position.x, position.z};
                if (ksys::tera::sub_71011094A0(&height, &xz, terrain, -1, 0))
                    distance = position.y - height;
            }
        }
    }
    _130 = distance;
}

Unk_SoundMgr38_28* Unk_SoundMgr38::sub_710102C104() const {
    return _28;
}

Unk_SoundMgr38_28* Unk_SoundMgr38::sub_710102C10C() const {
    if (_70)
        return nullptr;
    return _28;
}

void Unk_SoundMgr38::sub_710102B11C() {
    sub_710102AF84();
}

}  // namespace ksys::snd
