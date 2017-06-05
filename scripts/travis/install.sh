#!/usr/bin/env bash

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    source ./scripts/env-setup/linux/ubuntu-14.04-env-setup.sh;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    source ./scripts/env-setup/osx/env-setup.sh;
fi