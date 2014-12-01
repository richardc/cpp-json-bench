A small experiment with benchmarking tools and json serialisers.

# To use

This uses submodules for vendored components, so:

    git submodule init
    git submodule update

Make a `MOCK_DATA.json` at http://www.mockaroo.com/

    make && ./bin/bench
