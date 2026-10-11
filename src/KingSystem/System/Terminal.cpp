#include "KingSystem/System/Terminal.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(Terminal)

// Keep the native vptr store, following GameDataFlagSelector (upstream commit 96101229).
Terminal::~Terminal() { ; }

}  // namespace ksys
