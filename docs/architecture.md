 
@'
# architecture

this project will use:
- esp32 as controller
- can bus
- agisostack++ reference
- hydraulic raise/lower valve outputs
- sensors and limit switches
- optional section logic later

phase 1:
- one section group for the whole implement
- raise pulse when section is off
- lower pulse when section is on
- basic diagnostic states
'@ | Set-Content -Path .\docs\architecture.md


///////////////////////////////////////////////////////


създаване на `docs/architecture.md`:

```powershell
@'
# architecture

## overview

this project is built around an esp32-based implement controller connected to a can bus and controlled by an isobus stack.

this is meant to expose the seeder as a valid implement to a tractor terminal and to translate implement state into hydraulic actions.

## core idea

the first implementation will not try to manage 42 independent outlet shut-offs.

instead, it will treat the machine as:

- one section group for the whole implement
- one lift/raise command state
- one lower command state

when the tractor sends a section control / work state command, the controller translates that into:

- raise valve pulse for 4-5 seconds when section is disabled
- lower valve pulse for 4-5 seconds when section is enabled
- mechanical cutoff keeps the machine raised after the pulse
- the next command starts the opposite pulse

## main blocks

### 1. esp32 controller

responsible for:

- input capture
- sensor polling
- can communication
- valve timing
- state machine execution

### 2. can / isobus layer

running agisostack++ or a related isobus stack in the implement controller context.

this layer should expose:

- implement identity
- diagnostics
- work state
- section status
- alarm states

### 3. hydraulic output stage

two outputs are expected initially:

- raise valve
- lower valve

a typical pattern is:

- raise valve opened for a fixed time
- close valve
- machine stays in raised position due to mechanical cutoff / valve hold
- lower valve opened for a fixed time
- close valve
- machine settles in operating position

### 4. sensor inputs

planned sensor and switch inputs:

- hopper empty sensor
- fan running sensor
- lift up switch
- lift down switch
- hose blocked / outlet blocked detection
- optional valve feedback

### 5. state machine

the controller must handle states such as:

- idle
- raise_pulse
- hold_raised
- lower_pulse
- hold_lowered
- fault

this allows deterministic operation and reduces risk of valve overheating or stuck conditions.

## section logic

for the first phase:

- one section = whole implement
- if section off, call raise pulse
- if section on, call lower pulse

this is enough to support a practical isobus implement interface without building a full multi-outlet section-control system.

## future extension

this can evolve to:

- 2 section groups
- grouped outlet shut-off logic
- better integration with vt / tc / aog
'@ | Set-Content -Path .\docs\architecture.md