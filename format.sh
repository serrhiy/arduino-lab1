#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")"

mapfile -d '' files < <(find src include -type f \
    \( -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' \
    -o -name '*.h' -o -name '*.hh' -o -name '*.hpp' \) -print0)

if [ "${#files[@]}" -eq 0 ]; then
    exit 0
fi

clang-format -style=Microsoft -i "${files[@]}"
