#include "Game/AI/AI/aiTargetBeatGetDrop.h"
#include "Game/AI/aiAwarenessFilters.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

ksys::act::BaseProcLink* sub_71005E0F68(ksys::act::Actor* actor);

namespace uking::ai {

TargetBeatGetDrop::TargetBeatGetDrop(const InitArg& arg) : TargetBeatCheck(arg) {}

TargetBeatGetDrop::~TargetBeatGetDrop() = default;

bool TargetBeatGetDrop::init_(sead::Heap* heap) {
    return TargetBeatCheck::init_(heap);
}

void TargetBeatGetDrop::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetBeatCheck::enter_(params);
    _6c = false;
}

void TargetBeatGetDrop::calc_() {
    if (isCurrentChild("未撃破")) {
        _60 = sub_71005D9330(mActor);
        TargetBeatCheck::calc_();
        return;
    }
    if (!_6c)
        _6c = sub_71005E0F68(mActor)->hasProcInCalcState();
    sub_71005BCCE0();
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (_50.hasProcInCalcState())
            sub_71005BCF48();
        else if (child->isFinished())
            setFinished();
        else
            setFailed();
    } else {
        child->isChangeable();
    }
}

// NON_MATCHING: Accessor cleanup branches merge and translation loads are scheduled differently.
bool TargetBeatGetDrop::sub_71005BCCE0() {
    if (_50.hasProcInCalcState()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_50, &accessor);
        if (!accessor.sub_7100D10E6C(30) &&
            !sub_71005DEC08(&_50, mActor, 999.0f, 999.0f, sead::Mathf::pi()))
            return false;
    }

    _50.reset();
    auto* actor = mActor;
    if (!actor || !actor->getAwareness())
        return false;

    f32 distance = *mSearchDist_s;
    Unk_7102451420 filter;
    filter._28 = actor;
    auto* entries = &actor->getAwareness()->_8;
    for (auto* entry = ksys::act::sub_7100D7EEE8(entries, &filter); entry;
         entry = ksys::act::sub_7100D7EEE8(entries, &filter)) {
        auto* link = &entry->_0.mLink;
        if (!link->hasProcInCalcState())
            continue;
        {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            if (accessor.sub_7100D10E6C(30) ||
                sub_71005DEC08(link, mActor, 999.0f, 999.0f, sead::Mathf::pi()))
                continue;
        }
        const sead::Vector3f position = entry->_58.getTranslation();
        const f32 candidate_distance = (_60 - position).length();
        if (candidate_distance < distance && sub_710072E154(mActor, position, nullptr, -1)) {
            _50 = *link;
            distance = candidate_distance;
        }
    }
    return _50.hasProc();
}

void TargetBeatGetDrop::sub_71005BCF48() {
    // C++14 evaluation order: the original evaluates the destination first
    _40.operator=(_50);
    _50.reset();
    ksys::act::ai::InlineParamPack params;
    params.addActor(_40, "TargetBait", -1);
    params.addBool(false, "IsNotice", -1);
    changeChild("ドロップ取得", &params);
}

void TargetBeatGetDrop::leave_() {
    TargetBeatCheck::leave_();
}

void TargetBeatGetDrop::loadParams_() {
    TargetBeatCheck::loadParams_();
    getStaticParam(&mSearchDist_s, "SearchDist");
}

bool TargetBeatGetDrop::isChangeable() const {
    if (isCurrentChild("ドロップ取得") && !_6c)
        return false;
    return ksys::act::ai::Ai::isChangeable();
}

}  // namespace uking::ai
