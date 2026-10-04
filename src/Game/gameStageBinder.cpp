#include "Game/gameStageBinder.h"

namespace uking {

// The binders of the original are one TU (0x71007bec64-0x71007bfe10); their virtuals are inline in the header and
// are emitted with the out-of-line destructors.
Unk_710245abf0::~Unk_710245abf0() = default;
Unk_710245ac20::~Unk_710245ac20() = default;

TitleStageBinder::~TitleStageBinder() = default;
ViewerStageBinder::~ViewerStageBinder() = default;
OpenWorldStageArg::~OpenWorldStageArg() = default;
OpenWorldStageBinder::~OpenWorldStageBinder() = default;
IndoorStageBinder::~IndoorStageBinder() = default;
MainFieldDungeonStageBinder::~MainFieldDungeonStageBinder() = default;
StartupSaveCheckStageBinder::~StartupSaveCheckStageBinder() = default;

}  // namespace uking
