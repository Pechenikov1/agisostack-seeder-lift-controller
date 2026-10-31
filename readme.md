@'
# agisostack-seeder-lift-controller

isobus implement controller prototype for a pneumatic seeder.

this project is based on the official agisostack++ seeder example:
https://github.com/Open-Agriculture/AgIsoStack-plus-plus/tree/main/examples/seeder_example

goal:
- make a seeder visible to tractor vt / tc as an isobus implement
- support raise and lower control with valve pulses
- support basic diagnostics
- support optional section group logic in future phases
'@ | Set-Content -Path .\readme.md

/////////////////////////////////////////////

cd D:\documents\agisostack-seeder-lift-controller

mkdir docs
mkdir firmware
mkdir hardware
mkdir reference
mkdir firmware\esp32

@'
# agisostack-seeder-lift-controller

isobus implement controller prototype for a pneumatic seeder using agisostack++.

## goal

build a practical implement controller for a non-electronic pneumatic seeder so it can:

- be visible to a tractor as an isobus implement
- support basic lift and lower control via hydraulic valve pulse logic
- report basic diagnostics
- support optional section group logic in the future
- integrate with agopengps and a vt/tc workflow

## why this project

the machine is a pneumatic seeder with:

- seed hopper
- two metering units
- fan
- distribution heads
- 42 outlets
- hydraulic raise and lower cylinders
- mechanical raise cutoff
- optional future section control via valve logic

the main goal is not to build a full 42-section planter sc from day one.

the first version targets a realistic implement interface:

- one section group representing the whole implement
- raise pulse and lower pulse via hydraulic valve control
- diagnostics for empty hopper, blocked hoses, fan state, and other basic states
- basic isobus compatibility for vt / tc / gfx750 / agopengps ecosystem

## reference

this project is based on the official agisostack++ example:

https://github.com/Open-Agriculture/AgIsoStack-plus-plus/tree/main/examples/seeder_example

## current phase

phase 1:

- isobus implement identity and basic diagnostics
- lift control by timed valve pulses
- section state mapping from tc / work state
- optional alarms for:
  - hopper empty
  - hose blocked
  - fan fail
  - lift fault
- basic state machine

future phases:

- 2 section groups
- 1-2 independent shut-off groups for selected outlet groups
- deeper section control logic
- integration with agopengps automation
- vt display / task control enhancements

## high-level architecture

- esp32 controller
- can transceiver
- agisostack++ isobus stack
- hydraulic raise/lower valve outputs
- limit switches
- sensor inputs
- optional mosfets and relay outputs

## file structure

```text
agisostack-seeder-lift-controller/
├── readme.md
├── docs/
│   ├── architecture.md
│   ├── requirements.md
│   └── reference-notes.md
├── firmware/
│   └── esp32/
├── hardware/
├── reference/
│   └── agisostack-plus-plus/
│       └── examples/
│           └── seeder_example/
├── .gitignore