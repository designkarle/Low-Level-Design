# 09 — Design Patterns in Real Projects

Section 06 taught the **23 GoF patterns** with small, focused examples (in C++ and
Java). This section puts each one to work in a **production-flavoured Node.js
project** — the kind of scenario you'd actually meet on the job.

**Why a whole second pass on patterns?** A pattern only clicks when you've seen it
*solve a real problem*. "Strategy" is abstract; "swap normal / surge / member
pricing on a ride estimator" is not. Each project here is the same pattern from
section 06, re-cast as a believable feature with believable trade-offs.

All projects are **plain Node.js** (CommonJS, zero dependencies, zero install).

---

## The 23 projects

### Creational
| Pattern | Project |
|---|---|
| **Factory Method** | [Notification Senders](Factory%20Method%20-%20Notification%20Senders/Notes.md) — email / SMS / push |
| **Abstract Factory** | [Cloud Resources](Abstract%20Factory%20-%20Cloud%20Resources/Notes.md) — AWS vs GCP families |
| **Builder** | [HTTP Request](Builder%20-%20HTTP%20Request/Notes.md) — fluent, validated construction |
| **Prototype** | [Document Templates](Prototype%20-%20Document%20Templates/Notes.md) — clone + customise |
| **Singleton** | [Logger & Config](Singleton%20-%20Logger%20and%20Config/Notes.md) — the require-cache singleton |

### Structural
| Pattern | Project |
|---|---|
| **Adapter** | [Payment Gateways](Adapter%20-%20Payment%20Gateways/Notes.md) — multi-region, multi-SDK (the flagship) |
| **Bridge** | [Notification Channels](Bridge%20-%20Notification%20Channels/Notes.md) — type × channel |
| **Composite** | [Org Chart](Composite%20-%20Org%20Chart/Notes.md) — headcount + cost rollup |
| **Decorator** | [Data-Stream Pipeline](Decorator%20-%20Data%20Stream%20Pipeline/Notes.md) — compress + encrypt + encode |
| **Facade** | [Checkout](Facade%20-%20Checkout/Notes.md) — one call over four subsystems |
| **Flyweight** | [Map Markers](Flyweight%20-%20Map%20Markers/Notes.md) — shared icons |
| **Proxy** | [Caching Service](Proxy%20-%20Caching%20Service/Notes.md) — cache + access control |

### Behavioral
| Pattern | Project |
|---|---|
| **Chain of Responsibility** | [HTTP Middleware](Chain%20of%20Responsibility%20-%20HTTP%20Middleware/Notes.md) — auth → rate-limit → log |
| **Command** | [Editor Undo & Redo](Command%20-%20Editor%20Undo%20and%20Redo/Notes.md) — undo/redo + macros |
| **Interpreter** | [Rule Engine](Interpreter%20-%20Rule%20Engine/Notes.md) — discount/feature-flag rules |
| **Iterator** | [Paginated Feed](Iterator%20-%20Paginated%20Feed/Notes.md) — lazy pagination via generators |
| **Mediator** | [Smart-Home Hub](Mediator%20-%20Smart%20Home%20Hub/Notes.md) — sensors ↔ actuators |
| **Memento** | [Game Save](Memento%20-%20Game%20Save/Notes.md) — checkpoints / reload |
| **Observer** | [Stock Ticker](Observer%20-%20Stock%20Ticker/Notes.md) — live price fan-out |
| **State** | [Support Ticket](State%20-%20Support%20Ticket/Notes.md) — guarded lifecycle |
| **Strategy** | [Dynamic Pricing](Strategy%20-%20Dynamic%20Pricing/Notes.md) — normal / surge / subscription |
| **Template Method** | [Report Export](Template%20Method%20-%20Report%20Export/Notes.md) — CSV / JSON skeleton |
| **Visitor** | [Cart Operations](Visitor%20-%20Cart%20Operations/Notes.md) — invoice + tax over items |

---

## How every project is shaped
Each folder is a small, real Node project:
```
<Pattern - Scenario>/
  src/
    <domain>.js   the pattern's classes, split by responsibility
    index.js      the demo (composition root), guarded by require.main
  Notes.md        scenario, UML, layout, how-to-run, expected output, takeaway
```
Run any of them:
```powershell
cd "09 - Design Patterns in Real Projects/<Pattern - Scenario>"
node src/index.js
```
Node 18+, no dependencies.

## How this section differs from section 06
- **Section 06**: the pattern in isolation, in C++ **and** Java — *learn the shape*.
- **Section 09**: the pattern in a believable feature, in Node.js — *see it pay off*,
  including the **trade-offs** (Visitor makes operations cheap but types expensive;
  retry-vs-terminal in the payment Adapter; module-cache vs `getInstance()` for Singleton).

## A note on patterns combining
Real systems rarely use one pattern. The flagship **Adapter — Payment Gateways**
already blends Adapter + Factory + Strategy + a region policy + fallback. That's
the bridge to **section 07/08**, where whole products stack five or six patterns
at once.
