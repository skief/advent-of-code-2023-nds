#include <maxmod9.h>

#include "sounds.h"
#include "generated/soundbank_bin.h"
#include "generated/soundbank.h"

void Sounds::init() {
    mmInitDefaultMem((mm_addr)soundbank_bin);
    mmLoadEffect(SFX_AMAZINGGRACEOFCHRISTMAS);
}

void Sounds::start() {
    mmEffect(SFX_AMAZINGGRACEOFCHRISTMAS);
}
