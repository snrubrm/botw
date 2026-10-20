#include "KingSystem/Sound/sndSound.h"
#include <cstring>
#include <aal/aalGroupMgr.h>
#include <aal/aalSystemAccessor.h>

namespace ksys::snd {

// 0x710103e404
DuckingMgr::DuckingMgr() = default;

// 0x710103e424: frees the ducker array and destroys its heap.
DuckingMgr::~DuckingMgr() {
    mDuckers.freeBuffer();
    if (mHeap) {
        mHeap->destroy();
        mHeap = nullptr;
    }
}

// 0x710103dce4: finalizes the group ducker; the member destructor then releases it.
DuckingMgr::Ducker::~Ducker() {
    mDucker.finalize();
}

// NON_MATCHING: the original spills the state local to the stack (store + reload) before testing it, ours keeps
// it in a register (8 bytes shorter).
// 0x710103df60: per-frame update. While inactive and idle it releases the group ducker; otherwise it accumulates
// the ducking time and ends the ducking once the configured duration has passed.
void DuckingMgr::Ducker::calc() {
    if (!(_c8 & 1)) {
        const s32 state = mDucker.getState();
        if (state == 0) {
            if (_b0)
                return;
            if (!mDucker.isInitialized())
                return;
            mDucker.removeAndDestroyAllTargets();
            mDucker.finalize();
            return;
        }
    }
    mDucker.calc();
    _c0 += sub_710105E3A4();
    if (!_b0)
        return;
    const f32 duration = _b0->mDuration;
    if (duration > 0.0f && duration > _c0)
        return;
    _c8 &= ~1;
}

// NON_MATCHING: the original keeps `this` in x19 and computes &mDucker for the tail call, ours keeps `this` in
// x20 and precomputes &mDucker (8 bytes larger).
// 0x710103e2dc (placeholder name): restarts the ducking for `f` when the group's volume is low enough.
void DuckingMgr::Ducker::sub_710103E2DC(f32 f) {
    if (_c4 > f) {
        if (u32(mDucker.getState()) < 2)
            return;
        if (_b0) {
            const f32 duration = _b0->mDuration;
            if (duration > 0.0f) {
                const f32 remaining = duration - _c0;
                sub_710103E020(f);
                if (remaining > 0.0f)
                    mDucker.getSettings()._0 = remaining;
                mDucker.resetState();
                return;
            }
        }
    }
    sub_710103E020(f);
    mDucker.resetState();
}

// 0x710103ddf0: copies the settings' name into the ducker's buffer and sets the group ducker up from them.
void DuckingMgr::Ducker::setup(sead::Heap* heap, Unk_7102612628* settings) {
    mName.copy(settings->mName);
    _c8 = settings->_68 ? (_c8 | 2) : (_c8 & ~2);
    mDucker.initialize(nullptr);
    mDucker.setup(settings->mSettings);
    for (s32 i = 0; i < settings->mTargetNum; ++i)
        mDucker.createAndAddTarget(settings->mTargets[i]->mName, settings->mTargets[i]->mSettings, heap);
    _b0 = settings;
}

// 0x710103e128 (placeholder name): the same setup from a request, adding every group of the request as a target
// with the request's target setting.
void DuckingMgr::Ducker::sub_710103E128(sead::Heap* heap, Unk_71025022a0* request) {
    if (mDucker.isInitialized())
        return;
    mName.copy(request->mName);
    _c8 = request->_80 ? (_c8 | 2) : (_c8 & ~2);
    mDucker.initialize(nullptr);
    mDucker.setup(request->mSettings);
    auto* groups = request->mGroups;
    auto* group = groups->dataBegin();
    auto* const end = group + groups->size();
    for (; group != end; ++group)
        mDucker.createAndAddTarget(*group, request->mTargetSettings, heap);
    _c8 |= 1;
    _c0 = 0;
}

// 0x710103e020 (placeholder name): rewrites the volume and the fade speed of every target when the group
// ducker has as many targets as the settings, then starts the ducking with the given `f` factor.
void DuckingMgr::Ducker::sub_710103E020(f32 f) {
    const s32 num = mDucker.getTargetNum();
    if (num != _b0->mTargetNum)
        return;
    if (num >= 1) {
        for (s32 i = 0; i < num; ++i) {
            auto* target = mDucker.getTarget(i);
            const f32 old = target->getSettings()._0;
            const f32 volume = 1.0f - (1.0f - _b0->mTargets[i]->mSettings._0) * f;
            target->getSettings()._0 = volume;
            const f32 fader_volume = target->getFaderVolume();
            f32 value;
            if (volume > fader_volume)
                value = target->getSettings()._8 * (volume - fader_volume) / (1.0f - old);
            else
                value = _b0->mTargets[i]->mSettings._4;
            target->getSettings()._4 = value;
        }
    }
    mDucker.getSettings()._0 = _b0->mSettings._0;
    _c8 |= 1;
    _c0 = 0;
    _c4 = f;
}

void DuckingMgr::Ducker::activateMaybe() {
    _c8 |= 1;
    _c0 = 0;
}

void DuckingMgr::Ducker::deactivateMaybe(bool suspend) {
    _c8 &= ~1;
    if (suspend)
        mDucker.suspend();
}

void DuckingMgr::Ducker::activateAndResetMaybe() {
    _c8 |= 1;
    _c0 = 0;
    mDucker.resetState();
}

// Whether the ducker is still ducking: active, and either just started or ducking (state 1 or 2)
// with a target fader still moving.
bool DuckingMgr::Ducker::sub_710103E368() const {
    if (!(_c8 & 1))
        return false;
    if (_c0 == 0)
        return true;
    const s32 state = mDucker.getState();
    if (state != 1 && state != 2)
        return false;
    const s32 num = mDucker.getTargetNum();
    for (s32 i = 0; i < num; ++i) {
        if (mDucker.getTarget(i)->isFaderMoving())
            return true;
    }
    return false;
}

static const char* const sCustomDuckerNames[] = {"Evt:カスタム", "Evt:カスタム予備"};

// NON_MATCHING: token iterator and pointer-array temporaries use different stack slots,
// with minor loop and store scheduling differences.
DuckingMgr::Ducker* sub_71010421F0(DuckingMgr* mgr, DuckingMgr::DuckerType type,
                                  Unk_710103b704::StartParam& param) {
    if (type < DuckingMgr::DuckerType::cCustomEvt)
        return nullptr;
    auto* group_mgr = aal::SystemAccessor::getGroupMgr();
    if (!group_mgr)
        return nullptr;

    sead::FixedSafeString<128> name;
    sead::FixedPtrArray<aal::Group, 4> roots;
    s32 root_count = 0;
    for (auto it = param._0.tokenBegin(","), end = param._0.tokenEnd(","); it != end;) {
        it.getAndForward(&name);
        if (name.isEmpty())
            continue;
        auto* group = group_mgr->findGroup(name);
        if (group && root_count < 4) {
            roots.pushBack(group);
            ++root_count;
        }
    }

    sead::FixedPtrArray<aal::Group, 4> excluded;
    s32 excluded_count = 0;
    for (auto it = param._10.tokenBegin(","), end = param._10.tokenEnd(","); it != end;) {
        it.getAndForward(&name);
        if (name.isEmpty())
            continue;
        auto* group = group_mgr->findGroup(name);
        if (group && excluded_count < 4) {
            excluded.pushBack(group);
            ++excluded_count;
        }
    }

    sead::FixedPtrArray<aal::Group, 24> targets;
    s32 target_count = 0;
    for (auto& root : roots) {
        sead::FixedPtrArray<aal::Group, 24> expanded;
        sub_710105E5CC(&expanded, &excluded, &root);
        for (auto& group : expanded) {
            if (targets.indexOf(&group) == -1 && target_count < 24) {
                targets.pushBack(&group);
                ++target_count;
            }
        }
    }
    if (targets.isEmpty())
        return nullptr;

    // Native construction sets the name and settings but leaves _80 unset. The setup method
    // reads that flag only after rejecting an already initialized group ducker.
    Unk_71025022a0 request;
    request.mSettings = {param._2c, 0.0f, 0.0f};
    request.mGroups = &targets;
    request.mTargetSettings = {param._20, param._24, param._28, 1};
    const u32 name_index = u32(s32(type) - DuckingMgr::DuckerType::cCustomEvt);
    request.mName.copy(sCustomDuckerNames[name_index < 2 ? name_index : 0]);
    mgr->mHeap->freeAll();
    mgr->mDuckers[type].sub_710103E128(mgr->mHeap, &request);
    return &mgr->mDuckers[type];
}

}  // namespace ksys::snd
