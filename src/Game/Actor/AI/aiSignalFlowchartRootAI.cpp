#include "Game/Actor/AI/aiSignalFlowchartRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiQuery.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/Event/evtEventResource.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/Resource/Event/resResourceEventFlow.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resTempResourceLoader.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace uking::ai {

// The resource handle of "EventFlow/SignalFlowchart.bfevfl" (placeholder name), created by loadResource.
ksys::res::Handle* sUnk_7102602228;
ksys::res::EventFlowchart* sUnk_7102602230;

SignalFlowchartRootAI::SignalFlowchartRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {
    _178 = 0;
    _380 = 0;
    _3b8 = false;
    _3b9 = false;
    _3bc = 0;
    _3ba = false;
    _58 = nullptr;
    _60 = nullptr;
}

SignalFlowchartRootAI::~SignalFlowchartRootAI() {
    if (!_3ba)
        return;
    if (sUnk_7102602228) {
        sUnk_7102602228->requestUnload2();
        delete sUnk_7102602228;
        sUnk_7102602228 = nullptr;
    }
}

// NON_MATCHING: binder helpers inline and context iteration retains cached end pointers.
bool SignalFlowchartRootAI::init_(sead::Heap* heap) {
    if (!sUnk_7102602230) {
        loadResource(ksys::util::getDebugHeap());
        _3ba = true;
    }
    _58 = sUnk_7102602230->getRes();
    _60 = _58->flowcharts.Get()->Get();
    const evfl::ResFlowchart* flowchart = _60;
    evfl::FlowchartContext::Builder builder({&flowchart, &flowchart + 1});
    const char* entry = mEventFlowEntryName_m.cstr();
    if (_3ba)
        entry = "PlayerOnGround";
    if (!builder.SetEntryPoint("SignalFlowchart", entry) ||
        !builder.Build(&mContext, ksys::evt::makeEvflAllocateArg(heap)))
        return false;
    for (auto& object : mContext.GetObjs()) {
        for (auto& binding : object.GetActBinder().GetBindings()) {
            if (binding.IsUsed() && !binding.IsInitialized()) {
                binding.SetUserData(nullptr);
                binding.SetInitialized(true);
            }
        }
    }
    for (auto& object : mContext.GetObjs())
        sub_7100E1B8D4(&object.GetActBinder(), this);
    for (auto& object : mContext.GetObjs())
        sub_7100E1B9C8(&object.GetActBinder(), this);
    return true;
}

// NON_MATCHING: resource path pointer globals and temporary request initialization differ.
void SignalFlowchartRootAI::loadResource(sead::Heap* heap) {
    ksys::res::TempResourceLoader::LoadArg arg;
    arg.load_req.mRequester = "SignalFlowchartRootAI";
    arg.load_req._28 = false;
    arg.load_req.mPath = "Event/SignalFlowchart.beventpack";
    arg.load_req.mLoadDataAlignment = 0x100;
    ksys::res::TempResourceLoader::InitArg init_arg{};
    ksys::res::TempResourceLoader loader;
    ksys::res::ResourceMgrTask::instance()->initTempResourceLoader(&loader, init_arg);
    loader.load(arg);
    ksys::res::LoadRequest request;
    request.mRequester = "SignalFlowchartRootAI";
    request.mPackHandle = loader.getHandle();
    request._22 = true;
    sUnk_7102602228 = new (heap, 8) ksys::res::Handle;
    sUnk_7102602230 = sead::DynamicCast<ksys::res::EventFlowchart>(sUnk_7102602228->load(
        "EventFlow/SignalFlowchart.bfevfl", &request, nullptr));
}

// NON_MATCHING: resource pointer load scheduling around the owner store.
u64 SignalFlowchartRootAI::sub_7100E1B8D4(evfl::ActBinder* binder, SignalFlowchartRootAI* owner) {
    u8 any_ok = 0;
    u8 any_failed = 0;
    for (auto binding = binder->GetBindings().begin(); binding != binder->GetBindings().end(); ++binding) {
        if (!binding->IsUsed() || !binding->IsInitialized())
            continue;
        for (auto action = binding->GetActions().begin(); action != binding->GetActions().end(); ++action) {
            owner->_f8[owner->_178].owner = owner;
            auto& entry = owner->_f8[owner->_178];
            entry.res = action->res_action;
            action->handler = sub_7100E1B1B0;
            action->user_data = &entry;
            ++owner->_178;
            (action->handler ? any_ok : any_failed) = 1;
        }
    }
    return u64(any_ok) | (u64(any_failed) << 8);
}

// NON_MATCHING: resource pointer load scheduling around the owner store.
u64 SignalFlowchartRootAI::sub_7100E1B9C8(evfl::ActBinder* binder, SignalFlowchartRootAI* owner) {
    u8 any_ok = 0;
    u8 any_failed = 0;
    for (auto binding = binder->GetBindings().begin(); binding != binder->GetBindings().end(); ++binding) {
        if (!binding->IsUsed() || !binding->IsInitialized())
            continue;
        for (auto query = binding->GetQueries().begin(); query != binding->GetQueries().end(); ++query) {
            owner->_180[owner->_380].owner = owner;
            auto& entry = owner->_180[owner->_380];
            entry.res = query->res_query;
            query->handler = sub_7100E1B274;
            query->user_data = &entry;
            ++owner->_380;
            (query->handler ? any_ok : any_failed) = 1;
        }
    }
    return u64(any_ok) | (u64(any_failed) << 8);
}

// NON_MATCHING: ActionDoneHandler move clears its source fields in a different order.
void SignalFlowchartRootAI::sub_7100E1B1B0(const evfl::ActionArg& arg,
                                        evfl::ActionDoneHandler handler) {
    auto* entry = static_cast<BoundEntry*>(arg.action_user_data);
    entry->owner->sub_7100E1B31C(arg, std::move(handler));
}

// NON_MATCHING: query lookup pointer load and register scheduling.
int SignalFlowchartRootAI::sub_7100E1B274(const evfl::QueryArg& arg) {
    auto* entry = static_cast<BoundEntry*>(arg.query_user_data);
    auto* actor = ksys::evt::Manager::instance()->_1d378->sub_7100DC7E84();
    if (!actor)
        return 0;
    const auto* res = static_cast<const evfl::ResQuery*>(entry->res);
    auto* query = actor->getRootAi()->getQueries().getQuery(res->name.Get()->data());
    if (!query)
        return 0;
    query->loadParams(arg);
    return query->doQuery();
}

// NON_MATCHING: handler invocation tail merging and move assignment store order.
void SignalFlowchartRootAI::sub_7100E1B31C(const evfl::ActionArg& arg,
                                        evfl::ActionDoneHandler handler) {
    const auto* entry = static_cast<BoundEntry*>(arg.action_user_data);
    const auto* res = static_cast<const evfl::ResAction*>(entry->res);
    const sead::SafeString name = res->name.Get()->data();
    if (name == "Demo_SendSignal") {
        s32 type;
        s32 value;
        if (arg.param_accessor.FindInt(&type, "SignalType") &&
            arg.param_accessor.FindInt(&value, "Value")) {
            _3bc = type;
            if (type == 0) {
                if (value)
                    mActor->emitBasicSigOn();
                else
                    mActor->emitBasicSigOff();
            }
        }
    } else if (name == "Demo_LoopEnd") {
        mActionDoneHandler = std::move(handler);
        return;
    }
    handler.Invoke();
}

void SignalFlowchartRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    _3b8 = false;
    _3b9 = false;
    _3bc = 0;
}

void SignalFlowchartRootAI::calc_() {
    if (mActor->checkBasicSig()) {
        if (!_3b8) {
            mContext.Start(nullptr);
            _3b8 = true;
        } else {
            mActionDoneHandler.Invoke();
        }
    } else if (_3bc == 0) {
        mActor->emitBasicSigOff();
    }

    if (mContext.GetNumAllocatedNodes() == 0)
        setFinished();
}

void SignalFlowchartRootAI::leave_() {
    mActionDoneHandler.Reset();
    mContext.Clear();
}

void SignalFlowchartRootAI::loadParams_() {
    getMapUnitParam(&mEventFlowName_m, "EventFlowName");
    getMapUnitParam(&mEventFlowEntryName_m, "EventFlowEntryName");
}

}  // namespace uking::ai
