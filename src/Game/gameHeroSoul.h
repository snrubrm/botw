#pragma once

// Global functions of the hero soul / champion ability state (TU 0x7100a9d3f8-0x7100a9d4d0; names from
// the CSV, which are not namespaced; the CSV name of 0xa9d488 says Mipha although Player::canUseUrbosaFury is
// its only caller).
bool hasRitoSoul();             // 0x7100a9d3f8
bool hasDarukProtection();      // 0x7100a9d440
bool hasMiphaSoul();            // 0x7100a9d488
bool hasMiphaGraceCharges();    // 0x7100a9d4d0
