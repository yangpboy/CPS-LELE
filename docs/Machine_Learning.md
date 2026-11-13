
# Machine Learning

## 1. Overview

Lele uses Wekinator to map body movements to mechanical responses. The system combines four Neural Network regression models for continuous limb movement and one k-Nearest Neighbor (kNN) classifier for hip movement.

## 2. Input & Model Configuration

### Input Features

Python uses MediaPipe Pose to detect body landmarks. Instead of sending raw coordinates, we calculate body-relative coordinates using anatomical reference points and shoulder width.

```python
relative_x = (landmark_x - reference_x) / shoulder_width
relative_y = (landmark_y - reference_y) / shoulder_width

hip_sway = (hip_center_x - shoulder_center_x) / shoulder_width
```

This reduces the influence of camera position and distance, although it does not eliminate changes caused by body orientation or occlusion.

The system sends **23 input features** to Wekinator:

- 22 relative x/y coordinates from 11 body landmarks
- 1 additional hip-sway feature

Before training, we verified the input count and changing values through the Python console:

```python
print("Inputs:", len(inputs), inputs[:2])
```

### Model Configuration

We used Wekinator's custom configuration to combine continuous regression and discrete classification outputs.

| Output | Algorithm | Range | Function |
|---|---|---|---|
| 1–4 | Neural Network Regression | 0–1 | Control four stepper motor positions |
| 5 | kNN Classification | 1 / 2 | Control servo strumming behaviour |

Neural Networks were selected to learn continuous, potentially nonlinear relationships between body landmarks and motor positions. kNN was used to distinguish two discrete hip movement states based on recorded examples.

<img width="732" height="413" alt="dda9ef80-d170-4ed5-b3d0-52aae73b87d3" src="https://github.com/user-attachments/assets/7051a5a3-0fc5-419a-964b-57f7f3d2ba59" />

### OSC Communication

| Setting | Value |
|---|---|
| Python → Wekinator | `/wek/inputs`, port 6448 |
| Wekinator → Processing | `/wek/outputs`, port 12000 |
| Input features | 23 |
| Output values | 5 |

## 3. Training Process

We collected training examples through live webcam tracking, pairing body-relative input features with manually assigned output values.

Training was carried out in several stages:

**Combined Training:** All five outputs were enabled to record coordinated full-body movements.

**Individual Training:** Regression models were trained separately using representative target values of 0, 0.5 and 1. The classifier was trained using Classes 1 and 2.

**Grouped Training:** Selected outputs were trained together to cover simultaneous movements of different body parts.

**Pose Variation:** We recorded movements from different camera positions and body orientations. Different poses could share the same target value, such as raising a leg forward, sideways or bending it backwards.

**Multiple Participants:** Initially, approximately 1,500 examples per output were collected by one team member. Later, other team members contributed approximately 1,500 additional examples during training, introducing variation in body proportions, movement habits, gender and clothing, including long and short garments.

These methods aimed to reduce dependence on a single posture or participant and improve the consistency of movement mapping.

## 4. Testing & Iteration

We evaluated the models through live interaction, observing whether regression outputs changed with limb movements and whether the classifier responded to hip movements.

Testing included individual limbs, combined movements, different body orientations and multiple participants. When outputs behaved inconsistently, we added or adjusted training examples.

### Final Training Data

The final Wekinator project (v2) shows the following example counts:

| Output | Model | Examples |
|---|---|---:|
| 1 | Regression | 3,194 |
| 2 | Regression | 3,618 |
| 3 | Regression | 2,780 |
| 4 | Regression | 2,368 |
| 5 | Classification | 2,808 |
| **Total** | | **14,768** |

The total is the sum of examples across five models, not the number of unique body poses. Different counts reflect the use of combined, individual and grouped training.

<img width="963" height="787" alt="2" src="https://github.com/user-attachments/assets/feec9777-adca-4a3b-b00c-c82da2fbfe1c" />

Model performance remains dependent on training coverage and MediaPipe tracking accuracy. Differences in body proportions, clothing, camera orientation and occlusion may affect predictions. Assigning similar outputs to different poses can also make mappings less consistent.

Evaluation was based on live observation rather than a separate quantitative test dataset, so model accuracy and generalisation to unseen users have not been measured.

Future improvements include more balanced training data, testing with unseen participants, quantitative evaluation of predicted outputs and additional input smoothing.
