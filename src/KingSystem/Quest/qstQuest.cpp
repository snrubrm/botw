#include "KingSystem/Quest/qstQuest.h"
#include <utility/aglParameter.h>
#include "KingSystem/Quest/qstActorData.h"

namespace ksys::qst {

// chunks missing
Quest::~Quest() {
    mSteps.freeBuffer();
}

// NON_MATCHING
Quest::Quest(const sead::SafeString& name, sead::Heap* heap) : mName(name), mHeap(heap) {
    _8 = 0;
    _c = 0;
    _10 = 0;
    mNameHash = agl::utl::ParameterBase::calcHash(mName);
    mAocVersionFlags = 0;
}

void Quest::initFlags(gdt::Manager* gdm) {
    if (gdm == nullptr)
        return;

    mReady = gdm->getBoolHandle([&] {
        sead::FixedSafeString<64> ready;
        ready.format("%s_Ready", mName.cstr());
        return ready;
    }());

    mCancelled = gdm->getBoolHandle([&] {
        sead::FixedSafeString<64> cancelled;
        cancelled.format("%s_Cancelled", mName.cstr());
        return cancelled;
    }());

    switch (mQuestDependencyFlagType) {
    default:
        mDependencyFlag = gdt::InvalidHandle;
        break;
    case 0:
        mDependencyFlag = gdm->getBoolHandle(mQuestDependencyFlag);
        break;
    case 1:
        mDependencyFlag = gdm->getF32Handle(mQuestDependencyFlag);
        break;
    case 2:
        mDependencyFlag = gdm->getS32Handle(mQuestDependencyFlag);
        break;
    }
}

void Quest::setField31() {
    _31 = 1;
}

bool Quest::x_1() const {
    bool result = false;

    if (gdt::Manager::instance() == nullptr || mCancelled == gdt::InvalidHandle)
        return result;

    gdt::Manager::instance()->getBool(mCancelled, &result, true);
    return result;
}

void Quest::x_3() {
    if (_c == 1 || _c == 2)
        return;

    auto handle = mReady;
    if (handle != ksys::gdt::InvalidHandle) {
        bool result = false;
        auto* gdm = gdt::Manager::instance();
        if (gdm != nullptr) {
            if (gdm->getBool(handle, &result, true); !result)
                gdm->setBoolNoCheck(true, handle);
        }
    }
    _8 = _c;
    _c = 1;
    _10 = 0;
}

bool Quest::x_6(act::Actor* actor) const {
    if (!isStepUnderSize() || !mSteps[_140]->attention_off)
        return false;

    return mSteps[_140]->sub_7100FDB89C(actor);
}

bool Quest::x_7() const {
    if (!isStepUnderSize())
        return false;

    return mSteps[_140]->attention_off;
}

bool Quest::x_8(act::Actor* actor) {
    if (isStepUnderCapacity())
        mSteps[_140]->sub_7100FDB538(actor, mName);

    return true;
}

void Quest::x_9(act::Actor* actor) {
    if (isStepUnderCapacity())
        mSteps[_140]->sub_7100FDB794(actor);
}

const char* Quest::x_11() {
    if (!isNextStepUnderSize())
        return &sead::SafeString::cNullChar;

    return mSteps[_140 + 1]->name;
}

void Quest::formatQLNameKey(sead::BufferedSafeString* out) const {
    out->format("QL_%s_Name", mName.cstr());
}

// NON_MATCHING: the original keeps the unsigned index check of mSteps(i) inside the loop; clang folds it away here
// 0x7100fda5f8: the idx-th camera target counted across the actor data of all steps.
const CameraTarget* Quest::sub_7100FDA5F8(int idx) {
    if (idx < 0)
        return nullptr;
    for (int i = 0; i < mSteps.size() && idx >= 0; ++i) {
        const Step* step = mSteps(i);
        if (!step || !step->actor_data)
            continue;
        const int count = step->actor_data->targets.size();
        for (int j = 0; j < count; ++j) {
            if (idx == 0)
                return step->actor_data->getTarget(j);
            --idx;
        }
    }
    return nullptr;
}

bool Quest::sub_7100FDA678(sead::BufferedSafeString* out) const {
    const s32 idx = _140 > 0 ? _140 - 1 : -1;
    if (idx < 0 || sead::SafeString(mSteps(idx)->message_name).isEmpty())
        return false;

    if (idx == 0)
        out->format("QL_%s_Desc", mName.cstr());
    else
        out->format("QL_%s_%s", mName.cstr(), mSteps(idx)->message_name);
    return true;
}

}  // namespace ksys::qst
