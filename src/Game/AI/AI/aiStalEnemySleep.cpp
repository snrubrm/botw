#include "Game/AI/AI/aiStalEnemySleep.h"
#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

StalEnemySleep::StalEnemySleep(const InitArg& arg) : SpecialEnemySleep(arg) {}

StalEnemySleep::~StalEnemySleep() = default;

bool StalEnemySleep::init_(sead::Heap* heap) {
    return SpecialEnemySleep::init_(heap);
}

void StalEnemySleep::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getMtx().getBase(_70, 0);
    _70.normalize();
    SpecialEnemySleep::enter_(params);
    _7c = isRootAiParamINot5();
}

void StalEnemySleep::calc_() {
    SpecialEnemySleep::calc_();
    if (!isCurrentChild("睡眠") || !mActor->sub_7100EE1E94())
        return;
    if (_7c) {
        if (auto* lod = mActor->getLodState()) {
            if (lod->_1c < 2 || lod->_1c > 5) {
                const sead::Vector3f pos = mActor->getMtx().getTranslation();
                if (!visibilityCheckMaybe(pos, 1.0f)) {
                    mActor->deleteEx(ksys::act::Actor::DeleteType::_1,
                                     ksys::act::BaseProc::DeleteReason::_0);
                    return;
                }
            } else {
                mActor->deleteEx(ksys::act::Actor::DeleteType::_1,
                                 ksys::act::BaseProc::DeleteReason::_0);
                return;
            }
        }
    }
    _7c = false;
    if (auto* unit = sub_7100726FF4(mActor))
        unit->_8.setBit(4);
}

void StalEnemySleep::leave_() {
    SpecialEnemySleep::leave_();
    _7c = false;
}

void StalEnemySleep::loadParams_() {
    SpecialEnemySleep::loadParams_();
    getStaticParam(&mUseAwarenessWakeUp_s, "UseAwarenessWakeUp");
    getStaticParam(&mUseNoticeActiveWakeUp_s, "UseNoticeActiveWakeUp");
}

bool StalEnemySleep::m36() {
    if (!*mUseNoticeActiveWakeUp_s)
        return false;
    auto* unit = sub_7100726628(mActor);
    if (!unit)
        return false;
    return unit->_8.isOnBit(6);
}

ksys::act::Unk_7100d78e50* StalEnemySleep::m37(int* x) {
    if (!*mUseAwarenessWakeUp_s)
        return nullptr;
    return SpecialEnemySleep::m37(x);
}

bool StalEnemySleep::m39(sead::Vector3f* pos) {
    if (!pos)
        return false;
    pos->set(_70);
    return true;
}

void StalEnemySleep::m38(int x, ksys::act::Unk_7100d78e50* entry) {
    if (entry)
        _70.set(entry->_88);
}

}  // namespace uking::ai
