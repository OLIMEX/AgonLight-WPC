Hi Olimex,

This submission is in FORTH again. It is based on an existing tetris implementation in FORTH by  Dirk Uwe Zoller (1994), which was also bundled with my FORTH system.

It looks much different from the original though. A few differences.

- Runs in 40 column mode (so it should be easy to port to Cerberus as well).

- Uses different tile designs. Any similarity between some tiles and Danish construction toys is pure coincidence.

- Uses colour

- Uses cursor keys

- Adds simple sound effects.

To run, please check out my FORTH from github. You need the latest version (v0.08 of forth.bin) or forth24.bin that has the SYSVARS@ and SYSVARS! words. It can run under either forth.bin (16-bit) or forth24.bin (24 bit).

https://github.com/lennart-benschop/agon-forth

To run:

load forth.bin (or load forth24.bin)

run . restit.4th


Kind regards.

-- 

Lennart Benschop

