#include "Game/AI/AI/aiKeeseHangOnCeil.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KeeseHangOnCeil::KeeseHangOnCeil(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeeseHangOnCeil::~KeeseHangOnCeil() = default;

bool KeeseHangOnCeil::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KeeseHangOnCeil::enter_(ksys::act::ai::InlineParamPack* params) {
    _90.x();
    changeChild("張り付き");
}

bool KeeseHangOnCeil::isChangeable() const {
    return false;
}

void KeeseHangOnCeil::leave_() {
    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7E9BC(1);
        awareness->sub_7100D7E9BC(0);
    }
}

void KeeseHangOnCeil::loadParams_() {}

// NON_MATCHING: regalloc: we keep the address of the filter (`sp + 8`) in a callee-saved register across the calls, the
// original recomputes it for the destructor call and keeps the entry in x20 instead.
bool KeeseHangOnCeil::sub_710045258C(ksys::act::Unk_7100d78e50* out) {
    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return false;

    bool found = false;
    Unk_7102451470 filter{actor};
    while (auto* sensor = awareness->_260[1]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
        if (!entry)
            break;

        // called through a pointer in the original (not devirtualised)
        (&out->_0)->m14(&entry->_0);
        out->_58 = entry->_58;
        out->_88 = entry->_88;
        out->_94 = entry->_94;
        out->_a0 = entry->_a0;
        out->_a4 = entry->_a4;
        out->_a8 = entry->_a8;
        found = true;
        break;
    }
    return found;
}

void KeeseHangOnCeil::sub_7100452694(ksys::act::BaseProcLink* link, s32 a2, s32 a3,
                                     const sead::Vector3f* pos) {
    auto* actor = mActor;
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_38._18.mLock);
        auto& data = _38._18.mData;
        data._0 = *link;
        data._10.acquire(actor, false);
        data._20 = a2;
        data._24 = a3;
        data._28 = *pos;
        data._34 = 0;
    }

    if (auto* awareness = mActor->getAwareness()) {
        Unk_7102451448 filter;
        while (auto* entry = ksys::act::sub_7100D7EEE8(&awareness->_8, &filter)) {
            if (entry->_a8 < 10.0f) {
                ksys::act::ActorConstDataAccess accessor;
                ksys::act::acquireActor(&entry->_0.mLink, &accessor);
                _38.sub_710070DBB0(*accessor.getMessageTransceiverId(), true);
            }
        }
    }
}

bool KeeseHangOnCeil::sub_7100452800(ksys::act::Unk_7100d78e50* out) {
    if (sub_71005D9F70(mActor))
        return false;

    auto* actor = mActor;
    auto* awareness = actor->getAwareness();
    if (!awareness)
        return false;

    bool found = false;
    Unk_71024514c0 filter{actor};
    while (auto* sensor = awareness->_260[0]) {
        auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter);
        if (!entry)
            break;
        if (sub_71005D9FC0(&entry->_0.mLink))
            continue;

        // called through a pointer in the original (not devirtualised)
        (&out->_0)->m14(&entry->_0);
        out->_58 = entry->_58;
        out->_88 = entry->_88;
        out->_94 = entry->_94;
        out->_a0 = entry->_a0;
        out->_a4 = entry->_a4;
        out->_a8 = entry->_a8;
        found = true;
        break;
    }
    return found;
}

// NON_MATCHING: regalloc of the three unconditional `_90.x()` sites (shared `else` block of the sound state, and the
// two sound-found / sound-send paths): the original loads the vtable with a pre-indexed `ldr x8, [x0, #0x90]!` where
// we keep `this + 0x90` in x21.
void KeeseHangOnCeil::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("張り付き")) {
            if (child->isFailed()) {
                setFailed();
                return;
            }
            if (auto* awareness = mActor->getAwareness()) {
                awareness->sub_7100D7E9BC(1);
                awareness->sub_7100D7EAE4(0);
            }
            changeChild("待機", nullptr);
        } else if (isCurrentChild("降下")) {
            if (child->isFailed()) {
                setFailed();
                return;
            }
            setFinished();
        } else if (isCurrentChild("視界気づき")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("降下", &pack);
        } else {
            if (auto* awareness = mActor->getAwareness()) {
                awareness->sub_7100D7E9BC(1);
                awareness->sub_7100D7EAE4(0);
            }
            changeChild("待機", nullptr);
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("待機")) {
            ksys::act::Unk_7100d78e50 info;
            if (sub_710045258C(&info)) {
                sub_7100452694(&info._0.mLink, 1, info._a0, &info._88);
                if (auto* awareness = mActor->getAwareness()) {
                    awareness->sub_7100D7E9BC(1);
                    awareness->sub_7100D7E9BC(0);
                }
                if (_90._30 && _90._38.mData._20 == 1)
                    _90.x();
                changeChild("音気づき", nullptr);
            } else {
                ksys::act::BaseProcLink link;
                if (_90._30 && _90._38.mData._24 != 0 && _108 <= 0.0f) {
                    link = _90._38.mData._0;
                    sead::Vector3f pos;
                    pos = _90._38.mData._28;
                    sub_7100452694(&link, 1, _90._38.mData._24, &pos);
                    if (auto* awareness = mActor->getAwareness()) {
                        awareness->sub_7100D7E9BC(1);
                        awareness->sub_7100D7E9BC(0);
                    }
                    if (_90._30 && _90._38.mData._20 == 1)
                        _90.x();
                    changeChild("音気づき", nullptr);
                }
            }
        } else if (isCurrentChild("音気づき")) {
            ksys::act::Unk_7100d78e50 info;
            if (sub_7100452800(&info)) {
                sub_7100452694(&info._0.mLink, 0, info._a0, &info._88);
                sub_71005D8DE8(mActor, info._0.mLink, &info._58, nullptr);
                if (auto* awareness = mActor->getAwareness()) {
                    awareness->sub_7100D7E9BC(1);
                    awareness->sub_7100D7E9BC(0);
                }
                _90.x();
                changeChild("視界気づき", nullptr);
            } else {
                ksys::act::BaseProcLink link;
                if (sub_71005D9F70(mActor)) {
                    if (_90._30)
                        _90.x();
                } else if (_90._30) {
                    if (_90._38.mData._20 == 0 && _90._38.mData._24 == 2 && _108 <= 0.0f) {
                        link = _90._38.mData._0;
                        sead::Vector3f pos;
                    pos = _90._38.mData._28;
                        sub_7100452694(&link, 0, _90._38.mData._24, &pos);
                        sub_71005D8DE8(mActor, link, nullptr, nullptr);
                        if (auto* awareness = mActor->getAwareness()) {
                            awareness->sub_7100D7E9BC(1);
                            awareness->sub_7100D7E9BC(0);
                        }
                        _90.x();
                        changeChild("視界気づき", nullptr);
                    } else {
                        _90.x();
                    }
                }
            }
        }
    }

    if (_90._30)
        ksys::Timer::update(&_108, -1.0f);

    if (sub_71005D8F28(mActor))
        child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

bool KeeseHangOnCeil::handleMessage_(const ksys::Message* message) {
    if (_90._30 || !_90.m2(*message))
        return false;
    _108 = sead::GlobalRandom::instance()->getF32() * 8.0f;
    return true;
}

}  // namespace uking::ai
