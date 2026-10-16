#include "Game/Actor/Action/actionPriestBossClonesSpawnForDemo.h"
#include "Game/Actor/aiUnk_7102450fa8.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/System/Timer.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include <math/seadQuat.h>

namespace uking::action {

// NON_MATCHING: zero-store merging of _54-_5c (the original merges _58/_5c, ours _54/_58)
PriestBossClonesSpawnForDemo::PriestBossClonesSpawnForDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

PriestBossClonesSpawnForDemo::~PriestBossClonesSpawnForDemo() = default;

Unk_7102450fa8* PriestBossClonesSpawnForDemo::sub_71000664E4() {
    return sead::DynamicCast<Unk_7102450fa8>(*static_cast<Unk_71025afb58**>(mPriestBossMetaAIUnit_a));
}

bool PriestBossClonesSpawnForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PriestBossClonesSpawnForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PriestBossClonesSpawnForDemo::leave_() {
    auto* physics = mActor->getPhysics();
    physics->sub_7100FBDFA4(physics->get178(0));
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    sub_71007A3800(mActor);
}

void PriestBossClonesSpawnForDemo::loadParams_() {
    getDynamicParam(&mDurationFrame_d, "DurationFrame");
    getDynamicParam(&mDecelerationFrame_d, "DecelerationFrame");
    getDynamicParam(&mASName_d, "ASName");
    getDynamicParam(&mOffset_d, "Offset");
    getAITreeVariable(&mPriestBossMetaAIUnit_a, "PriestBossMetaAIUnit");
}

// NON_MATCHING: block placement of the shared distance tail only.
void PriestBossClonesSpawnForDemo::calc_() {
    if (!sub_71000664E4())
        return;

    if (_54 >= 1) {
        ksys::Timer::update(&_58, 1.0f);
        if (_58 <= f32(_54)) {
            ksys::act::ActorLinkConstDataAccess accessor;
            if (sub_71000664E4()->sub_71007194D4(_50, &accessor)) {
                const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
                ksys::act::sub_7100EE57FC(mActor, pos);
            }
            return;
        }
        mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
        _54 = 0;
    }

    if (_84 && !mASName_d.isEmpty()) {
        playAS(mASName_d.cstr(), false, 0, 0, -1.0f);
        _84 = false;
    }

    ksys::Timer::update(&_5c, 1.0f);
    f32 t;
    if (sub_7100066884()) {
        t = mOffset_d->length();
        if (m32())
            setFinished();
    } else {
        const s32 duration = *mDurationFrame_d;
        const s32 decel_frames = *mDecelerationFrame_d;
        const f32 decel_start = f32(duration - decel_frames);
        const f32 accel_time = _5c > decel_start ? decel_start : _5c;
        const f32 over = _5c - decel_start;
        const f32 decel_time = sead::Mathf::clamp(over, 0.0f, f32(decel_frames));
        const f32 moved = accel_time * (_6c + _70);
        if (decel_time > 0.0f && _5c <= f32(duration))
            _74 += m33(decel_time / f32(decel_frames));
        t = moved + _74 * _6c + decel_time * _70;
    }
    sub_71000668A0(t);
}

bool PriestBossClonesSpawnForDemo::m32() {
    return true;
}

f32 PriestBossClonesSpawnForDemo::m33(f32 t) {
    t -= 1.0f;
    return (t * t - 1.0f) + 1.0f;
}

bool PriestBossClonesSpawnForDemo::sub_7100066884() {
    return _5c >= f32(*mDurationFrame_d);
}

void PriestBossClonesSpawnForDemo::sub_71000668A0(f32 t) {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (sub_71000664E4()->sub_71007194D4(_50, &accessor)) {
        const sead::Matrix34f& base_mtx = accessor.getActorMtx();
        const sead::Vector3f offset = _60;
        sead::Quatf rotation;
        base_mtx.toQuat(rotation);
        rotation.normalize();
        sead::Vector3f rotated;
        rotated.setRotated(rotation, offset);
        sead::Matrix34f mtx;
        mtx.makeQT(rotation, base_mtx.getTranslation() + rotated * t);
        ksys::act::sub_7100EE58C0(mActor, mtx);
    }
}

void PriestBossClonesSpawnForDemo::sub_7100066CE4(int delay) {
    _54 = delay;
    if (delay >= 1) {
        sub_71000668A0(0.0f);
        mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_20);
    }
}

}  // namespace uking::action
