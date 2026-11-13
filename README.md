# CPS-LELE
From IDE CPS group18, the string pitch-adjustment mechanism and the dancer-worn device that triggers the strings.

LELE is an interactive musical instrument inspired by the ukulele. It transforms body movements into physical string control. The movement amplitude of four limbs independently controls the pitch of four strings, while hip-sway movements control the strumming mechanism. The project explores how full-body movement can become a playful and expressive way of making music.


## How to Play
1. Stand in front of the camera.
2. Move your arms and legs.
3. Observe the mechanical response.
<img width="1536" height="1024" alt="Group 13 (2)" src="https://github.com/user-attachments/assets/b97d3e9a-feac-48a0-a800-6a47c8cea3fa" />

## System Workflow
<img width="1800" height="1300" alt="Group 8 (3)" src="https://github.com/user-attachments/assets/a778b606-9cfb-4716-b505-e745ebc627e1" />


## Documentation

### Technical Documentation

| Section | Description |
|---|---|
| [Installation & Startup Guide](docs/start up guide.docx) | Dependencies, hardware setup and step-by-step instructions for running Lele. |
| [Mechanical Design](docs/Mechanical_Design.md) | Mechanical structure, materials, fabrication and design decisions. |
| [Hardware Design](docs/Hardware_Design.md) | Components, circuit diagram, wiring and power supply. |
| [Software Design](docs/Software_Design.md) | System architecture, data flow and input-output mapping. |
| [Machine Learning](docs/Machine_Learning.md) | Wekinator configuration, training process, model evaluation and limitations. |
| [Testing & Debugging](docs/Testing_and_Debugging.md) | System testing, troubleshooting and debugging decision tree. |

### Source Code

| Folder | Description |
|---|---|
| [Python](code/python/) | Body tracking and OSC input using MediaPipe. |
| [Wekinator](code/WekinatorProject/) | Machine learning project and model configuration. |
| [Processing](code/processing/) | OSC communication and serial data transmission. |
| [Arduino](code/arduino/final/) | Stepper motor and servo control. |
| [Python Requirements](requirements.txt) | Required Python libraries. |

### Additional Resources

| Document | Description |
|---|---|
| [Project Reflection](Project_Reflection.docx) | Project limitations, challenges and future improvements. |
