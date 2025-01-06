Shell
---

A shell written in C just for fun.

## Development

Check out the code and its dependencies

```sh
git clone git@github.com:shikaan/shell.git
cd shell
git submodule update --init
```

Build

```sh
make
```

Test

```sh
make test
```

## Missing features

This shell is by no means complete nor totally usable. 

There are some glaring holes and missing features such as:
* no piping
* only output redirection and only for stdout
* no history
* no templating nor subshell expansion with `$`
* cannot navigate the prompt with arrow keys