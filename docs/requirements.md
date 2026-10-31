@'
# requirements

must have:
- isobus visibility to tractor
- raise/lower control
- basic work state handling
- basic diagnostics

nice to have:
- 2 section groups
- agopengps integration
- vt alarms / status
'@ | Set-Content -Path .\docs\requirements.md

////////////////////////////////////////////////////////

@'
# requirements

## functional requirements

### must have
- implement visible to tractor as isobus-capable
- basic work state handling
- basic section state support
- raise/lower valve pulse logic
- mechanical lift state support
- diagnostics for:
  - hopper empty
  - blocked hose / outlet
  - fan fail
  - valve fault
- safe default state

### nice to have
- 2 section groups
- left/right wing grouping
- automatic lower/raise with field boundaries
- integration with agopengps
- vt display of status and alarms

## hardware requirements
- esp32
- can transceiver
- mosfets / relays for hydraulic valves
- sensor interfaces
- valve feedback / limit switches

## software requirements
- c++ firmware
- agisostack++ reference integration
- logic for timer-based raise/lower valve pulses
- safe state machine

## constraints
- no full 42-outlet section calibration at phase 1
- no attempt to re-route seeds back into the hopper
- no unnecessary complexity before proving the isobus implement interface
'@ | Set-Content -Path .\docs\requirements.md