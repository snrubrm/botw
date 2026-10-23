#include "Game/Actor/actActorReaction.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2EventSLink.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/ActorSystem/actReactionSLinkLimiter.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Sound/sndInfoData.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/XLink/xlinkManager.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include "KingSystem/XLink/xlinkXLink.h"
#include "Game/Actor/aiXlinkHandle.h"
#include "KingSystem/Sound/sndSound.h"
#include <hostio/seadHostIOCurve.h>
#include <algorithm>

namespace ksys::act {
// 0x7100ebe72c / 0x7100ebf054 (declared only; placeholder signatures): map the reaction slide
// type name to its index and return the text of the reaction size enum.
s32 sub_7100EBE72C(const al::ByamlIter& iter, const al::ByamlIter& iter2);
const char* sub_7100EBF054(s32 index);
}

namespace uking::act {

ActorReaction::ActorReaction(const CreateArg& arg) : Actor(arg) {
    _1c0 = 2;
    getJobHandler(ksys::act::JobType::PreCalc) = nullptr;
    getJobHandler(ksys::act::JobType::Calc1) = nullptr;
    getJobHandler(ksys::act::JobType::Calc2) = nullptr;
}

ActorReaction::~ActorReaction() = default;

ksys::act::BaseProc* ActorReaction::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) ActorReaction(arg);
}

}  // namespace uking::act

Unk_71024efd58::Unk_71024efd58(const InitArg& arg) : _8(arg.actor), _10(arg._8) {}

Unk_71024efd58::~Unk_71024efd58() = default;

void Unk_71024efd58::sub_7100EBF8C4(sead::Heap* heap) {
    m8();
    m4(heap);
}

namespace ksys::act {

void ActorUnk6b8::sub_7100EBBCB8(bool fixed) {
    if (fixed) {
        _88 |= 0x4000;
        _8e = 3;
    } else {
        _88 &= ~0x4000;
    }
}

void ActorUnk6b8::sub_7100EBBCE4(bool on) {
    _88 = on ? (_88 | 0x100) : (_88 & ~0x100);
}

void ActorUnk6b8::sub_7100EBBD04() {
    _90 = 10;
}

// NON_MATCHING: the original calls the base constructor 0x7100ebf8a0 (ours inlines it; it is defined above) and
// stores _84 before _7c.
ActorUnk6b8::ActorUnk6b8(const InitArg& arg) : Unk_71024efd58(arg) {
    if (auto* xlink = _8->getXLink()) {
        if (auto* user = xlink->_48) {
            xlink2::Locator locator;
            user->searchAsset(&locator, "ReactionEffect");
            if (locator.getAssetCallTable())
                _88 |= 0x800;
        }
    }
    _88 |= 2;
    if (_8->getName().findIndex("Tree") != -1 && _8->getName().findIndex("Trunk") != -1)
        _88 |= 4;
    if (_8->getName().findIndex("_Trunk") != -1)
        _88 |= 0x200;
    _7c = 0;
    _80 = 0;
    _84 = 0;
    _8a |= 3;
}

// Keep the native vptr store, following GameDataFlagSelector (upstream commit 96101229).
ActorUnk6b8::~ActorUnk6b8() { ; }

// NON_MATCHING: the _8e decrement is cmp / b.le / sub in the original (ours: subs / b.lt like the other
// counters), and the fade target address is kept in a register.
void ActorUnk6b8::m5() {
    if (BaseProcMgr::instance()->getMode() != BaseProcMgr::Mode::_0)
        return;
    auto* body = _8->getPhysicsMainBody();
    if (!body)
        return;

    auto* reaction = Reaction::instance()->_a8;
    const f32 rate = reaction ? reaction->sub_7100EC877C() : 0.0f;
    if (!(_88 & 0x4000)) {
        if (_74 > 0.0f) {
            _74 *= rate;
            if (_74 <= sead::Mathf::epsilon())
                _74 = 0.0f;
        }
        _7c = (_7c & 3) != 0 ? _7c - 1 : 0;
        _80 = (_80 & 3) != 0 ? _80 - 1 : 0;
        _84 = (_84 & 3) != 0 ? _84 - 1 : 0;
        if (_8e > 0)
            --_8e;
        if (_8c > 0)
            --_8c;
        if (_90 > 0)
            --_90;
        if (_8f > 0)
            --_8f;
        if (_8b > 0)
            --_8b;
        _4c = _40;
        body->getLinearVelocity(&_40);
    }

    if (_8d > 0 && --_8d <= 0) {
        _20.fade(reaction ? reaction->sub_7100EC87A4() : 0);
        _58 = phys::MaterialMask();
    }

    if (_8->getLife() && *_8->getLife() <= 0 && !_8->sub_71011CEA90())
        _20.fade(-1);

    if (_8->sub_71011CEA90()) {
        if (!(_88 & 0x400)) {
            if (reaction)
                _8c = reaction->sub_7100EC89BC();
            _88 |= 0x400;
        }
    } else {
        _88 &= ~0x400;
    }
    _88 &= 0xef07;

    if (auto* xlink = _8->getXLink()) {
        if (auto* user = xlink->_50) {
            if (xlink->_cc.isOnBit(1))
                user->setPropertyValue(0x18, _88 >> 8 & 1);
            if (xlink->_cc.isOnBit(22)) {
                user->setPropertyValue(0x19, _a0 / 30.0f);
                user->setPropertyValue(0x1a, _a4 / 30.0f);
            }
        }
    }
    _88 &= ~0x100;
    _a0 = 0.0f;
    _a4 = 0.0f;
    ++_7a;
}

void ActorUnk6b8::m8() {}

void ActorUnk6b8::m9() {
    _20.fade(-1);
    _8d = 0;
}

void ActorUnk6b8::m10() {
    const u16 flags = _88;
    _88 = flags | 0x2000;
    if (flags & 1)
        _20.fade(-1);
}

void ActorUnk6b8::SoundHandles::fade(s32 frame) {
    _0.fade(frame);
    _10.fade(frame);
}

// NON_MATCHING: the body and call sequence match, but the ReactionSetting, the ByamlIter local and
// the by-value SafeString temporaries are laid out 0x18 higher on the stack than the original
// (the size-name SafeString and the text temporary land in the local area instead of the outgoing
// argument area), and the original writes kind/size with one stp instead of a 64-bit str.
// 0x7100ebdcb0: the slide reaction of a contact. Emits the "ReactionSlide" asset for the actor's
// sound user when the held event is gone, then either updates the still-active event or rebuilds
// the full reaction setting (kind / size / material / volume / pitch) and emits it through the
// reaction receiver. `a` is the incoming speed, `b` and `c` are passed through to the setting and
// the extra sound, and the two masks are the contact materials.
void ActorUnk6b8::sub_7100EBDCB0(f32 a, f32 b, f32 c, Actor* actor,
                                 const phys::MaterialMask* mask1,
                                 const phys::MaterialMask* mask2) {
    _88 &= ~1;

    if (_20._0.isActive() || (_88 & 0x2000))
        return;

    auto* reaction = Reaction::instance()->_a8;
    if (!reaction)
        return;

    sead::Vector3f position = actor->getMtx().getTranslation();
    if ((_88 & 0x200) && actor->getMainBody())
        actor->getMainBody()->getCenterOfMassInWorld(&position);

    if (reaction->_108 + reaction->_10c > 2)
        return;

    auto* limiter = reaction->mSLinkLimiter;
    if (limiter && !limiter->sub_7100EC9D84(1, position, false))
        return;

    const f32 speed =
        a * std::max(snd::InfoData::instance()->getReactionSettingSlideVelocityRatio(
                         snd::InfoData::instance()->getInfo(
                             act::InfoData::instance()->getSLinkUser(
                                 actor->getName().cstr()))),
                     0.0f);

    if (auto* xlink = actor->getXLink()) {
        if (auto* user = xlink->_50) {
            if (!_20._0.isActive()) {
                xlink2::Locator locator;
                if (user->searchAsset(&locator, "ReactionSlide")) {
                    if (auto* xlink2 = actor->getXLink()) {
                        if (auto* user2 = xlink2->_50) {
                            const s32 material = mask1->getMaterial();
                            user2->setPropertyValue(0, material);
                            const s32 sub_material =
                                xlink::Manager::instance()->getSubMaterialIndex(
                                    material, mask1->getSubMaterialIdx());
                            user2->setPropertyValue(1, sub_material);
                            user2->setPropertyValue(4, speed);
                        }
                    }
                    user->emit(locator, &_20._0);
                }
            }
        }
    }

    f32 arg4;
    if (_20._0.isActive()) {
        f32 value = 0.0f;
        if (actor->get68f())
            value = actor->get6f4();
        reaction->sub_7100EC7D50(speed, value, 1.0f, 1.0f, &_20._0, nullptr, nullptr);
        _20._0.setPosition(position);
        arg4 = -1.0f;
        if (auto* xlink = actor->getXLink()) {
            arg4 = xlink->sub_71012342A0();
            if (arg4 >= 0.0f) {
                auto* event = static_cast<xlink2::EventSLink*>(_20._0.getEvent());
                if (event && event->getCreateId() == _20._0.getCreateId())
                    _20._0.setVolumeScale(std::max(arg4 * event->getVolumeScale(), 0.0f));
            }
        }
    } else {
        ReactionSetting setting;
        setting.speed = speed;
        setting._14 = b;
        setting._18 = c;
        setting.mask1 = *mask1;
        setting.mask2 = *mask2;
        setting.volume = 1.0f;
        setting.pitch = 1.0f;
        setting.kind = 1;
        setting.size = 0;
        setting._1c = 0.0f;
        if (actor->get68f())
            setting._1c = actor->get6f4();
        setting.name = actor->getName().cstr();
        setting._20 = (actor->_6a0->_10._8 >> 3) & 1;

        al::ByamlIter info = snd::InfoData::instance()->getInfo(
            act::InfoData::instance()->getSLinkUser(actor->getName().cstr()));
        setting.kind = sub_7100EBE72C(info, info);

        sead::SafeString size_name =
            snd::InfoData::instance()->getReactionSettingSlideType(info);
        s32 size = 0;
        for (s32 i = 0; i < 37; ++i) {
            if (size_name == sub_7100EBF054(i)) {
                size = i;
                break;
            }
        }
        setting.size = size;

        setting.pitch = snd::InfoData::instance()->getReactionSettingSlidePitch(info);
        f32 volume = snd::InfoData::instance()->getReactionSettingSlideVolume(info);
        f32 scale = -1.0f;
        if (actor && actor->getXLink())
            scale = actor->getXLink()->sub_71012342A0();
        if (scale >= 0.0f)
            volume *= scale;
        setting.volume = volume;
        arg4 = volume;

        if (!(_88 & 0x2000))
            reaction->sub_7100EC72A0(&_20._0, position, setting);

        _88 |= 1;
        _58 = setting.mask2;
    }

    if (_20._0.isActive())
        _20._0.getEvent()->resetFlagBit(1);
    if (auto* event = _20._0.getEvent())
        event->resetFlagBit(3);

    sub_7100EBE92C(speed, b, actor->get6f4(), arg4, actor, *mask2);
    if (limiter)
        limiter->sub_7100ECA2A0(1, position, _20._0);
    ksys::eft::sub_710105E114(&_20._0, actor);
    ++reaction->_10c;
}

}  // namespace ksys::act
