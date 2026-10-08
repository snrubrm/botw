#include "Game/AI/AI/aiDemoRootAI.h"
#include "KingSystem/Event/evtActionContext.h"

namespace uking::ai {

// Helpers for the RootAi + 0x140 event context used by DemoRootAI (defined here, not in
// aiDemoRootAI.cpp, or they inline into its callers). The context type itself is unknown
// (RootAi is not modeled here), so the functions take void* and only the used layout is given.

// The +8 member of the RootAi + 0x140 context: head of an ActionContext chain.
struct DemoContext {
    u8 _0[8];
    ksys::evt::ActionContext* _8;
};

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
