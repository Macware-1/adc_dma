#!/bin/bash

echo "Build docker container"
docker build -t stm32-build-env .

echo "Bild firmware image"
docker run --rm -v "$(dirname "$PWD")":/workspace stm32-build-env