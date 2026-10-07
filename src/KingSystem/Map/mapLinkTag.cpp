#include "KingSystem/Map/mapLinkTag.h"
#include <algorithm>
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/System/MCMgr.h"
#include "KingSystem/System/SystemTimers.h"

namespace ksys::map {

// NON_MATCHING: only the block order of the getS32 buffer 1 path (same instructions; the original tests the 0x8000 flag with the
// opposite polarity there).
bool isFlagSet(bool* value, bool a, const Object* obj) {
    if (!obj)
        return false;

    const auto hash = obj->getRevivalGameDataFlagHash();
    if (hash == gdt::InvalidHandle)
        return false;

    const auto flags = obj->getFlags();
    *value = false;
    auto* mgr = gdt::Manager::instance();
    if (flags.isOn(Object::Flag::IncrementSave)) {
        s32 count = 0;
        const bool result = a ? mgr->getS32Buffer1Debug(hash, &count) : mgr->getS32(hash, &count, true);
        if (result && count >= 1)
            *value = true;
        return result;
    }
    if (a)
        return mgr->getBoolBuffer1Debug(hash, value);
    return mgr->getBool(hash, value, true);
}

bool isLinkTagNAndOrNOr(const sead::SafeString& name) {
    return name == "LinkTagNAnd" || name == "LinkTagNOr";
}

// NON_MATCHING: only the order of the constant stores of the members (the original stores 0x1dd / 0x1df, then 0x1e8, then
// the 8 bytes at 0x1e0).
LinkTag* LinkTag::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) LinkTag(arg);
}

LinkTag::LinkTag(const CreateArg& arg) : BaseProc(arg) {
    getJobHandler(act::JobType::Calc3) = &mJob;
}

LinkTag::~LinkTag() {
    if (getSceneStatus() != 4)
        _1ec.load();
}

// NON_MATCHING: the whole name chain and the parameter reads match; the differences are the position of the `bool` store before
// the NoChangeSignal read, the SaveFlagOnOffType case blocks (the original loads / ors `_1e0` in each case; ours selects the mask
// first) and the end (the original stores `_1e0 | 0x10` and later `_1e0 | 0x30`, ours one store with the final value).
act::BaseProc::InitResult LinkTag::init_() {
    if (mName == "LinkTagOr")
        _1dc = 1;
    else if (mName == "LinkTagNOr")
        _1dc = 3;
    else if (mName == "LinkTagNAnd")
        _1dc = 2;
    else if (mName == "LinkTagXOr")
        _1dc = 4;
    else if (mName == sead::SafeString("LinkTagAnd"))
        _1dc = 0;
    else if (mName == sead::SafeString("LinkTagCount"))
        _1dc = 5;
    else if (mName == sead::SafeString("LinkTagPulse"))
        _1dc = 6;
    else if (mName == sead::SafeString("LinkTagNone"))
        _1dc = 7;

    if (mName == "LinkTagNAnd" || mName == "LinkTagNOr")
        _1e0 |= 4;

    bool no_change_signal = false;
    if (_1f8.tryGetParamBoolByKey(&no_change_signal, "NoChangeSignal") && no_change_signal)
        _1e0 |= 0x40;

    s32 save_flag_on_off_type = 0;
    if (_1f8.tryGetParamIntByKey(&save_flag_on_off_type, "SaveFlagOnOffType")) {
        switch (save_flag_on_off_type) {
        case 1:
            _1e0 |= 0x100;
            break;
        case 2:
            _1e0 |= 0x200;
            break;
        }
    }

    bool flag_value = false;
    isFlagSet(&flag_value, false, mObj);
    const bool is_set = flag_value;
    updateIsFlagSetFlag(is_set, true, true);
    if (is_set) {
        _1e0 |= 0x10;
        _1d0 = ~u64(0);
        _1e0 |= 0x20;
        _1d8 = ~0u;
    } else {
        _1e0 &= ~0x10;
        _1e0 &= ~0x20;
        _1d8 = 0;
        _1d0 = 0;
    }
    return InitResult::Ok;
}

void LinkTag::calc() {
    if (mState == State::Delete)
        return;
    if (_1de)
        return;

    const s8 array_idx = act::BaseProcMgr::instance()->getCurrentExtraJobArrayIdx();
    u32 frame = 0;
    if (auto* timers = SystemTimers::instance())
        frame = timers->mFrameCounter;
    const u32 prev_frame = _1e4;
    _1e4 = frame;

    switch (_1dc) {
    case 5:
        calcCount(frame != prev_frame);
        break;
    case 6:
        calcPulse(frame != prev_frame);
        break;
    case 7:
        break;
    default:
        calcOther(frame != prev_frame);
        break;
    }

    if (!(_1e0 & 1)) {
        _1e0 |= 1;
        if (mObj && mObj->getLinkData())
            mObj->getLinkData()->setNumExecLinkTagTo1();
    }

    _1e0 &= ~0x1000;
    _1ec.setBitOff(array_idx ^ 1);
}

// NON_MATCHING: the original keeps the branch on bit 6 (and extracts the bits with ubfx); ours folds both paths into csel.
bool LinkTag::sub_7100D39420(bool a) const {
    if (_1e0 & 0x40)
        return ((_1e0 >> 5) & 1) ^ ((_1e0 & 4) >> 2);
    if (!a)
        return ((_1e0 >> 3) & 1) ^ ((_1e0 & 4) >> 2);
    return (_1e0 >> 10) & 1;
}

bool LinkTag::sub_7100D39D60(sead::Matrix34f* mtx) {
    if (_1df >= 0 && mObj && mObj->getLinkData()) {
        auto* actor = mObj->getLinkData()->mLinksToSelf.links[_1df].getObjectActor();
        if (actor) {
            *mtx = actor->getMtx();
            return true;
        }
    }
    return false;
}

void LinkTag::sub_7100D39DE4() {
    if (mObj && deleteLater(DeleteReason::_0))
        mObj->setFlags0(Object::Flag0::ActorCreated);
}

bool LinkTag::sub_7100D39E2C() {
    if (mObj && mObj->getLinkData())
        return mObj->getLinkData()->sub_7100D4FBF8();
    return true;
}

// NON_MATCHING: only the count accumulation (the original selects `count + 1` with csinc; ours folds the bool into an add) and
// the register assignment of the loop counters.
void LinkTag::calcCount(bool frame_changed) {
    if (!(_1e0 & 1))
        return;
    if (!mObj)
        return;

    u8 count = 0;
    if (auto* link_data = mObj->getLinkData()) {
        auto& links = link_data->mLinksToSelf.links;
        const s32 num = std::min(links.size(), 0x60);
        for (s32 i = 0; i < num; ++i) {
            if (links[i].type <= MapLinkDefType::ChangeAtnSig && isTriggered(&links[i], i))
                ++count;
        }
    }

    _1e0 &= ~0x10;
    if (count != _1e2) {
        _1e2 = count;
        setS32ByIdxForLinkTag(gdt::Manager::instance(), count, mObj->getRevivalGameDataFlagHash());
        updateIsFlagSetFlag(s8(_1e2) > 0, false, frame_changed);
    }
}

void LinkTag::finalizeInit_(InitContext* context) {
    if (mObj)
        mObj->registerBaseProc(this);
    BaseProc::finalizeInit_(context);
}

act::BaseProc::PreDeletePrepareResult LinkTag::prepareForPreDelete_() {
    if (mObj) {
        if (auto* link_data = mObj->getLinkData(); link_data && (s16(_1e0) < 0)) {
            link_data->x_3(true);
            link_data->sub_7100D4F884();
        }
        mObj->unlinkProc(true);
        mObj = nullptr;
    }
    return PreDeletePrepareResult::Done;
}

bool LinkTag::startPreparingForPreDelete_() {
    if (!BaseProc::startPreparingForPreDelete_())
        return false;
    if (_1ec.load() == 0)
        return true;

    auto* link = &mJob.getLink();
    if (_1ec.isBitOn(0)) {
        if (act::BaseProcMgr::instance()->hasExtraJobLink(link, 0))
            return false;
        _1ec.setBitOff(0);
    }
    if (_1ec.isBitOn(1)) {
        if (act::BaseProcMgr::instance()->hasExtraJobLink(link, 1))
            return false;
        _1ec.setBitOff(1);
    }
    return true;
}

bool LinkTag::canWakeUp_() {
    if (mObj) {
        if (auto* link_data = mObj->getLinkData()) {
            if (s16(_1e0) >= 0) {
                _1e0 |= 0x8000;
                link_data->x_8(true);
                link_data->sub_7100D4F824();
            }
            if (!link_data->x_7(true))
                return false;
        }
        if (mObj) {
            if (auto* link_data = mObj->getLinkData()) {
                if (link_data->findLinkWithType(MapLinkDefType::MtxCopyCreate))
                    _1e0 |= 2;
            }
        }
    }
    return true;
}

act::BaseProc::IsSpecialJobTypeResult LinkTag::isSpecialJobType_(act::JobType type) {
    return IsSpecialJobTypeResult::No;
}

bool LinkTag::hasJobType_(act::JobType type) {
    if (type != act::JobType::Calc3)
        return false;
    if (_1e0 & 0x4000)
        return true;
    if (mObj && mObj->getRevivalGameDataFlagHash() != gdt::InvalidHandle)
        return true;
    return _1dc == 6;
}

inline void LinkTag::queueCalcJob_() {
    if (mState == State::Delete)
        return;

    const s8 array_idx = act::BaseProcMgr::instance()->getCurrentExtraJobArrayIdx();
    if (mStateFlags.isOn(StateFlags::RequestDelete))
        return;
    if (_1ec.setBitOn(array_idx))
        act::BaseProcMgr::instance()->queueExtraJobPush(&mJob.getLink());
}

void LinkTag::queueExtraJobPush_(act::JobType type, int idx) {
    if (type != act::JobType::Calc3)
        return;

    _1ec.setBitOff(idx ^ 1);
    queueCalcJob_();
}

// NON_MATCHING: only the position of the `_1dd = 0` store (the original stores it before computing `_1e0 | 0x80`).
void LinkTag::onEnterCalc_() {
    if (_1dc == 6) {
        _1e0 |= 0x4000;
        if (mObj && mObj->getLinkData()) {
            auto& links = mObj->getLinkData()->mLinksToSelf.links;
            const s32 num = std::min(links.size(), 0x60);
            for (s32 i = 0; i < num; ++i) {
                if (links[i].type <= MapLinkDefType::ChangeAtnSig && isTriggered(&links[i], i))
                    ++_1e2;
            }
        }
        _1e0 &= ~0x10;
    }

    _1e0 &= 0xef7e;
    _1dd = 0;
    _1e0 |= 0x80;
    if (mObj) {
        if (mObj->getRevivalGameDataFlagHash() != gdt::InvalidHandle)
            _1e0 |= 0x4080;
        queueCalcJob_();
    }
}

bool LinkTag::shouldSkipJobPush_(act::JobType type) {
    if (_1ec.isBitOn(act::BaseProcMgr::instance()->getCurrentExtraJobArrayIdx()))
        return true;
    if (_1e0 & 0x1000)
        return false;
    return !(_1e0 & 0x2000);
}

void LinkTag::onJobPush2_(act::JobType type) {
    if (auto* mc = MCMgr::instance()) {
        if (_1dd == mc->get1be4()) {
            _1e0 |= 0x1000;
        } else if (mObj) {
            bool value = false;
            if (isFlagSet(&value, true, mObj) && ((_1e0 >> 3) & 1) != value)
                _1e0 |= 0x1000;
        }
    }
    _1dd = -1;
}

}  // namespace ksys::map
