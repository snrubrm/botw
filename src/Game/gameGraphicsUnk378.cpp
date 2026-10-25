#include "Game/gameGraphics.h"

// Home of the Graphics render-block TUs at 0x710128a000..0x710128cfff (Graphics::Unk_378 and the
// code around it). The shadow settings setter below belongs here: its code sits at 0x710128b084,
// between the Unk_378 helpers 0x710128af04 and 0x710128b08c.

// 0x710128b084 (unnamed in the CSV): sets the quality index of the shadow settings block reached
// through Graphics + 0xa98. Graphics' shadow mode switch (0x7100f2f2c8) calls it with 1..4.
void Graphics::Unk_a98::setQuality(u32 quality) {
    mQuality = quality;
}

// 0x710128babc (unnamed in the CSV): bumps the change counter at +0x7c. Graphics' shadow mode
// path (0x7100f1fdc8) calls it on the shadow settings block after testing a related flag.
void Graphics::Unk_a98::incrementChangeCountMaybe() {
    mChangeCount.increment();
}
