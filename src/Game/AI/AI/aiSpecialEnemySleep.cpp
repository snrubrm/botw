#include "Game/AI/AI/aiSpecialEnemySleep.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"

namespace uking::ai {

SpecialEnemySleep::SpecialEnemySleep(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SpecialEnemySleep::~SpecialEnemySleep() = default;

bool SpecialEnemySleep::isChangeable() const {
    return (isCurrentChild("起き上がる") && getCurrentChild()->isFinishedOrFailed()) ||
           ((isCurrentChild("待機") || isCurrentChild("横になる")) &&
            getCurrentChild()->isChangeable());
}

bool SpecialEnemySleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpecialEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    _54 = ksys::Timer(*mAwakeDelayTime_s, *mAwakeDelayTime_s);
    _52 = false;
    if (auto* awareness = mActor->getAwareness()) {
        _50 = awareness->sub_7100D7E964();
        _51 = awareness->_260[0] ? awareness->_260[0]->_50 : false;
        awareness->enable();
    }

    if (mActor->getRootAi()->getI() == 5) {
        changeChild("横になる");
        return;
    }

    if (auto* awareness = mActor->getAwareness()) {
        awareness->sub_7100D7EAE4(0);
        awareness->sub_7100D7EAE4(2);
        if (!*mIsAwakenByHearing_s)
            awareness->sub_7100D7EAE4(1);
    }
    changeChild("睡眠");
}

void SpecialEnemySleep::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("横になる")) {
            if (child->isFailed()) {
                setFailed();
                return;
            }
            if (m36() || (_52 && _54.value <= sead::Mathf::epsilon())) {
                m34();
            } else {
                if (auto* awareness = mActor->getAwareness()) {
                    awareness->sub_7100D7EAE4(0);
                    awareness->sub_7100D7EAE4(2);
                    if (!*mIsAwakenByHearing_s)
                        awareness->sub_7100D7EAE4(1);
                }
                changeChild("睡眠");
            }
        } else if (isCurrentChild("睡眠")) {
            m34();
        } else if (isCurrentChild("起き上がる")) {
            if (*mIsWaitAfterAwaken_s)
                m35();
            else
                setFinished();
        } else {
            setFinished();
        }
    } else if (child->isChangeable()) {
        if (isCurrentChild("横になる")) {
            int x = -1;
            if (auto* entry = m37(&x)) {
                m38(x, entry);
                if (*mIsWaitAfterAwaken_s)
                    m35();
                else
                    setFinished();
            }
        } else if (isCurrentChild("睡眠")) {
            if (_52 && _54.value <= sead::Mathf::epsilon()) {
                m34();
            } else {
                int x = -1;
                if (auto* entry = m37(&x)) {
                    m38(x, entry);
                    _52 = true;
                }
            }
        }
    }

    if (isCurrentChild("睡眠") && m36())
        m34();

    if (_52)
        _54.update();
}

void SpecialEnemySleep::leave_() {
    if (isActorDeletedOrDeleting())
        return;
    auto* awareness = mActor->getAwareness();
    if (!awareness)
        return;
    if (_50) {
        awareness->sub_7100D7E9BC(0);
    } else {
        awareness->sub_7100D7EBE0(1.0f);
        awareness->disable();
    }
}

void SpecialEnemySleep::loadParams_() {
    getStaticParam(&mAwakeDelayTime_s, "AwakeDelayTime");
    getStaticParam(&mIsAwakenByHearing_s, "IsAwakenByHearing");
    getStaticParam(&mIsWaitAfterAwaken_s, "IsWaitAfterAwaken");
}

// NON_MATCHING: register allocation only (ours keeps &filter in a callee-saved register for the destructor
// calls, one register more than the original)
ksys::act::Unk_7100d78e50* SpecialEnemySleep::m37(int* x) {
    auto* awareness = mActor->getAwareness();
    if (!awareness || awareness->_300 == 0)
        return nullptr;

    ksys::map::AutoPlacementMgr* mgr;
    {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        mgr = ksys::map::AutoPlacementMgr::instance();
        if (mgr && mgr->isNonAutoPlacement(pos, true))
            return nullptr;
    }

    {
        Unk_71024514e8 filter{mActor, nullptr};
        if (auto* sensor = awareness->_260[1]) {
            if (auto* entry = ksys::act::sub_7100D7EEE8(&sensor->_8, &filter)) {
                if (x)
                    *x = 1;
                return entry;
            }
        }
    }

    ksys::act::Unk_7100d78e50* entry;
    {
        Unk_71024514c0 filter{mActor};
        mgr = ksys::map::AutoPlacementMgr::instance();
        if (mgr) {
            do {
                entry = nullptr;
                if (!awareness->_260[0])
                    break;
                entry = ksys::act::sub_7100D7EEE8(&awareness->_260[0]->_8, &filter);
            } while (entry && mgr->isNonAutoPlacement(entry->_88, true));
        } else {
            entry = nullptr;
            if (awareness->_260[0])
                entry = ksys::act::sub_7100D7EEE8(&awareness->_260[0]->_8, &filter);
        }
    }
    if (entry) {
        if (x)
            *x = 0;
        return entry;
    }

    {
        Unk_71024514c0 filter{mActor};
        mgr = ksys::map::AutoPlacementMgr::instance();
        if (mgr) {
            do {
                entry = nullptr;
                if (!awareness->_260[3])
                    break;
                entry = ksys::act::sub_7100D7EEE8(&awareness->_260[3]->_8, &filter);
            } while (entry && mgr->isNonAutoPlacement(entry->_88, true));
        } else {
            entry = nullptr;
            if (awareness->_260[3])
                entry = ksys::act::sub_7100D7EEE8(&awareness->_260[3]->_8, &filter);
        }
    }
    if (entry && x)
        *x = 3;
    return entry;
}

void SpecialEnemySleep::m35() {
    if (_51) {
        if (auto* awareness = mActor->getAwareness())
            awareness->sub_7100D7E9BC(0);
    }
    sead::Vector3f pos;
    if (m39(&pos)) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(pos, "TargetPos", -1);
        changeChild("待機", &pack);
    } else {
        changeChild("待機");
    }
}

}  // namespace uking::ai
