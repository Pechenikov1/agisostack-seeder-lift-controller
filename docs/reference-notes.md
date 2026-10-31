@'
# reference-notes

official example:
https://github.com/Open-Agriculture/AgIsoStack-plus-plus/tree/main/examples/seeder_example

relevant:
- isobus setup
- diagnostics
- section control reference
- task controller / vt patterns

not relevant yet:
- full 42 section control
- per outlet calibration
'@ | Set-Content -Path .\docs\reference-notes.md

//////////////////////////////////////////////////////////


@'
# reference-notes

## official source

https://github.com/Open-Agriculture/AgIsoStack-plus-plus/tree/main/examples/seeder_example

## what is relevant

- implement identity and isobus setup
- diagnostic protocol usage
- task controller and virtual terminal references
- section control state logic
- work-state and control patterns

## what is not relevant yet

- full 42-section real planter logic
- per-outlet seed re-routing
- detailed section calibration
- full multi-machine integration

## project interpretation

this project is not a direct copy of the example.

it is a practical adaptation for:

- one section group for the whole implement
- timed lift/raise pulse logic
- basic isobus visibility to tractor vt
- future extension to grouped section control
'@ | Set-Content -Path .\docs\reference-notes.md