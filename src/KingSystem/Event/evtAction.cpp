#include "KingSystem/Event/evtAction.h"

namespace ksys::evt {

// 0x71008a71fc (CSV evt::Action::ctor)
Action::Action(const void* action_data, ActorBase* actor) : ActionBase(action_data, actor) {}

// 0x71008a7230 (CSV evt::Action::dtor), 0x71008a7244 (dtorDelete)
// (user-provided empty body: the original keeps the vtable pointer store, see uiScreenDtors2.cpp)
Action::~Action() { ; }

}  // namespace ksys::evt
