#include "Game/AI/Action/actionDgnObjDlcGondolaCreateTag.h"
#include "Game/AI/AI/aiMoveAndFreeFallGondola.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/System/VFR.h"

namespace uking::action {

DgnObjDlcGondolaCreateTag::DgnObjDlcGondolaCreateTag(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

// NON_MATCHING: the base-handle address is formed two instructions earlier.
DgnObjDlcGondolaCreateTag::~DgnObjDlcGondolaCreateTag() = default;

bool DgnObjDlcGondolaCreateTag::init_(sead::Heap* heap) {
    sub_7100056294();
    sub_710005637C(&_980[0], *mIntervalTime_m);
    sub_710005637C(&_980[1], *mIntervalTime_m + *mIntervalTime_m);
    sub_710005637C(&_980[2], *mIntervalTime_m * 3.0f);
    sub_710005637C(&_980[3], *mIntervalTime_m * 4.0f);
    sub_710005637C(&_980[4], *mIntervalTime_m * 5.0f);
    return true;
}

void DgnObjDlcGondolaCreateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_7100056294();
    sub_710005637C(&_980[5], 0.0f);
    _a30 = *mIntervalTime_m;
}

void DgnObjDlcGondolaCreateTag::leave_() {
    for (auto& handle : _980)
        handle.deleteProc();
}

void DgnObjDlcGondolaCreateTag::loadParams_() {
    getStaticParam(&mActorName_s, "ActorName");
    getMapUnitParam(&mIntervalTime_m, "IntervalTime");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

// NON_MATCHING: loop register allocation and the count reload on skipped links differ.
void DgnObjDlcGondolaCreateTag::sub_7100056294() {
    auto* object = mActor->getMapObject();
    if (!object || !object->getLinkData())
        return;
    auto* links = &object->getLinkData()->mLinksToSelf.links;
    for (u32 i = 0; i < u32(links->size()); ++i) {
        const auto& link = (*links)[i];
        if (link.type == ksys::map::MapLinkDefType::Reference) {
            auto* linked_object = link.other_obj;
            if (linked_object) {
                if (_360.isFull())
                    return;
                auto* proc_link = _360.emplaceBack();
                proc_link->acquire(linked_object->tryGetActor(false), false);
            }
        }
    }
}

void DgnObjDlcGondolaCreateTag::sub_710005637C(ksys::act::BaseProcHandle* handle, f32 offset_time) {
    if (_40.isFull() || handle->isAllocatedOrFailed())
        return;
    ksys::act::InstParamPack params;
    params->addPosition(mActor->getMtx().getTranslation());
    params->add(*mRailMoveSpeed_m, "RailMoveSpeed");
    params->add(offset_time, "GondolaRailOffsetTime");
    auto* creator = ksys::act::ActorCreator::instance();
    mActorName_s.cstr();
    creator->requestCreateActor(mActorName_s.getStringTop(),
        ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), handle, &params, nullptr, 1);
}

void DgnObjDlcGondolaCreateTag::calc_() {
    for (s32 i = 0; i < 5; ++i) {
        if (_980[i].isAllocatedOrFailed())
            sub_710005671C(&_980[i]);
    }
    _a30 += ksys::VFR::instance()->getRawDeltaTime();
    if (_a30 > *mIntervalTime_m) {
        sub_710005671C(&_980[5]);
        if (!_980[5].isAllocatedOrFailed()) {
            sub_710005637C(&_980[5], 0.0f);
            _a30 = 0.0f;
        }
    }
    for (u32 i = 0; i < u32(_40.size());) {
        if (_40[i]->hasProc()) {
            ++i;
        } else {
            _40.erase(i);
            i = 0;
        }
    }
}

void DgnObjDlcGondolaCreateTag::sub_710005671C(ksys::act::BaseProcHandle* handle) {
    if (handle->isProcReady()) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(handle->releaseAndWakeProc());
        if (actor) {
            auto* link = _40.emplaceBack();
            link->acquire(actor, false);
            auto* rail = sub_7100EEF264(mActor, 0);
            if (auto* ai = sub_7100056E70(actor->getRootAi())) {
                ai->sub_71004AFD30(mActor);
                ai->sub_71004AFD3C(rail);
            }
        }
    } else if (_980[5].hasProcCreationFailed()) {
        _980[5].deleteProcIfFailed();
    }
}

ai::MoveAndFreeFallGondola*
DgnObjDlcGondolaCreateTag::sub_7100056E70(ksys::act::ai::ActionBase* action) {
    for (u32 i = 0; i < u32(action->getNumChildren()); ++i) {
        if (auto* ai = sub_7100056E70(action->getChild(i)))
            return ai;
    }
    return sead::DynamicCast<ai::MoveAndFreeFallGondola>(action);
}

bool DgnObjDlcGondolaCreateTag::handleMessage_(const ksys::Message* message) {
    if (_9e0.m2(*message)) {
        for (u32 i = 0; i < u32(_40.size()); ++i) {
            auto* link = _40[i];
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(link, &accessor);
            if (accessor.hasProc()) {
                const auto* id = accessor.getMessageTransceiverId();
                const auto& source = message->getSource();
                if (id->queue_id == source.queue_id && id->id == source.id) {
                    _40.erase(i);
                    return false;
                }
            }
        }
    } else if (u32(message->getType()) - 0x3000003 < 2) {
        for (u32 i = 0; i < u32(_360.size()); ++i)
            sub_7100056CD4(_360[i], message);
        for (u32 i = 0; i < u32(_40.size()); ++i)
            sub_7100056CD4(_40[i], message);
    }
    return false;
}

// NON_MATCHING: accessor cleanup branches and their saved-register allocation differ.
void DgnObjDlcGondolaCreateTag::sub_7100056CD4(ksys::act::BaseProcLink* link,
                                           const ksys::Message* message) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    if (accessor.hasProc()) {
        const auto& source = message->getSource();
        const auto* id = accessor.getMessageTransceiverId();
        if (source.isRegistered() && id->isRegistered() &&
            (source.queue_id != id->queue_id || source.id != id->id)) {
            auto* sender = ksys::act::ActorSystem::instance()->getStasisMessageSender();
            sender->sendMessage(sead::DynamicCast<ksys::act::Actor>(link->getProc(nullptr, nullptr)),
                                message->getType(), true);
        }
    }
}

}  // namespace uking::action
