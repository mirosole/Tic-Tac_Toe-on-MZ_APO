# 🎮 Embedded System Game for MZ\_APO

## 📌 Description

This project is a **game** developed for the **MZ\_APO platform**, written in **C**.
It utilizes hardware controls such as **RGB LEDs, rotary encoders, and a graphical display**.
The project also supports running in **QtRVSim** (an embedded systems emulator).

---

## 📂 Project Structure

📁 **Main project files:**

* **`checker_game.c`** – main executable
* **`draw_game.h`** – functions for rendering game visuals
* **`game_objects.h`** – data structures for game objects
* **`game_logic.h`** – game logic processing
* **`drawing.h`** – helper functions for drawing
* **`utils.h`** – utility functions
* **`mzapo_parlcd.h`** – display management
* **`mzapo_phys.c`** – peripheral control (buttons, encoders, LEDs)
* **`serialize_lock.h`** – game state saving/loading

---

## 🎯 Key Features

✅ **Graphical interface** rendered on the display
✅ **Hardware control support** (buttons, encoders)
✅ **RGB LED indicators** for player states
✅ **Game state saving and loading**
✅ **Support for QtRVSim** (testing on PC)

---

## 🛠 Installation & Execution

### 🔧 **Compile the project**

```sh
make
```

### ▶ **Run the game**

```sh
./checker_game
```

If using **QtRVSim**, run it in the emulator:

```sh
qtrvsim ./checker_game
```

---

## 🎮 Controls

| Action    | Control Element |
| --------- | --------------- |
| Move      | Rotary encoder  |
| Select    | Encoder button  |
| Save game | Special button  |

RGB LEDs indicate **player state**:
🟢 **Green** – normal
🔵 **Blue** – object absorbed
🔴 **Red** – game over

---

## ⚙️ Requirements

📌 **MZ\_APO** or **QtRVSim**
📌 **GCC compiler (C99 or later)**
📌 **Makefile for building**

---

## 🚀 Development

👨‍💻 **Oleksii Miroshnichenko & Olena Romushka**
📅 Final project for the APO university course.

---

