#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::evt {

// 0x7100dc8ca8
EventXlinkInfo::EventXlinkInfo() = default;

// 0x7100dc8db4
EventXlinkInfo::~EventXlinkInfo() {
    auto* proc = _18.getProc(nullptr);
    if (sead::IsDerivedFrom<act::Actor>(proc))
        proc->deleteLater(act::BaseProc::DeleteReason::_0);
    _8.deleteProc();
    _28.freeBuffer();
    _38.freeBuffer();
}

// 0x7100dc8ee8
void EventXlinkInfo::init(bool a1, const al::ByamlIter& iter, sead::Heap* heap, res::Handle* pack) {
    const char* elink_user = "";
    iter.tryGetStringByKey(&elink_user, "elink_user");
    const sead::SafeString elink = elink_user;
    const char* slink_user = "";
    iter.tryGetStringByKey(&slink_user, "slink_user");
    const sead::SafeString slink = slink_user;

    if (elink.isEmpty() && slink.isEmpty())
        return;

    mHeap = heap ? heap : act::BaseProcHeapMgr::instance()->getHeap();
    _180 = a1;
    _48 = slink;
    _c8 = elink;

    if (!slink.isEmpty()) {
        snd::SoundMgr::instance()->_60->loadBars(slink, &_a0, heap, false, false, pack);
        _c0 = true;
    }

    if (!elink.isEmpty()) {
        res::LoadRequest req;
        req.mLoadDataAlignment = 0x4000;
        req.mRequester = elink;
        req.mPackHandle = pack;
        sead::FormatFixedSafeString<128> path("Effect/%s.esetlist", elink.cstr());
        _120.requestLoad(path, &req);
        _170 = true;
    }
    _181 = true;
}

// NON_MATCHING: block placement (the original moves the XLink reader block after the shared return and masks the
// returned bool there).
// 0x7100dc9208: loads the resources and the actor; true once done (or when there is nothing to load)
bool EventXlinkInfo::finishLoad(bool a1) {
    if (_c8.isEmpty() && _48.isEmpty())
        return true;
    if (!_181)
        return false;

    if (_170) {
        if (!_120.isReady())
            return false;
        _170 = false;
    }

    bool done;
    if (_182) {
        done = false;
    } else {
        done = a1;
        if (sub_7100DC9404()) {
            done = false;
            _182 = true;
        }
    }

    if (_c0) {
        if (!_a0.sub_7101057258(_48, nullptr))
            return false;
        _c0 = false;
    }

    if (done)
        return true;
    if (!_182)
        return false;
    if (!_8.isAllocatedOrFailed())
        return true;

    if (!_8.isProcReady()) {
        const bool failed = _8.hasProcCreationFailed();
        if (!a1 && failed) {
            _182 = false;
            if (sub_7100DC9404())
                _182 = true;
            return false;
        }
        return failed;
    }

    auto* actor = static_cast<act::Actor*>(_8.releaseProc());
    actor->getActorFlags2().set(act::Actor::ActorFlag2::NoDistanceCheck);
    _18.acquire(actor, false);
    if (_a0._18 & 1) {
        if (auto* xlink = sub_7100DC9628())
            xlink->sub_710123051C(&_a0);
    }
    return true;
}

// NON_MATCHING: the temporary parameter names and the bool value use different stack slots (as in
// ActorContextStuff::sub_710065DACC). The getHeap() result is discarded in the original too.
// 0x7100dc9404: requests the DemoXLinkActor that plays the xlink:<_c8>,<_48> model user
bool EventXlinkInfo::sub_7100DC9404() {
    sead::FixedSafeString<128> model_user;
    model_user.appendWithFormat("xlink:%s,%s", _c8.cstr(), _48.cstr());
    act::InstParamPack params;
    params->addModelUser(model_user);
    if (_180) {
        params->add(true, "@SB");
        act::BaseProcHeapMgr::instance()->getHeap();
    }
    if (_8.hasProcCreationFailed())
        _8.deleteProcIfFailed();
    return act::ActorCreator::instance()->requestCreateActor("DemoXLinkActor", mHeap, &_8, &params, nullptr, 1);
}

// 0x7100dc9da0
bool EventXlinkInfo::sub_7100DC9DA0(const sead::SafeString& event_name, const sead::SafeString& entry_point) {
    if (event_name == "Demo709_0" || event_name == "Demo721_0")
        return false;
    if (event_name == "Electric_Relic") {
        if (entry_point == "Electric_Relic_BattleField01" || entry_point == "Electric_Relic_BattleField02" ||
            entry_point == "Electric_Relic_BattleField03") {
            return false;
        }
    }
    return true;
}

// 0x7100dc96a0
void EventXlinkInfo::x_1(EventFlowBase* flow) {
    if (auto* actor = sead::DynamicCast<act::Actor>(_18.getProc(nullptr))) {
        if (_8.isAllocatedOrFailed())
            _8.releaseAndWakeProc();
        else
            actor->wakeUp(act::BaseProc::SleepWakeReason::_0);
        actor->x_15(flow, nullptr);
    }
}

// 0x7100dc9780
void EventXlinkInfo::x_0() {
    if (auto* actor = sead::DynamicCast<act::Actor>(_18.getProc(nullptr))) {
        actor->sleep(act::BaseProc::SleepWakeReason::_0);
        actor->sub_71011C98F8();
    }
}

// 0x7100dc9628
xlink::XLink* EventXlinkInfo::sub_7100DC9628() {
    if (_18.hasProc()) {
        act::ActorLinkConstDataAccess accessor;
        if (act::acquireActor(&_18, &accessor))
            return accessor.sub_7100D0F214();
    }
    return nullptr;
}

// 0x7100dca228
const sead::SafeString& EventXlinkInfo::sub_7100DCA228(s32 idx) const {
    return _28[idx]._0;
}

// 0x7100dca244
const sead::SafeString& EventXlinkInfo::sub_7100DCA244(s32 idx) const {
    return _28[idx]._10;
}

// 0x7100dca264
const sead::SafeString& EventXlinkInfo::sub_7100DCA264(s32 idx) const {
    return _28[idx]._20;
}

}  // namespace ksys::evt
