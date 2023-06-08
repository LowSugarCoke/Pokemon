#pragma once

// Constants representing effectiveness rates
#define  NO  0    // No effect
#define  NV  0.5  // Not very effective
#define  NM  1    // Normal effectiveness
#define S    2    // Super effective

// 2D array representing the effectiveness rates between types
static const float kEffectivenessRate[18][18] = {
    { NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, NV, NO, NM, NM, NV, NM },
    { NM, NV, NV, NM, S,  S,  NM, NM, NM, NM, NM, S,  NV, NM, NV, NM, S,  NM },
    { NM, S,  NV, NM, NV, NM, NM, NM, S,  NM, NM, NM, S,  NM, NV, NM, NM, NM },
    { NM, NM, S,  NV, NV, NM, NM, NM, NO, S,  NM, NM, NM, NM, NV, NM, NM, NM },
    { NM, NV, S,  NM, NV, NM, NM, NV, S,  NV, NM, NV, S,  NM, NV, NM, NV, NM },
    { NM, NV, NV, NM, S,  NV, NM, NM, S,  S,  NM, NM, NM, NM, S,  NM, NV, NM },
    { S,  NM, NM, NM, NM, S,  NM, NV, NM, NV, NV, NV, S,  NO, NM, S,  NM, NV },
    { NM, NM, NM, NM, S,  NM, NM, NV, NV, NM, NM, NM, NV, NV, NM, NM, NO, S },
    { NM, S,  NM, S,  NV, NM, NM, S,  NM, NO, NM, NV, S,  NM, NM, NM, S,  NM },
    { NM, NM, NM, NV, S,  NM, S,  NM, NM, NM, NM, S,  NV, NM, NM, NM, NV, NM },
    { NM, NM, NM, NM, NM, NM, S,  S,  NM, NM, NV, NM, NM, NM, NM, NO, NV, NM },
    { NM, NV, NM, NM, S,  NM, NV, NV, NM, NV, S,  NM, NM, NV, NM, S,  NV, NV },
    { NM, S,  NM, NM, NM, S,  NV, NM, NV, S,  NM, S,  NM, NM, NM, NM, NV, NM },
    { NO, NM, NM, NM, NM, NM, NM, NM, NM, NM, S,  NM, NM, S,  NM, NV, NM, NM },
    { NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, NM, S,  NM, NV, NO },
    { NM, NM, NM, NM, NM, NM, NV, NM, NM, NM, S,  NM, NM, S,  NM, NV, NM, NV },
    { NM, NV, NV, NV, NM, S,  NM, NM, NM, NM, NM, NM, S,  NM, NM, NM, NV, S },
    { NM, NV, NM, NM, NM, NM, S,  NV, NM, NM, NM, NM, NM, NM, S,  S,  NV, NM }
};
