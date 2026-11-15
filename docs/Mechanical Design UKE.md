# UKE — Dancer String Triggering Device

An independently controlled rotating and expanding linkage for progressively plucking the strings of a mechanical music-box system.

<img width="2267" height="1300" alt="Frame 26" src="https://github.com/user-attachments/assets/7ce52491-65f9-43c9-9da6-a0e100578bcc" />

## Overview

The dancer mechanism combines two mechanically separated motions:

1. A **stepper motor and timing-belt drive** rotate the complete dancer assembly around the central axis. As it turns, the outer picks contact and pluck the strings in sequence.
2. An **servo, gear set and vertical rack** move the upper sliding shaft seat. This opens or closes the umbrella-style radial linkages and changes how many picks can reach the strings.

An **magnet** is mounted above the upper sliding shaft seat to control the slider while maintaining clearance around the central guide structure.

<img width="9068" height="4252" alt="Frame 27" src="https://github.com/user-attachments/assets/5e070324-0946-4587-9e66-c50a8260f4e4" />

## Mechanism architecture

| Subsystem | Input | Mechanical action | Output |
|---|---|---|---|
| Rotation drive | Stepper motor | Drives a bearing-guided timing belt | Rotates the upper dancer assembly |
| Open / close drive | SG90 servo | Turns the gear set and vertical rack | Raises or lowers the upper sliding shaft seat |
| Radial linkage | Vertical slider movement | Opens or contracts the paired wooden arms | Changes the operating radius and number of reachable strings |
| Pivot system | M4 bolts, nuts, washers and bearings | Allows repeatable low-friction rotation | Keeps each linkage pair articulated |
| Magnetic control | N52 ring magnet | Couples to the upper slider without contacting the central mast | Supports controlled vertical motion |

<img width="9068" height="6132" alt="Frame 25" src="https://github.com/user-attachments/assets/ec2cb616-a53c-4594-a6c2-fe884fcc7bef" />

## Operating envelope

The radius is measured in the XY plane from the **central rotation axis to the outermost mechanism point**, including the outer bearing or wheel.

| State | Radius | Diameter |
|---|---:|---:|
| Open / extended | 190.3 mm | 380.5 mm |
| Closed / folded | 171.5 mm | 343.1 mm |
| Difference | 18.7 mm | 37.4 mm |

Closing the mechanism reduces its radial envelope by approximately **9.8%**.

<img width="9068" height="5236" alt="Frame 29" src="https://github.com/user-attachments/assets/8b98208b-050f-4fde-9763-041e06a201a2" />


## Materials and components

| Component group | Material / specification | Function |
|---|---|---|
| Structure | Laser-cut plywood | Base, frame, radial linkages and structural plates |
| Custom parts | PLA or PETG | Sliding hubs, belt-drive supports and joint parts |
| Pivot joints | M4 bolts, nuts, washers and bearings | Secure the arms while allowing repeated rotation |
| Rotation drive | Stepper motor, timing belt, drive hub and bearing guide | Transfer torque to the rotating upper mechanism |
| Open / close drive | SG90 servo, gear set and vertical rack | Move the upper slider vertically |
| Magnetic control | N52 ring magnet, 40 mm OD × 28 mm ID × 5 mm | Control the upper sliding shaft seat |

<img width="9068" height="4032" alt="Frame 24" src="https://github.com/user-attachments/assets/2c4efaae-1791-4048-ab1c-41d791d47117" />

## Assembly relationship

The exploded view separates the main groups while preserving their assembly direction and mechanical relationship.

<img width="9068" height="6060" alt="Frame 28" src="https://github.com/user-attachments/assets/00b075a2-e637-4931-981f-d328738bdffc" />

Recommended assembly order:

1. Assemble the plywood base, side frames and motor supports.
2. Install the stepper motor, drive hub, bearing guide and timing belt.
3. Install the servo, gear set and vertical rack; confirm that the rack moves without binding.
4. Fit the lower fixed pivot seat and central guide shaft.
5. Fit the upper sliding shaft seat and magnet.
6. Attach each wooden linkage pair using the M4 pivot hardware.
7. Attach the outer picks or wheels and check that each radial arm moves freely.
8. Rotate and open / close the mechanism manually before powering either motor.



## Motion and clearance checks

- The **upper sliding shaft seat** must move vertically; the **lower fixed pivot seat** must remain fixed.
- The timing belt must follow the drive hub and bearing guide without crossing or intersecting the bearing body.
- The rotating assembly and open / close drive must remain mechanically independent.
- M4 joints should rotate freely without visible side play or over-tightening.
- Test magnet clearance, belt tension and full linkage travel at low speed before normal operation.


## Prototype status

This repository documents a working design-stage prototype. Before fabrication or long-duration operation, verify joint clearances, belt tension, material thickness, motor torque and safe separation from the music-box strings.
