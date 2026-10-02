#include "Game/AI/AI/aiKeepBackSelect.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

KeepBackSelect::KeepBackSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeepBackSelect::~KeepBackSelect() = default;

// NON_MATCHING: regalloc (this+0x70 computed into x8 before the name argument)
bool KeepBackSelect::init_(sead::Heap* heap) {
    if (!mNodeName_s.isEmpty())
        _70.search(mActor->getModel(), mNodeName_s);
    return true;
}

void KeepBackSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 keep_time = *mKeepTime_s;
    _ac = keep_time;
    _b0 = keep_time;
    _a8 = keep_time;
    changeChild("角度内", params);
}

void KeepBackSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KeepBackSelect::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mBaseAxis_s, "BaseAxis");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getStaticParam(&mXZOnly_s, "XZOnly");
    getStaticParam(&mNodeName_s, "NodeName");
    getStaticParam(&mLocalOffset_s, "LocalOffset");
}

}  // namespace uking::ai
