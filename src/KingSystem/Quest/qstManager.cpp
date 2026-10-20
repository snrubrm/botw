
#include "KingSystem/Quest/qstManager.h"
#include "KingSystem/Quest/qstActorData.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::qst {

// Initialised by the TU's static initialiser at 0x7100fd7dc4.
static sead::FixedSafeString<32> sManagerName("ksys::qst::Manager");
static sead::FixedSafeString<128> sQuestPackPath("Quest/QuestProduct.bquestpack");
static sead::FixedSafeString<32> sResetName("リセット");

void Manager::resetAndLoadQuestInfo() {
    _44 = 0;
    _48.freeBuffer();
    mQuests.freeBuffer();
    if (mHandle.isSuccess())
        return;
    mHandle.unloadAndResetUnitFlag20000();
    res::LoadRequest req;
    req._22 = true;
    req.mRequester = "qst::Manager";
    mHandle.requestLoad(sQuestPackPath, &req);
    mFlags |= 2;
}

bool Manager::sub_7100FD7820() {
    if (mHandle.isReady()) {
        mFlags &= ~2;
        if (mHandle.isSuccess())
            mFlags |= 1;
        return true;
    }
    if (mHandle.isReadyOrNeedsParse())
        mHandle.parseResource(nullptr);
    return false;
}

// NON_MATCHING: the two final u32 stores merge to an unaligned u64 store rather than stp.
void Manager::prepareFirstTimeGenStage() {
    _28 = _2c;
    mFlags = 0;
    _2c = 1;
    _30 = 0;
}

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

Manager::~Manager() {
    cleanUp();
    util::safeDeleteHeap(mHeap);
}

void Manager::init(sead::Heap* heap) {
    if (sDisable)
        return;

    mHeap = util::DualHeap::tryCreate(0x99999, "QuestHeap", heap, util::getDebugHeap(), 8,
                                      sead::Heap::cHeapDirection_Forward, true);
    cleanUp();

    _e4 = -0x51;
    mFlags = 0;
    _28 = _2c;
    _2c = 0;
    _30 = 0;
}

void Manager::cleanUp() {
    _44 = 0;
    _48.freeBuffer();
    mQuests.freeBuffer();
    mHandle.unloadAndResetUnitFlag20000();
}

bool Manager::sub_7100FD7460(const sead::SafeString& name) const {
    for (s32 i = 0; i < _48.size(); ++i) {
        const auto* target = _48[i];
        if (target && target->enabled && target->name == name)
            return true;
    }
    return false;
}

// NON_MATCHING: returns the cached quest pointer and removes the redundant final bounds check.
Quest* Manager::sub_7100FD7610(const sead::SafeString& name) const {
    const u32 hash = sead::HashCRC32::calcStringHash(name);
    for (s32 i = 0; i < mQuests.size(); ++i) {
        auto* quest = mQuests[i];
        if (quest->mNameHash == hash)
            return quest;
    }
    return nullptr;
}

bool Manager::isQuestActor(act::Actor* actor) const {
    for (int i = 0; i < mQuests.size(); ++i) {
        const auto* quest = mQuests[i];
        if (quest->x_6(actor))
            return true;
    }
    return false;
}

// NON_MATCHING: leftovers from a stripped debug function
void Manager::auto0(act::Actor* actor) {
    if (actor == nullptr)
        return;

    for (int i = 0; i < mQuests.size(); ++i) {
        Quest* quest = mQuests[i];
        if (quest->_c != 2 && quest->flagStuff())
            quest->x_9(actor);
    }
}

bool Manager::auto4(act::Actor* actor) const {
    auto end = mQuests.end();
    for (auto it = mQuests.begin(); it != end; ++it) {
        if (it->_c != 2 && it->flagStuff() && !it->x_8(actor))
            return false;
    }
    return true;
}

void Manager::sub_7100FD78B0(const sead::SafeString& quest_name) {
    setQuestStep(quest_name, "Ready", false, false, false);
}

// NON_MATCHING: loops are nonmatching
bool Manager::sub_7100FD78F8() {
    s32 size = mQuests.size();
    u32 data_count = 0;

    for (int i = 0; i < size; ++i) {
        data_count += mQuests[i]->_148;
    }

    if (data_count == 0)
        return true;
    if (!_48.tryAllocBuffer(data_count, mHeap, 8))
        return false;

    for (int i = 0; i < size; ++i) {
        s32 num2 = mQuests[i]->_148;
        for (int j = 0; j < num2; ++j) {
            const CameraTarget* data = mQuests[i]->sub_7100FDA5F8(j);
            if (data != nullptr) {
                _48.pushBack(data);
            }
        }
    }
    return true;
}

bool Manager::sub_7100FD7B30(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                             bool setAocVersionFlag1) {
    return setQuestStep(quest_name, step_name, false, false, setAocVersionFlag1);
}

bool Manager::setQuestStepFromEvent(const sead::SafeString& quest_name,
                                    const sead::SafeString& step_name, bool force_run_telop,
                                    bool setAocVersionFlag1) {
    return setQuestStep(quest_name, step_name, true, force_run_telop, setAocVersionFlag1);
}

bool Manager::setQuestStep(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                           bool copy_name, bool force_run_telop, bool setAocVersionFlag1) {
    u32 hash = sead::HashCRC32::calcStringHash(quest_name);
    for (auto it = mQuests.begin(), end = mQuests.end(); it != end; ++it) {
        if ((it->_c != 1 && it->_c != 2) || it->mNameHash != hash)
            continue;

        it->setField31();

        it->_e8.copy(step_name);

        it->_e0 = false;
        it->mForceRunTelop = false;

        if (copy_name) {
            it->_e0 = true;
            if (step_name.isEmpty())
                it->_e8.copy(it->x_11());
        }
        if (force_run_telop)
            it->mForceRunTelop = true;
        if (setAocVersionFlag1)
            it->mAocVersionFlags |= 1;

        return true;
    }

    return false;
}

}  // namespace ksys::qst
