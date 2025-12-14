# AI Usage Policy

This project is a learning-focused exploration of real-time physics simulation, graphics programming, and low-level C++ system design. To preserve the educational value and ensure that all core engineering work represents the developer’s own understanding and skill, the use of AI tools is intentionally constrained.

This document outlines how AI may and may not be used within this repository.

---

## 📘 Purpose of These Guidelines
AI can accelerate development, but it can also inhibit learning if overused.  
The goal of this policy is to:

- Protect the developer's learning outcomes  
- Ensure core technical work is authored manually  
- Use AI as a tutor, reviewer, and debugging assistant — not a co-author  
- Maintain transparency for anyone reviewing the repository  

---

## ✅ Allowed AI Assistance

AI tools **may be used** for the following:

### **1. Explanations & Conceptual Guidance**
AI can explain:
- C++ concepts (memory, RAII, references, vectors, ownership)
- Real-time physics concepts (forces, integrators, numerical stability)
- Rendering and graphics concepts (SFML usage, blending, trails)
- Architectural patterns and tradeoffs  
- General debugging strategies  

### **2. Code Review & Feedback**
AI may:
- Review code written by the developer  
- Identify inefficiencies, potential bugs, or numerical issues  
- Suggest improvements without rewriting entire core systems  

### **3. Debugging Assistance**
AI may:
- Help interpret compiler errors  
- Point out logical issues in provided code  
- Explain crashes or undefined behavior  

### **4. Documentation & Non-Core Tasks**
AI may generate:
- README content  
- Learning outcomes  
- Project descriptions  
- Comments and documentation  
- Build files (CMake, SFML linking) *after the developer’s initial attempt*  
- Minor helper utilities unrelated to simulation logic  

---

## ❌ Prohibited AI Use (Core Learning Zones)

AI **must not** design or implement any major system that aligns with the core learning goals of the project.

The following areas must be written entirely by the developer:

### **1. Physics Simulation Logic**
- Physics update loop  
- Force functions (gravity, drag, repulsion, springs)  
- Numerical integrators (Euler, semi-implicit Euler, Verlet, etc.)  

### **2. Engine Architecture**
- Scene management system  
- Base scene interfaces (e.g., `IScene`)  
- Rendering pipeline logic  
- The main update → render → event loop  
- Core class implementations:
  - `Particle`
  - `Attractor`
  - `ParticleSystem`
  - Anything in directories like `core/`, `engine/`, or `simulation/`

### **3. Rendering & Visual Behavior**
- Particle and attractor rendering
- Trail systems, fade buffers, blending effects
- Any subsystem responsible for real-time motion visualization

### **4. End-to-End System Implementations**
AI must not output full drop-in code for major features.  
It may offer *explanations*, *hints*, *pseudo-code*, or *reviews*, but not final production code.

---

## 🧭 Process Guidelines

### **1. The developer must attempt implementation first.**
AI should be consulted **after** an initial attempt, not before.

### **2. AI responses should prioritize learning.**
Hints, explanations, and questions are preferred to code.

### **3. If AI outputs core code inadvertently, it must be rewritten manually.**
No copy-pasting into the project for protected areas.

### **4. AI may decline requests that violate this policy.**

---

## 📝 Summary

AI is a tool for:
- learning  
- debugging  
- reviewing  
- brainstorming  
- documenting  

But **not** for building the core simulation or engine.

This policy ensures the repository reflects authentic technical growth, while still benefiting from AI where appropriate.

---

If you have questions about these rules or see opportunities to improve them, feel free to open an issue or start a discussion.
