#include "KingSystem/Map/mapLinkTag.h"
#include <algorithm>
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/System/MCMgr.h"
#include "KingSystem/System/SystemTimers.h"

namespace ksys::map {

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
