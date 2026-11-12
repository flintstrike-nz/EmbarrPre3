# cinnabarr-engine

This fork builds **cinnabarr-engine**, the headless download engine used by [Cinnabarr](https://github.com/flintstrike-nz/EmbarrPre1). It is qBittorrent's `qbittorrent-nox` with a small "engine mode" layered on top. The design is in Cinnabarr's roadmap (`docs/embarr/ROADMAP.md`, §3 and §5).

Cinnabarr starts the engine as a child process and is its only client. Users never open the engine's web UI.

## Build

Same dependencies as qBittorrent (Qt ≥ 6.6, libtorrent ≥ 2.0.10, Boost, OpenSSL, zlib), plus `-DCINNABARR_ENGINE=ON`:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DGUI=OFF -DWEBUI=ON -DCINNABARR_ENGINE=ON
cmake --build build
# -> build/cinnabarr-engine
```

Without `CINNABARR_ENGINE` the build is unchanged and produces `qbittorrent` / `qbittorrent-nox` as upstream.

## Run (how Cinnabarr starts it)

```bash
CINNABARR_ENGINE_API_KEY=qbt_<28 random alphanumerics> \
  cinnabarr-engine --profile=<Cinnabarr AppData>/engine --webui-port=<free port> --confirm-legal-notice
```

Cinnabarr shows qBittorrent's legal notice to the user itself, so it passes `--confirm-legal-notice`.

## What engine mode forces on every start

| Setting | Value | Why |
| --- | --- | --- |
| API key | `CINNABARR_ENGINE_API_KEY` (required; the engine exits if it is missing or invalid) | Cinnabarr authenticates with `X-API-Key` |
| WebUI address | `127.0.0.1` | Private API, never on the network |
| UPnP for WebUI, HTTPS, alternative WebUI | off | Not needed on loopback |
| Local-host auth bypass, subnet whitelist | off | The API key is the only way in |
| Search engine | off, and the `search` API isn't registered | Cinnabarr searches indexers itself |
| `.!qB` extension for incomplete files | on | Cinnabarr downloads straight into the library |
| "Unwanted" folder | off | Unwanted files are never downloaded |
| RSS processing and auto-downloading | off, can't be turned on through `setPreferences`, and the `rss` API isn't registered | Cinnabarr fetches feeds and grabs releases itself |

The temporary WebUI password is not printed in engine mode.

## What engine mode leaves out

- **The web interface.** The WebUI's own files (`src/webui/www`) aren't built in, and any request outside `/api` gets `404`. Cinnabarr is the only interface.
- **The `search`, `rss` and `torrentcreator` APIs.** These aren't registered, so they return `404`.
- **The GUI.** `src/gui` isn't built (`GUI=OFF`).

These parts are switched off in the build rather than deleted, so upstream qBittorrent changes still merge cleanly.

The API calls Cinnabarr relies on, beyond what qBittorrent's own clients use, are `transfer/info`, `transfer/speedLimitsMode`, `transfer/toggleSpeedLimitsMode`, `torrents/start` / `torrents/stop` (with `hashes=all`) and `torrents/recheck`. Keep them when trimming further.

Every request must carry the API key (`X-API-Key` or `Authorization: Bearer`). Password logins, Basic authentication and cookie sessions are refused even if a WebUI password is saved in the profile.

`CINNABARR_ENGINE` requires `GUI=OFF` and `WEBUI=ON`, and can't be combined with `SYSTEMD` (Cinnabarr supervises the engine itself); CMake stops with an error otherwise.
