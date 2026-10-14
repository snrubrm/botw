#include "Game/Actor/actActorReaction.h"
#include <basis/seadNew.h>
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include <math/seadMathCalcCommon.h>
#include <xlink2/xlink2Locator.h>
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include <xlink2/xlink2UserInstanceELink.h>
#include "KingSystem/XLink/xlinkXLink.h"

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

namespace ksys::act {

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

}  // namespace ksys::act
