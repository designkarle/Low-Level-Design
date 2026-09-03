# 06 — Design Patterns (the 23 GoF patterns)

Design patterns are **named, reusable solutions** to recurring design problems — built on OOP (section 03) and the SOLID principles (section 05). Each pattern here has a focused, canonical example in **both C++ and Java**, with its own `Notes.md`. Section 09 then applies many of them to **real Node.js projects**.

> Almost every pattern is *disciplined dynamic polymorphism*: a base interface plus interchangeable concrete classes, wired together to localize whatever varies.

---

## Creational — *how objects get made*
| Pattern | One-liner |
|---|---|
| [Factory Method](Creational/Factory%20Method/Notes.md) | Subclasses decide which concrete product to create. |
| [Abstract Factory](Creational/Abstract%20Factory/Notes.md) | Create matching **families** of products. |
| [Builder](Creational/Builder/Notes.md) | Build a complex object step by step (no telescoping ctor). |
| [Prototype](Creational/Prototype/Notes.md) | Create new objects by **cloning** a configured instance. |
| [Singleton](Creational/Singleton/Notes.md) | Exactly one instance, one global access point. |

## Structural — *how objects are composed*
| Pattern | One-liner |
|---|---|
| [Adapter](Structural/Adapter/Notes.md) | Make an incompatible interface fit the one a client expects. |
| [Bridge](Structural/Bridge/Notes.md) | Split abstraction from implementation so both vary freely. |
| [Composite](Structural/Composite/Notes.md) | Treat leaves and trees uniformly. |
| [Decorator](Structural/Decorator/Notes.md) | Add responsibilities by wrapping, at runtime. |
| [Facade](Structural/Facade/Notes.md) | One simple front door over a complex subsystem. |
| [Flyweight](Structural/Flyweight/Notes.md) | Share intrinsic state across many objects to save memory. |
| [Proxy](Structural/Proxy/Notes.md) | A stand-in that controls access (lazy/cache/guard). |

## Behavioral — *how objects interact & share responsibility*
| Pattern | One-liner |
|---|---|
| [Chain of Responsibility](Behavioral/Chain%20of%20Responsibility/Notes.md) | Pass a request down a chain of handlers. |
| [Command](Behavioral/Command/Notes.md) | Encapsulate a request as an object (enables undo). |
| [Interpreter](Behavioral/Interpreter/Notes.md) | A class per grammar rule; evaluate a sentence tree. |
| [Iterator](Behavioral/Iterator/Notes.md) | Traverse a collection without exposing its storage. |
| [Mediator](Behavioral/Mediator/Notes.md) | Centralize many-to-many interaction in one object. |
| [Memento](Behavioral/Memento/Notes.md) | Capture/restore state without breaking encapsulation. |
| [Observer](Behavioral/Observer/Notes.md) | Notify many dependents when one object changes. |
| [State](Behavioral/State/Notes.md) | Behaviour changes with internal state (state = class). |
| [Strategy](Behavioral/Strategy/Notes.md) | Interchangeable algorithms, swapped at runtime. |
| [Template Method](Behavioral/Template%20Method/Notes.md) | Fixed algorithm skeleton, subclassed steps. |
| [Visitor](Behavioral/Visitor/Notes.md) | Add operations to a hierarchy without editing it. |

---

## Patterns that look similar (don't mix them up)
- **Strategy vs State** — both swap an object's behaviour via composition, but State *transitions itself* between states; Strategy is chosen by the client and doesn't self-change.
- **Adapter vs Facade** — Adapter makes *one* incompatible interface fit an expected one; Facade *simplifies* a whole subsystem behind a convenient API.
- **Factory Method vs Abstract Factory** — Factory Method makes *one* product via a subclass hook; Abstract Factory makes a *family* of matching products.
- **Decorator vs Proxy** — both wrap an object with the same interface; Decorator *adds behaviour*, Proxy *controls access*.

## Every chapter
- `C++ Code/example.cpp` — teaching-style C++ (`g++ -std=c++14`).
- `Java Code/Main.java` — the same design in Java (`javac Main.java ; java Main`).
- `Notes.md` — intent, domain, a Mermaid diagram, and expected output.

➡️ Next: **[07 — LLD of Giant Systems](../07%20-%20LLD%20of%20Giant%20Systems/Notes.md)**
