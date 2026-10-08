#include "Game/AI/AI/aiDemoRootAI.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtActionContext.h"

namespace ai {
// DemoRootAI-TU helper caller (no header in the repo; declared-only): finds the demo AI for the
// root (returns it or null; the return feeds the DemoRootAI helpers below, so DemoRootAI*).
class ActorAI {
public:
    static uking::ai::DemoRootAI* x_0(ksys::act::ai::RootAi* root);
};
}  // namespace ai

namespace uking::ai {

// Helpers for the RootAi + 0x140 event context used by DemoRootAI (defined here, not in
// aiDemoRootAI.cpp, or they inline into its callers). The context type itself is unknown
// (RootAi is not modeled here), so the functions take void* and only the used layout is given.

// The +8 member of the RootAi + 0x140 context: head of an ActionContext chain.
struct DemoContext {
    u8 _0[8];
    ksys::evt::ActionContext* _8;
};

// 0x7100d61fac / 0x7100d62154 (CSV placeholders; defined in aiDemoRootAIHelpers.cpp, not here,
// or the walker below starts skipping the d61fac call).
void sub_7100D61FAC(DemoRootAI* demo, ksys::evt::ActionContext* ctx, u32* bits, u32 flags);
void sub_7100D62154(DemoRootAI* demo, ksys::evt::ActionContext* ctx);

// 0x7100d6300c (CSV placeholder): walk the ActionContext list at the RootAi + 0x140 context and
// advance each node (d61fac for status-0 nodes, d62154 for status-1 nodes), then unlink all.
// NON_MATCHING: everything matches except the stack slot of the `bits` word (original sp+0x8,
// ours sp+0xc; the zero store and the address computation); no source reordering tried (four
// declaration positions) moves it.
void sub_7100D6300C(void* context, ksys::act::Actor* actor) {
    u32 bits;
    ksys::evt::ActionContext* next;
    DemoRootAI* demo = ::ai::ActorAI::x_0(actor->getRootAi());
    auto* chain = static_cast<DemoContext*>(context);
    ksys::evt::ActionContext* ctx = chain->_8;
    while (ctx != nullptr) {
        if (ctx->mStatus2 == 0) {
            bits = 0;
            sub_7100D61FAC(demo, ctx, &bits, (ctx->_af4 >> 2) & 1);
        }
        if (ctx->mStatus2 == 1)
            sub_7100D62154(demo, ctx);
        next = ctx->_a58;
        ctx->statusStuff_1(actor);
        ctx->_a58 = nullptr;
        ctx = next;
    }
    chain->_8 = nullptr;
}

// 0x7100d630ac (CSV placeholder name): release the ActionContext chain (statusStuff_2 on each
// node, unlink all).
void sub_7100D630AC(void* context) {
    auto* chain = static_cast<DemoContext*>(context);
    ksys::evt::ActionContext* ctx = chain->_8;
    while (ctx != nullptr) {
        ksys::evt::ActionContext* next = ctx->_a58;
        ctx->statusStuff_2();
        ctx->_a58 = nullptr;
        ctx = next;
    }
    chain->_8 = nullptr;
}

}  // namespace uking::ai
