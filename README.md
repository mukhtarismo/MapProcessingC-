# OpenStreetMap Campus Navigator (C++17)

A single, end‑to‑end C++ command‑line app that parses an OpenStreetMap (OSM) extract of Northwestern’s Evanston campus, lists buildings, computes building locations, finds the nearest CTA bus stops, and (when online) fetches live arrival predictions.

---

## 

* **Core:** C++17, STL, TinyXML2 (XML), nlohmann/json (JSON), cURL.
* **Data:** `nu.osm` (OSM XML) + `bus-stops.txt` (CSV).
* **Queries:** `*` (all buildings), `<name>` (substring match), `@` (all bus stops), `$` (quit).
* **Speed:** Node lookups refactored from linear to **binary search** → typical calls to `getID()` drop from **>1,000,000** to **<3,000** for common workflows.
* **Design:** Cohesive types (`Node/Nodes`, `Building/Buildings`, `BusStop/BusStops`), thin `main`, pass‑by‑reference, `emplace_back`, exception handling for API edge cases, and offline mocking.

---

## Features

* Parse OSM **nodes** and **university buildings** (ways with `building=university`).
* Print buildings and search by partial name; show **ID**, **address**, **# perimeter nodes**, and **centroid** (avg lat/lon of perimeter nodes).
* Import CTA bus stops from CSV; list stops sorted by **Stop ID**.
* Compute **closest Northbound/Southbound** stops to a building (haversine via `dist.h`).
* Fetch **live predictions** (vehicle, route, direction, minutes) via CTA Bus Tracker API; robust to missing/empty fields; supports **offline** test mode.

---

## Architecture (quick)

* **Node / Nodes** — store 15,070 map nodes; `Nodes::find(id, ...)` uses **binary search** (data sorted by OSM id).
* **Building / Buildings** — stores building metadata and perimeter `NodeIDs`; `getLocation(const Nodes&)` returns centroid; `print()` and `findAndPrint()` encapsulate CLI output.
* **BusStop / BusStops** — CSV ingest, sorting/printing, nearest‑stop query.
* **Utilities** — `osm.*` (TinyXML2 helpers), `dist.h` (distance), `curl_util.*` (HTTP + offline mocks), `json.hpp` (JSON).

---

## Setup

```bash
# Build (online mode)
make build

# Build with offline API mocking (use saved responses)
make build-offline   # or: make build-online-save to capture for later

# Run
./a.out
```

> Dependencies are vendored (TinyXML2, json.hpp) or included via provided sources; no special system install required beyond a C++17 toolchain and libcurl.

---

## Usage

```
Enter OSM filename: nu.osm
# map nodes: 15070
# buildings: 103

Enter building name (* for all, @ for bus stops, $ to quit): Mudd
Mudd Hall
Address: 2233 Tech Drive
Building ID: 33908908
# perimeter nodes: 42
Location (lat, lon): 42.05851, -87.67688

Enter building name: @     # lists bus stops sorted by Stop ID
Enter building name: $     # exit
** Done **
```


Project built from course‑provided scaffolding plus my original implementation. Third‑party libraries acknowledged above; API keys kept out of source. Conforms to Northwestern CS 211 academic integrity guidelines.
