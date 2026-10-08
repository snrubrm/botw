#include "Game/AI/AI/aiDemoRootAI.h"
#include "KingSystem/Event/evtActionContext.h"

namespace uking::ai {

// DemoRootAI node-advance helpers (the 0x7100d61fac-0x7100d62750 cluster; defined here, not in
// aiDemoRootAIContext.cpp, or the context walker below starts skipping the d61fac call: with
// d61fac's body visible it proves the 0x10-flag gate and jumps over the call).

// 0x7100d61fc0 / 0x7100d62750 (CSV placeholders, not decompiled yet): advance one node
// (declared only so the definer below can call them).
void sub_7100D61FC0(DemoRootAI* demo, ksys::evt::ActionContext* ctx, u32* bits, bool flag);
void sub_7100D62750(ksys::act::ai::Ai* ai, u32 child_idx, s32 request_idx,
                    ksys::act::ai::InlineParamPack* params);

// 0x7100d61fac (CSV placeholder): gate for sub_7100D61FC0 (skipped when the request's 0x10 flag
// is set; the low bit of the flags is forwarded).
void sub_7100D61FAC(DemoRootAI* demo, ksys::evt::ActionContext* ctx, u32* bits, u32 flags) {
    if ((ctx->_af4 & 0x10) != 0)
        return;
    sub_7100D61FC0(demo, ctx, bits, flags & 1);
}

// 0x7100d62154 (CSV placeholder; not decompiled yet): advance one node by child index
// (declared only so the context walker can call it).
void sub_7100D62154(DemoRootAI* demo, ksys::evt::ActionContext* ctx);

// 0x7100d6225c (CSV placeholder, not decompiled yet): tail callee of sub_7100D62154
// (declared only).
void sub_7100D6225C(ksys::act::ai::Ai* ai, const sead::SafeString& name, u32 bits, bool flag);

}  // namespace uking::ai
