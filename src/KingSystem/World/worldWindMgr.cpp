#include "KingSystem/World/worldWindMgr.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include <aal/aalHandle.h>
#include <aal/aalShape.h>
#include <aal/aalSoundSource.h>
#include <aal/aalSpeakerBalanceUnifier.h>
#include <xlink2/xlink2AssetExecutorSLink.h>
#include <xlink2/xlink2EventSLink.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actChemicalElementHolder.h"
#include "KingSystem/World/worldElementDirectionalWind.h"
#include "KingSystem/World/worldManager.h"
#include "Game/gameUnkRttiPlaceholders.h"
#include "KingSystem/Utils/Types.h"
#include <utility/aglPrimitiveTexture.h>
#include <g3d/aglTextureUtilG3D.h>
#include <cstring>
#include <layer/aglRenderer.h>
#include <layer/aglLayer.h>
#include <random/seadGlobalRandom.h>

namespace ksys::world {

// Wind transition constants at 0x710250d280; field meaning unknown. Hidden visibility matches the
// original's direct adrp+add access (no GOT, no constant folding).
struct WindTransitionConstants {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _c;
    f32 _10;
    f32 _14;
    f32 _18;
};
KSYS_VISIBILITY_HIDDEN WindTransitionConstants sUnk_710250d280 = {
    0.001f, 30.0f, 120.0f, 2.0f, 0.0001f, 300.0f, 60.0f};

Unk_710250D258::~Unk_710250D258() = default;

void Unk_710250D258::sub_71010EE904(f32 delta, f32 speed) {
    switch (_c) {
    case 0:
        if (_8) {
            _c = 1;
            break;
        }
        if (_14 <= 0.0f) {
            _14 = (sead::GlobalRandom::instance()->getF32() + 2.0f) * 30.0f * 60.0f;
        } else {
            _14 -= delta;
            if (_14 < 0.0f) {
                _14 = 0.0f;
                if (speed <= 10.0f) {
                    auto* manager = Manager::instance();
                    if (!manager || manager->mManualWindTimer == 0)
                        _8 = true;
                }
            }
        }
        break;
    case 1:
        _10 += (-1.0f / sUnk_710250d280._14) * delta;
        if (_10 < 0.0f) {
            _c = 2;
            _10 = 0.0f;
        }
        break;
    case 2:
        if (auto* manager = Manager::instance()) {
            manager->rerollClimateWindPowers();
            ++_c;
        } else {
            _c = 3;
        }
        break;
    case 3:
        _10 += (1.0f / sUnk_710250d280._18) * delta;
        if (_10 >= 1.0f) {
            _c = 4;
            _10 = 1.0f;
        }
        break;
    case 4:
        _c = 0;
        _8 = false;
        break;
    }
}

WindMgr::WindMgr()
    : _20(nullptr), _28(0x18), _2c(15.0f), _30(0.0f), _34(1.0f, 0.0f, 0.0f),
      _40(1.0f, 0.0f, 0.0f), _4c(15.0f), _50(0.0f, 0.0f),
      _58(0.0f, 0.0f), _60(0.0f), _64(0.0f), _68(0.0f), _6c(0.0f) {
    std::memset(&_98, 0, sizeof(_98));
}

WindMgr::~WindMgr() = default;

void WindMgr::init_(sead::Heap* heap) {
    _20 = new (heap, 8) Unk_710251F868;
    _20->sub_71012FEAA8(heap);
    std::memset(&_98, 0, sizeof(_98));
    agl::g3d::TextureUtilG3D::convertToResTexture(
        &_98, agl::utl::PrimitiveTexture::instance()->mSamplers[2]->mTextureData, nullptr);
}

void WindMgr::sub_71010EEBE4(sead::Vector3f* out, const sead::Vector3f* position) {
    if (!(_28 & 8)) {
        sub_71010EEA98(out, position);
        return;
    }
    out->set(_34);
}

agl::TextureSampler* WindMgr::sub_71010EEE94() {
    if (!(_28 & 0x40))
        return &_20->_48;
    return agl::utl::PrimitiveTexture::instance()->mSamplers[2];
}

agl::TextureData* WindMgr::sub_71010EEEBC() {
    if (!(_28 & 0x40))
        return _20->_40;
    return &agl::utl::PrimitiveTexture::instance()->mSamplers[2]->mTextureData;
}

nn::gfx::ResTextureData* WindMgr::sub_71010EEEE8() {
    if (!(_28 & 0x40))
        return &_20->_1b8;
    return &_98;
}

f32 WindMgr::sub_71010EEF48() const {
    return _20->_8;
}

// NON_MATCHING: the constant load, multiplication schedule and upper clamp differ.
f32 WindMgr::sub_71010EEF04() const {
    // The original constant at 0x710250d250 is 12.0f.
    const f32 strength = _70._10 * ((_68 / 12.0f) * 15.0f);
    if (strength < 0.0f)
        return 0.0f;
    if (strength > 1.0f)
        return 1.0f;
    return strength;
}

// NON_MATCHING: the inlined strength calculation has the same differences as sub_71010EEF04.
f32 WindMgr::x_0() {
    return _20->sub_71012FF2B0(sub_71010EEF04());
}

// NON_MATCHING: the inlined strength calculation has the same differences as sub_71010EEF04.
f32 WindMgr::x_1() {
    return _20->sub_71012FF268(sub_71010EEF04());
}

// NON_MATCHING: vector component copies and normalization scheduling differ slightly.
void WindMgr::sub_71010EEA98(sead::Vector3f* out, const sead::Vector3f* position) {
    if (_28 & 6) {
        *out = _40;
        out->normalize();
        return;
    }
    if (auto* manager = Manager::instance())
        *out = position ? manager->getWindDirection(*position) : manager->getWindDirection();
    out->normalize();
}

f32 WindMgr::sub_71010EECE8(const sead::Vector3f* position, f32 value) {
    if (_28 & 0x10)
        return sub_71010EECF8(position, value);
    return sub_71010EEC04();
}

// NON_MATCHING: the flag conditions fold into one comparison and share the fallback branch.
f32 WindMgr::sub_71010EEC04() {
    sead::Vector3f position(0.0f, 0.0f, 0.0f);
    if (auto* renderer = agl::lyr::Renderer::instance()) {
        if (auto* layer = renderer->mLayers[1]) {
            if (auto* camera = layer->sub_7100B60CE0())
                camera->getWorldPosByMatrix(&position);
        }
    }
    auto* manager = Manager::instance();
    if ((!manager || manager->mManualWindTimer == 0) && !(_28 & 0x20)) {
        if (_28 & 8)
            return _2c * _70._10;
    }
    if (_28 & 6)
        return _4c;
    return manager ? manager->getWindSpeed(position) : 0.0f;
}

// NON_MATCHING: flag branches share fallback paths and the blend math is scheduled differently.
f32 WindMgr::sub_71010EECF8(const sead::Vector3f* position, f32 value) {
    sead::Vector3f wind;
    if (_28 & 8)
        wind = _34;
    else
        sub_71010EEA98(&wind, position);
    sead::Vector2f direction(wind.x, wind.z);
    direction.normalize();
    auto* manager = Manager::instance();
    f32 speed;
    if ((!manager || manager->mManualWindTimer == 0) && !(_28 & 0x20) && (_28 & 8))
        speed = _2c * _70._10;
    else if (_28 & 6)
        speed = _4c;
    else
        speed = manager ? manager->getWindSpeed(*position) : 0.0f;
    const f32 strength = _20->sub_71012FF01C(position, &direction, speed / 15.0f, value);
    const f32 excess = speed - 15.0f;
    // The original upper-bound comparison selects 1 even when excess is NaN.
    const f32 blend = excess < 0.0f ? 0.0f : excess <= 1.0f ? excess : 1.0f;
    return speed * ((strength + (1.0f - strength) * blend) * 0.3f + 0.7f);
}

}  // namespace ksys::world

ElementDirectionalWindOrGust*
ElementDirectionalWindOrGust::create(const ElementDirectionalWindCreateArg* arg) {
    auto* holder = ksys::world::Manager::instance()->getChemicalMgrUnchecked()->_ae8;
    if (holder)
        return holder->sub_71010F1BB0(arg);
    return nullptr;
}

// NON_MATCHING: the original passes the address of the (not yet constructed) local `name` to the base
// constructor, so no temporary ElementName is built there.
ElementDirectionalWindOrGust::ElementDirectionalWindOrGust(const ElementDirectionalWindCreateArg& arg,
                                                           sead::Heap* heap)
    : Unk_7102518688(ElementName(), heap, false) {
    mArg = arg;
    mArg.direction.normalize();

    ElementName name;
    if (mArg.flags & 2)
        name.mName = "gust";
    else
        name.mName = "directional_wind";
    if (mArg.actor && mArg.actor->getChemicalContainer())
        name._18 = mArg.actor->getChemicalContainer()->_68;
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());

    if (mArg.flags & 4)
        _88 = true;
    mArg.actor = nullptr;
}

ElementDirectionalWindOrGust::~ElementDirectionalWindOrGust() {
    if (_48) {
        delete _48;
        _48 = nullptr;
    }
    _50 = false;
    if (_58.isActive()) {
        _58.fade();
        _58.reset();
    }
    if (_68.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
    }
    _68.fade();
    _78 = false;
    if (_80) {
        _80->destroy();
        _80 = nullptr;
    }
}

f32 ElementDirectionalWindOrGust::m22() {
    const f32 radius = mArg._20;
    return sead::Mathf::pi() * radius * radius + (radius * 0.75f + mArg._24);
}

// NON_MATCHING: register allocation (one more callee-saved register keeps &_68).
void ElementDirectionalWindOrGust::doEmitSLink() {
    if (mArg.flags & 0x20)
        return;
    if (_68.isActive() || !_78)
        return;
    _68 = ksys::eft::searchAndEmitSLink(ksys::act::Reaction::instance()->_38, "windEmit", false);
    if (!_68.isActive())
        return;
    _68.getEvent()->resetFlagBit(1);
    auto* shape = _80;
    if (shape && _68.isActive()) {
        if (auto* executor =
                static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                source->mSpatialSetting.setShape(shape);
    }
    if (!_88)
        _68.setPosition(mArg.position);
}

// NON_MATCHING: scheduling (the original reads _50 before the handle test and the arg fields in another order).
void ElementDirectionalWindOrGust::doEmitELink() {
    const bool active = _58.isActive();
    if (!_50) {
        if (active) {
            _58.fade();
            _58.reset();
        }
        return;
    }
    if (active)
        return;

    const sead::Vector3f pos = mArg.position;
    const sead::Vector3f dir = mArg.direction;
    const f32 length = mArg._24;
    const char* name;
    if (mArg.flags & 0x10)
        name = "Chemical_Uchiwa";
    else if (mArg.flags & 2)
        name = "Chemical_Gust";
    else
        name = "Chemical_Wind";
    _58 = ksys::eft::searchAndEmitELink(ksys::act::Reaction::instance()->_38, name);
    const sead::Matrix34f mtx(1, 0, 0, pos.x + length * dir.x * 0.5f,  //
                              0, 1, 0, pos.y + length * dir.y * 0.5f,  //
                              0, 0, 1, pos.z + length * dir.z * 0.5f);
    _58.setMatrix(mtx);
}

void ElementDirectionalWindOrGust::m33(bool a, bool fixed) {
    if (_48)
        _48->setFixed(ksys::phys::Fixed(fixed), ksys::phys::PreserveVelocities(true));
    if (!(mArg.flags & 8)) {
        _50 = !a;
        doEmitELink();
    }
    if (_68.isActive()) {
        if (auto* executor = static_cast<xlink2::EventSLink*>(_68.getEvent())->getAliveAssetExecutor())
            if (auto* source = executor->getHandle()->getSoundSource())
                if (auto* calculator = source->mSpatialCalculator)
                    calculator->detachShape(true);
    }
    _68.fade();
}

s32 ElementDirectionalWindOrGust::m26() {
    return (mArg.flags & 0x40 ? 1 : 0) + 1;
}

// NON_MATCHING: the original loads mArg._24 before the length (kept in s12).
f32 ElementDirectionalWindOrGust::m13(f32* out, const sead::Vector3f& pos,
                                      ksys::act::Chemical* chemical) {
    sead::Vector3f diff = pos - mArg.position;
    f32 distance = diff.length();
    if (mArg._24 != 0.0f) {
        if (distance > 0.0f)
            diff *= 1.0f / distance;
        const f32 cos = diff.dot(mArg.direction);
        distance *= std::sqrt(sead::Mathf::clamp(1.0f - cos * cos, 0.0f, 1.0f));
    }
    f32 ratio = distance / mArg._20;
    ratio *= ratio;
    if (ratio > 1.0f)
        ratio = 1.0f;
    *out = 1.0f - ratio;
    return mHolder->_30;
}

// NON_MATCHING: the original copies the direction as 8 + 4 bytes and loads mArg._24 before the length.
f32 ElementDirectionalWindOrGust::m14(sead::Vector3f* out, const sead::Vector3f& pos) {
    *out = mArg.direction;
    sead::Vector3f diff = pos - mArg.position;
    f32 distance = diff.length();
    if (mArg._24 != 0.0f) {
        if (distance > 0.0f)
            diff *= 1.0f / distance;
        const f32 cos = diff.dot(mArg.direction);
        distance *= std::sqrt(sead::Mathf::clamp(1.0f - cos * cos, 0.0f, 1.0f));
    }
    f32 strength = mArg._28;
    if (mArg._20 <= distance)
        strength *= 1.0f - sead::Mathf::clamp(distance - mArg._20, 0.0f, 1.0f);
    return strength;
}

// NON_MATCHING: regalloc (s10 / s11 and s0 / s1 swapped), as ElementWater::m20.
f32 ElementDirectionalWindOrGust::m20(ksys::act::Chemical* chemical) {
    sead::Matrix34f mtx;
    chemical->sub_7100D9153C(&mtx);
    sead::Vector3f dir;
    mtx.getTranslation(dir);
    dir -= mArg.position;
    const f32 distance = dir.normalize();
    const f32 cos = dir.dot(mArg.direction);
    const f32 sin = std::sqrt(sead::Mathf::clamp(1.0f - cos * cos, 0.0f, 1.0f));
    const f32 radius = chemical->_34;
    return sead::Mathf::clamp((radius - (distance * sin - mArg._20)) / (radius + radius), 0.0f, 1.0f);
}

ElementDirectionalWindOrGust*
ksys::act::Unk_71024dd490::sub_71010F1BB0(const ElementDirectionalWindCreateArg* arg) {
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
    auto* element = new (parent, std::nothrow_t()) ElementDirectionalWindOrGust(*arg, heap);
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
Unk_710250d3e8::Unk_710250d3e8(const Unk_710250d3e8Arg& arg, sead::Heap* heap)
    : Unk_7102518688(ElementName(), heap, true), mArg(arg) {
    ElementName name;
    name._18 = arg._0;
    name.mName = "directional_wind";
    emitWrap(name, ksys::world::Manager::instance()->getElementHolderMaybe());
}

Unk_710250d3e8*
ksys::act::Unk_71024dd490::sub_71010F1D1C(const Unk_710250d3e8Arg* arg) {
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
    auto* element = new (parent, std::nothrow_t()) Unk_710250d3e8(*arg, heap);
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
