#include "KingSystem/Utils/StateMachine.h"
#include "Game/UI/uiScreenChildStates.h"
#include "Game/UI/uiScreens.h"

// The leaf screens keep their StateMachine states (static objects holding member function pointers to
// the screen's own virtual slots, 154+) as ksys::StateTemplate<Screen<Name>>: one vtable per screen.
template class ksys::StateTemplate<uking::ui::ScreenAkashNum>;
template class ksys::StateTemplate<uking::ui::ScreenAppHome>;
template class ksys::StateTemplate<uking::ui::ScreenAppMapDungeon>;
template class ksys::StateTemplate<uking::ui::ScreenAppMenuBtn>;
template class ksys::StateTemplate<uking::ui::ScreenAppTool>;
template class ksys::StateTemplate<uking::ui::ScreenDLCSinJuAkashiNum>;
template class ksys::StateTemplate<uking::ui::ScreenGameOver>;
template class ksys::StateTemplate<uking::ui::ScreenHardMode>;
template class ksys::StateTemplate<uking::ui::ScreenKologNum>;
template class ksys::StateTemplate<uking::ui::ScreenMainScreen>;
template class ksys::StateTemplate<uking::ui::ScreenMamoNum>;
template class ksys::StateTemplate<uking::ui::ScreenPauseMenuRecipe>;
template class ksys::StateTemplate<uking::ui::ScreenRupee>;
template class ksys::StateTemplate<uking::ui::Unk_710247af10>;
template class ksys::StateTemplate<uking::ui::Unk_710247b428>;
template class ksys::StateTemplate<uking::ui::Unk_710247e468>;
template class ksys::StateTemplate<uking::ui::ScreenAppAlbum>;
template class ksys::StateTemplate<uking::ui::ScreenAppCamera>;
template class ksys::StateTemplate<uking::ui::ScreenSaveTransferWindow>;
template class ksys::StateTemplate<uking::ui::Screen>;
template class ksys::StateTemplate<uking::ui::ScreenBase>;
template class ksys::StateTemplate<uking::ui::ScreenTitle>;
