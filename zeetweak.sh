#!/bin/bash
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
cd "$SCRIPT_DIR"
VENV_DIR=".venv"

if ! command -v python3 &> /dev/null; then
    echo "Error: Python 3 not found."
    exit 1
fi

if [ ! -d "$VENV_DIR" ]; then
    echo "Setting up virtual environment and required packages..."
    python3 -m venv "$VENV_DIR"
    "$VENV_DIR/bin/python" -m pip install --upgrade pip
    "$VENV_DIR/bin/pip" install pyserial numpy pillow matplotlib
fi
"$VENV_DIR/bin/python" zeecapture.py "$@"
