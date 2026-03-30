# CTF Challenge: Buffer Overflow & Race Condition

A CTF challenge combining a TOCTOU race condition and a stack buffer overflow, running in Docker. Created by Felix Ichters and Lukas Dzielski.

## Setup

```sh
docker compose up --build
```

Entry point: `ssh user@localhost -p 2222`

## Architecture

Three containers share a volume and a network:

- **Start Container** — SSH entry point for the player
- **Server Container** — Runs a Flask server with a vulnerable C binary (`vuln.c`) exposed via `POST /write`
- **Buffer-Overflow Container** — Contains the `admin` binary and both flags; accessible via SSH after completing stage 1

The shared volume holds `authorized_keys`, which is symlinked into the Buffer-Overflow container.

## Challenge 1: Race Condition (TOCTOU)

The Flask server exposes `POST /write?filename=<path>` which invokes a vulnerable C binary. The binary:

1. Checks write permission on the file (`access()`)
2. Introduces an artificial delay
3. Opens and writes to the file (`fopen()`)

The window between the permission check and the write allows you to swap the target file with a symlink to `authorized_keys` in the shared volume.

**Goal:** Write your SSH public key into the Buffer-Overflow container's `authorized_keys` to gain SSH access.

**Flag 1** is in the home directory of the user on the Buffer-Overflow container.

## Challenge 2: Stack Buffer Overflow

Once inside the Buffer-Overflow container, the `admin` binary is vulnerable to a classic stack buffer overflow via `gets()`. ASLR is active (cannot be disabled inside Docker), but the binary leaks the buffer address to a hidden file `.leak` on each run.

**Exploit steps:**

1. Read the leaked buffer address from `.leak`
2. Calculate the offset to the return address (`rsp - leak` in GDB)
3. Build the payload: NOP sled + x86-64 shellcode (`setuid(0)` / `setgid(0)` / `execve("/bin/sh")`) + return address
4. Send it via pwntools

**Flag 2** is at `/root`, readable only from a root shell.

## Notes

- The exploit reliability varies across kernel versions and machines due to modern security mitigations
- Most buffer overflow resources target 32-bit systems — the shellcode here is x86-64
- Core dumps are not reliably available inside Docker; use GDB to find the offset manually
