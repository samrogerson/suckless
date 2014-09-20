#! /usr/bin/env bash

set -euo pipefail

function usage() {
    echo "./`basename $0` [linkcfg|patch]"
    exit 1
}

function linkcfg() {
    for config in *-config.h; do
        local target_dir=${config%%-config.h}
        (
            cd "$target_dir"
            ln -sf ../"$config" config.h 
        )
    done
}

function apply_patches() {
    for p in patches/*.patch; do
        local patch_basename=`basename $p`
        local target_dir=${patch_basename/.patch/}
        patch -b -d "$target_dir" -p0 -i ../"$p"
    done
}

function main() {
    while [[ $# -gt 0 ]]; do
        action="${1:-}"
        case "$action" in
            "linkcfg")
                linkcfg
                ;;
            "patch")
                apply_patches
                ;;
            *)
                usage
                ;;
        esac
        shift
    done
}

main "$@"
