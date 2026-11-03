# embarr-engine

This fork builds **embarr-engine**, the headless download engine used by [Embarr](https://github.com/flintstrike-nz/EmbarrPre1). It is qBittorrent's `qbittorrent-nox` with a small "engine mode" layered on top. The design is in Embarr's roadmap (`docs/embarr/ROADMAP.md`, §3 and §5).

Embarr starts the engine as a child process and is its only client. Users never open the engine's web UI.

## Build

Same dependencies as qBittorrent (Qt ≥ 6.6, libtorrent ≥ 2.0.10, Boost, OpenSSL, zlib), plus `-DEMBARR_ENGINE=ON`:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DGUI=OFF -DWEBUI=ON -DEMBARR_ENGINE=ON
cmake --build build
# -> build/embarr-engine
```

Without `EMBARR_ENGINE` the build is unchanged and produces `qbittorrent` / `qbittorrent-nox` as upstream.

## Run (how Embarr starts it)

```bash
EMBARR_ENGINE_API_KEY=qbt_<28 random alphanumerics> \
  embarr-engine --profile=<Embarr AppData>/engine --webui-port=<free port> --confirm-legal-notice
```

Embarr shows qBittorrent's legal notice to the user itself, so it passes `--confirm-legal-notice`.

## What engine mode forces on every start

| Setting | Value | Why |
| --- | --- | --- |
| API key | `EMBARR_ENGINE_API_KEY` (required; the engine exits if it is missing or invalid) | Embarr authenticates with `X-API-Key` |
| WebUI address | `127.0.0.1` | Private API, never on the network |
| UPnP for WebUI, HTTPS, alternative WebUI | off | Not needed on loopback |
| Local-host auth bypass, subnet whitelist | off | The API key is the only way in |
| Search engine | off | Embarr searches indexers itself |
| `.!qB` extension for incomplete files | on | Embarr downloads straight into the library |
| "Unwanted" folder | off | Unwanted files are never downloaded |

The temporary WebUI password is not printed in engine mode.
