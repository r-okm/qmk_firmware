#!/usr/bin/env bash
set -euo pipefail

QMK_FIRMWARE_VERSION="${QMK_FIRMWARE_VERSION:-latest}"
SCRIPT_DIR="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"

main() {
    docker run --rm \
        --user "$(id -u):$(id -g)" \
        --workdir /qmk_firmware \
        --volume "${SCRIPT_DIR}:/qmk_firmware" \
        "qmkfm/qmk_firmware:${QMK_FIRMWARE_VERSION}" \
        make ble_micro_pro:r-okm:uf2
}

main
