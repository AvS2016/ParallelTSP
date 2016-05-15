#!/bin/bash -e

COMP_URL="https://github.com/philsquared/Catch/archive/V1.5.0.tar.gz"
COMP_ARCH="Catch-1.5.0.tar.gz"
COMP_DIR="Catch-1.5.0"

mkdir -p dep
cd dep

export CATCH_INSTALL_DIR="$(pwd)/catch"

if [ -d "$CATCH_INSTALL_DIR" ]; then
    echo "Catch already installed."
    return
fi

# install catch
dlfile "$COMP_URL" "$COMP_ARCH"
tar xzf "$COMP_ARCH"
rm -f "$COMP_ARCH"
mkdir -p "$CATCH_INSTALL_DIR/include"
cp "$COMP_DIR/single_include/catch.hpp" "$CATCH_INSTALL_DIR/include"
