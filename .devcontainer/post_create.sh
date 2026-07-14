#!/bin/bash

set -e

pre-commit install --install-hook-types pre-commit,commit-msg,pre-push
pre-commit install-hooks