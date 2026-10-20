#include "Game/Actor/actRope.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "Game/gameSceneSubsysMisc.h"

// Existing global damage callback cleanup, also called by DynamicActor.
void sub_7100D2D424(uking::act::DamageManagerBase* manager);

namespace uking::act {

Rope::Rope(const CreateArg& arg) : RopeBase(arg), _a00(this), _c30(this), _cc8(this, 0x800002a) {}

void Rope::m63() {
    RopeBase::m63();
    sub_71007394E8(this);
    sub_7100739108(getActorAttackSensor(this));
    sub_7100739168(sub_71007A2844(this));
    _a00.clearCallbacks();
    _cc8._8 = &getMessageTransceiver();
}

ksys::act::BaseProc* Rope::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Rope(arg);
}

bool Rope::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!RopeBase::prepareInit_(heap, arg))
        return false;
    if (!_c30.init(heap))
        return false;
    // called through a pointer in the original (not devirtualised)
    const s32 num_callbacks = (&_a00)->getNumCallbacks();
    if (num_callbacks != 0) {
        _a00.mCallbacks.tryAllocBuffer(num_callbacks, heap);
        _a00.mCallbacks.fill(nullptr);
        if (!_a00.mCallbacks.getBufferPtr())
            return false;
    }
    // called through a pointer in the original (not devirtualised)
    if (!(&_a00)->allocStruct20(heap))
        return false;
    // called through a pointer in the original (not devirtualised)
    return (&_a00)->initCallbacks(heap);
}

void Rope::onPreDeleteStart_(PrepareArg& arg) {
    sub_7100D2D424(&_a00);
    // called through a pointer in the original (not devirtualised)
    (&_a00)->preDelete1();
    // called through a pointer in the original (not devirtualised)
    (&_a00)->preDelete2();
    _c30.free();
}

void Rope::initMaybe() {
    RopeBase::initMaybe();
}

void Rope::updatePositionMaybe() {
    RopeBase::updatePositionMaybe();
}

void Rope::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    RopeBase::m76(setter);
    auto* mgr = sead::DynamicCast<uking::act::DamageManager>(getDamageMgr());
    if (!mgr)
        return;
    const s32 type = mgr->getField54();
    auto* mask = mgr->tgSensorMaterialOnHitMaybe();
    mgr->applyDamage(*getLife());
    if (type == -1)
        return;
    sead::BitFlag8 flags;
    sub_7100732864(&flags, this);
    if (!flags.isOnBit(0))
        return;
    DamageReactionInfo info;
    sub_7100732B28(&info, this);
    info._30 = mask;
    sub_7100733418(this, &info, nullptr);
}

// NON_MATCHING: block layout (the original checks hasProc for a single end before joining the shared tail, and
// indexes the end with `idx != 0`).
void Rope::m148(s32 idx) {
    const auto send = [this](const ksys::act::BaseProcLink& link) {
        if (!link.hasProc())
            return;
        auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr));
        _cc8.sub_710070DBB0(*actor->getMesTransceiverId(), true);
    };
    if (idx < 0) {
        send(_8c0[0]);
        send(_8c0[1]);
    } else if (idx < 2) {
        send(_8c0[idx]);
    }
}

ksys::act::Unk_71025ae640* Rope::getAtk() {
    return &_c30;
}

void Rope::m149() {
    if (GameSceneSubsys5::instance() == nullptr)
        return;
    GameSceneSubsys5::instance()->sub_7100905C70();
}

s32* Rope::getLife() {
    return &_cb0;
}

uking::act::DamageManagerBase* Rope::getDamageMgr() {
    return &_a00;
}

// NON_MATCHING: the original inlines the destructors of RopeBase and ActorAtk; both are out of line here until
// their key functions (RopeBase::initMaybe 0x7100ecf66c, ActorAtk::init 0x710079d7b0) are decompiled.
Rope::~Rope() = default;

}  // namespace uking::act
