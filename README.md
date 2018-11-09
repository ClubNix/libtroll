# libtroll
A library for really horrible people.

## Disclaimer

By using this library, you agree to the fact that you are a really horrible
person and if anything happens to your computer or a computer of a co-worker,
you (or (s)he) deserved it.

## Description

**TODO**

## Compiling

- Install [meson](https://mesonbuild.com/)
- `meson --buildtype=release build`
- `cd build`
- `ninja`

## Using

- Make sure that the environment variable `LD_PRELOAD` points to the compiled
  library.
- Run the program

For example, if you do `LD_PRELOAD=build/src/libtroll.so whoami` in the source
directory after building the project, `whoami` will print your user name in pink

For maximum evilness, you can set the `LD_PRELOAD` in a user's profile. This
leads to permanent fun!

## Levels

When compiling this library, you have the choice between 5 levels:

| Destruction level | Description                                                                                      |
|-------------------|--------------------------------------------------------------------------------------------------|
| 1: Cosmetic       | This is only a visual improvement of the entire system, nothing dangerous theoretically.         |
| 2: Weird          | You may notice a change a behavior in your program. If a program crashes, this is not our fault. |
| 3: Crash-o-matic  | This is like Russian Roulette, but for programs, and not russian.                                |
| 4: Data Destroyer | Self explanatory name.                                                                           |
| 5: Nuke.sh        | If your entire system is crashing, this is the kernel's fault.                                   |
