# Shoptimize 🛒

Command line tool that solves a [constraint satisfaction problem (CSP)](https://en.wikipedia.org/wiki/Constraint_satisfaction_problem) to generate an optimal `n`-day grocery list.

### Supported constraints
1. Maximum amount of money to spend
2. Number of times a meal component can/must be used

## Building
```sh
git clone --recursive https://github.com/bornabesic/shoptimize.git
cd shoptimize
mkdir build
cd build
cmake .. -D CMAKE_BUILD_TYPE=Release
make
```

### Dependencies
This project uses [yaml-cpp](https://github.com/jbeder/yaml-cpp) library to parse the configuration from a YAML file. It is stored in `lib/` as a git submodule. During the build process, the library is statically linked against the executable.

## Usage
```sh
shoptimize <configfile> <storename>
```
Arguments:
- `configfile`: Path to a YAML configuration file
- `storename`: Name of a store (defined in the configuration file) to use

### Example
Expected output when using [config/example.yaml](config/example.yaml) configuration file.

```sh
$ shoptimize config/example.yaml Kaufland

Products: 4
Components: 3
Stores: 1
Meals: 12
Constraints: 2

Time: 0.00140942 s
Solutions: 56

Best solution:
{Minutensteaks} {Heringsfilet}  {Pasta Pesto}   {Pasta Pesto}   {Heringsfilet}  {Pasta Pesto}   {Pasta Pesto}   {Heringsfilet}  {Pasta Pesto}   {Heringsfilet}  {Minutensteaks} {Heringsfilet}
Cost: 10.249
```
