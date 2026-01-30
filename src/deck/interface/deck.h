// Includes all the deck C API headers

#ifndef __DECK_H__
#define __DECK_H__

/* Core: handles initialisation, discovery and drivers */
#include "deck_core.h"

/* Deck constants (needed even for SITL for type definitions) */
#include "deck_constants.h"

// #ifndef CONFIG_PLATFORM_SITL
/* Deck APIs */
#include "deck_digital.h"
#include "deck_analog.h"
#include "deck_spi.h"
// #endif

#endif
