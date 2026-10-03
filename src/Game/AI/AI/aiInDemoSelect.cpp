#include "Game/AI/AI/aiInDemoSelect.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtUnk_7100dc816c.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

InDemoSelect::InDemoSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InDemoSelect::~InDemoSelect() = default;

bool InDemoSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void InDemoSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!ksys::evt::sub_7100DC8684(mDemoFile_s, mDemoEntryPoint_s)) {
        changeChild("デモ終了", params);
        return;
    }

    const s32 delay_max = *mDemoRetDelayMax_s;
    _74 = sead::Mathi::min(delay_max, 0);
    _78 = sead::Mathi::max(delay_max, 0);
    resetDelay();

    if (mActor->get1a0() || (mActor->getMapObject() &&
                         mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000)))
        changeChild("デモ中", params);
    else if (*mOtherDemoNoRun_s)
        changeChild("非参加デモ", params);
    else
        changeChild("デモ終了", params);
}

void InDemoSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (child->isFinished())
            setFinished();
        else
            setFailed();
        return;
    }
    if (!*mForceChangeDemo_s && !child->isChangeable())
        return;

    if (isCurrentChild("デモ中")) {
        if (!ksys::evt::sub_7100DC8684(mDemoFile_s, mDemoEntryPoint_s)) {
            if (updateDelay())
                changeChild("デモ終了");
            return;
        }
        resetDelay();
        if (mActor->get1a0())
            return;
        if (auto* map_obj = mActor->getMapObject()) {
            if (map_obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
                return;
        }
        if (*mOtherDemoNoRun_s)
            changeChild("非参加デモ");
        return;
    }

    const bool is_non_participating = isCurrentChild("非参加デモ");
    const bool in_demo_file = ksys::evt::sub_7100DC8684(mDemoFile_s, mDemoEntryPoint_s);
    if (is_non_participating) {
        if (!in_demo_file) {
            if (updateDelay())
                changeChild("デモ終了");
            return;
        }
        resetDelay();
        if (mActor->get1a0()) {
            changeChild("デモ中");
            return;
        }
        auto* map_obj = mActor->getMapObject();
        if (!map_obj)
            return;
        if (map_obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000))
            changeChild("デモ中");
        return;
    }

    if (!in_demo_file)
        return;
    resetDelay();
    if (mActor->get1a0()) {
        changeChild("デモ中");
        return;
    }
    if (auto* map_obj = mActor->getMapObject()) {
        if (map_obj->getFlags0().isOn(ksys::map::Object::Flag0::_20000)) {
            changeChild("デモ中");
            return;
        }
    }
    if (*mOtherDemoNoRun_s)
        changeChild("非参加デモ");
    else
        changeChild("デモ中");
}

void InDemoSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InDemoSelect::loadParams_() {
    getStaticParam(&mDemoRetDelayMax_s, "DemoRetDelayMax");
    getStaticParam(&mOtherDemoNoRun_s, "OtherDemoNoRun");
    getStaticParam(&mForceChangeDemo_s, "ForceChangeDemo");
    getStaticParam(&mDemoFile_s, "DemoFile");
    getStaticParam(&mDemoEntryPoint_s, "DemoEntryPoint");
}

}  // namespace uking::ai
