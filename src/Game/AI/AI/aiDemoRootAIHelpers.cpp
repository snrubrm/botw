#include "Game/AI/AI/aiDemoRootAI.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcHeapMgr.h"
#include "KingSystem/Event/evtActionContext.h"

namespace uking::ai {

// DemoRootAI node-advance helpers (the 0x7100d61fac-0x7100d62750 cluster; defined here, not in
// aiDemoRootAIContext.cpp, or the context walker below starts skipping the d61fac call: with
// d61fac's body visible it proves the 0x10-flag gate and jumps over the call).

void sub_7100D61FC0(DemoRootAI* demo, ksys::evt::ActionContext* ctx, u32* bits, bool flag);

// 0x7100d61fac (CSV placeholder): gate for sub_7100D61FC0 (skipped when the request's 0x10 flag
// is set; the low bit of the flags is forwarded).
void sub_7100D61FAC(DemoRootAI* demo, ksys::evt::ActionContext* ctx, u32* bits, u32 flags) {
    if ((ctx->_af4 & 0x10) != 0)
        return;
    sub_7100D61FC0(demo, ctx, bits, flags & 1);
}

void sub_7100D6225C(DemoRootAI* demo, const sead::SafeString& name, s32 idx, bool flag);
void sub_7100D62750(DemoRootAI* demo, u32 child_idx, s32 request_idx,
                    ksys::act::ai::InlineParamPack* params);

// 0x7100d61fc0 (CSV placeholder): start the child named by the context, either as a one-shot
// trigger action, as the current child (slot -1) or in slot `ctx->_48`. The formatted "%s.evfl"
// strings are unused (their use was compiled out of the release build).
// NON_MATCHING: regalloc only (child index and parameter pointer swap x21/x22).
void sub_7100D61FC0(DemoRootAI* demo, ksys::evt::ActionContext* ctx, u32* bits, bool flag) {
    const s32 idx = ctx->_48;
    const u32 child_idx = demo->getChildIdx(ctx->_8);
    if (child_idx == 0xffff) {
        sead::FormatFixedSafeString<128> message("%s.evfl", ctx->_a60.cstr());
        return;
    }
    auto* child = demo->getChild(child_idx);
    auto* params = &ctx->_50;
    if (child->isTriggerAction()) {
        child->oneShot(params);
        return;
    }
    if (idx < 31) {
        const u32 bit = 1u << (idx + 1);
        if ((*bits & bit) != 0) {
            ksys::act::ai::ActionBase* current =
                idx == -1 ? demo->getCurrentChild() : demo->_38[idx];
            if (current && !flag)
                sead::FormatFixedSafeString<128> message("%s.evfl", ctx->_a60.cstr());
        } else {
            *bits |= bit;
        }
        if (idx == -1) {
            demo->changeChild(child_idx, params);
            return;
        }
    }
    sub_7100D62750(demo, child_idx, idx, params);
}

// 0x7100d62154 (CSV placeholder): stop the node of the context: destroy its slot action, or go
// back to "Demo_Idling" (flag 8), else switch to "Demo_VisibleOff".
// NON_MATCHING: sub_7100D6225C ignores its flag and is defined in this TU, so clang passes 0
// instead of the (flags >> 2) & 1 the original computes (one ldrh of the flags shared with the
// bit-3 test); the rest matches.
void sub_7100D62154(DemoRootAI* demo, ksys::evt::ActionContext* ctx) {
    if ((ctx->_af4 & 0x10) == 0) {
        const s32 child_idx = demo->getChildIdx(ctx->_8);
        if (child_idx == 0xffff)
            return;
        if (demo->getChild(child_idx)->isTriggerAction())
            return;
        const s32 idx = ctx->_48;
        if (idx >= 0) {
            sub_7100D6225C(demo, ctx->_8, idx, (ctx->_af4 >> 2) & 1);
            return;
        }
        if ((ctx->_af4 & 8) != 0) {
            demo->sub_7100D62394(ctx);
            return;
        }
    }
    const s32 idx = demo->getChildIdx("Demo_VisibleOff");
    if (idx != 0xffff)
        demo->changeChild(idx, nullptr);
}

// 0x7100d6225c (CSV placeholder): destroy the action in slot `idx` when its name matches `name`.
// The flag argument is passed by sub_7100D62154 but ignored (same as ActionBase::m4's ignored bool).
void sub_7100D6225C(DemoRootAI* demo, const sead::SafeString& name, s32 idx, bool flag) {
    (void)flag;
    if (demo->_38.size() <= idx)
        return;
    auto* action = demo->_38[idx];
    if (!action)
        return;
    // isEqual (not compare: the 0x80000 bound check exits with b.gt, i.e. `i <= max`): the
    // SafeString temporary's cstr devirtualises away, leaving exactly the two virtual calls on
    // `name` that the original shows.
    if (!name.isEqual(sead::SafeString(action->getName())))
        return;
    auto& slot = demo->_38[idx];
    auto* target = slot;
    if (!target)
        return;
    target->leave();
    target->hasUpdateForPreDeleteCb();
    target->onPreDelete();
    delete target;
    slot = nullptr;
}

// 0x7100d62750 (CSV placeholder): replace the action in slot `request_idx` with a clone of child
// `child_idx`, entered with `params`. The IsDerivedFrom check keeps the guard-initialised
// Derive<ActionBase> static (inlined from Action::getRuntimeTypeInfoStatic) that the original
// shows; the clone keeps working on the Action the child was verified against.
void sub_7100D62750(DemoRootAI* demo, u32 child_idx, s32 request_idx,
                    ksys::act::ai::InlineParamPack* params) {
    if (demo->_38.size() <= request_idx)
        return;
    auto* child = demo->getChild(child_idx);
    if (!sead::IsDerivedFrom<ksys::act::ai::Action>(child))
        return;
    auto* clone = ksys::act::ai::Actions::clone(
        *static_cast<ksys::act::ai::Action*>(child),
        ksys::act::BaseProcHeapMgr::instance()->getHeap());
    if (!clone)
        return;
    auto& slot = demo->_38[request_idx];
    if (auto* old = slot) {
        old->leave();
        old->hasUpdateForPreDeleteCb();
        old->onPreDelete();
        delete old;
        slot = nullptr;
    }
    demo->_38[request_idx] = clone;
    demo->_38[request_idx]->enter(params, demo->getName());
}

}  // namespace uking::ai
