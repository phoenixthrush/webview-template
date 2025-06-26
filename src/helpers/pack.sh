#!/usr/bin/env bash

cross_build=(build/bin/Release/*.exe)
native_build=(build/bin/*)
dll="build/bin/Release/libwebview.dll"

[ -f "$dll" ] && rm "$dll"

if compgen -G "${cross_build[0]}" > /dev/null || compgen -G "${native_build[0]}" > /dev/null; then
    echo "Build output found."

    if command -v upx &>/dev/null; then
        if compgen -G "${cross_build[0]}" > /dev/null; then
            echo "Compressing cross build with UPX..."
            upx --best "${cross_build[@]}"
        elif compgen -G "${native_build[0]}" > /dev/null; then
            if [[ "$(uname)" == "Darwin" ]]; then
                echo "Skipping compression on macOS (native build)."
            else
                echo "Compressing native build with UPX..."
                upx --best "${native_build[@]}"
            fi
        fi
    else
        echo "UPX is not installed."
    fi
else
    echo "No build output found."
fi
