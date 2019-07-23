#! /bin/bash

set -o pipefail
set -e

cmdname="$0"
scriptdir="$(readlink -f $(dirname "$cmdname"))"

hascmd() {
  which "$1" 2>/dev/null
}

get_avail_nice_cmd() {
  local cmd=""
  if hascmd nice; then
    cmd="nice -n 19 $cmd"
  fi
  if hascmd ionice; then
    cmd="ionice -c 3 $cmd"
  fi
  echo "$cmd"
}

load_config() {
  . "$scriptdir/build_config.sh"
  test -n "$IDF_PATH" || IDF_PATH="$scriptdir/toolchain/esp-idf/"
  test -n "$IDF_TOOLS_PATH" || IDF_TOOLS_PATH="$scriptdir/toolchain"
  export IDF_PATH IDF_TOOLS_PATH
}

setup_toolchain() {
  mkdir -p "$scriptdir/toolchain"
  git clone --recursive https://github.com/espressif/esp-idf "$IDF_PATH"
  "$IDF_PATH/install.sh"
}

idfexec() {
  test -e "$IDF_PATH" || setup_toolchain
  (
    . "$IDF_PATH"/export.sh >/dev/null
    exec "$@"
  )
}

idf() {
  idfexec idf.py "$@"
}

build() {
  idfexec $(get_avail_nice_cmd) idf.py build "$@"
}

clean() {
  idf clean "$@" || true
  rm -rfv "$scriptdir/build" "$scriptdir/sdkconfig"
}

flash() {
  idf flash "$@"
}

help() {
  echo >&2 "
USAGE

    \$ $cmdname help – show this help page
    \$ $cmdname build COMMAND [ARGS...] – Shortcut for $cmdname idfexec idf.py build
    \$ $cmdname clean COMMAND [ARGS...] – Shortcut for $cmdname idfexec idf.py clean
    \$ $cmdname flash COMMAND [ARGS...] – Shortcut for $cmdname idfexec idf.py flash
    \$ $cmdname idf COMMAND [ARGS...] – Shortcut for $cmdname idfexec idf.py
    \$ $cmdname idfexec COMMAND [ARGS...] – Execute an argument in the esp-idf environment
    \$ $cmdname setup_toolchain – Install esp-idf and a compiler toolchain for it in the toolchain/ directory
  "
}

main() {
  local cmd="$1"
  shift || true
  test -n "$cmd" || cmd="build"

  if grep -Pq '^(help|setup_toolchain|idfexec|idf|build|clean|flash)$' <<< "$cmd"; then
    "$cmd" "$@"
  else
    echo >&2 "ERROR: Unsupported command: $cmd"
    help
    return 1
  fi
}

load_config
main "$@"
