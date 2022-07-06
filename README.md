# rx631_gcc_projects

GCC for Renesas Toolchain を利用した RX631 用のソースコードと Makefile を置いています。

ソースコードと Makefile は e2 studio を用いて生成したものです。
ToolChain がインストールされた Linux などの環境があれば、Windows の環境が無くともコンパイル出来るようになっていますが、Makefile はコンパイルコマンドをベタ書きした状態です。

## Directory Structure

C++向けは `g++`、C言語向けは `gcc` フォルダに分けています。
利用したいフォルダにある Makefile を利用してコンパイルすることで、以下のファイルが生成されます。

```bash
cd gcc
make
```

- `gcc_rx_project.elf`
- `gcc_rx_project.mot`

## TODO

- [ ] Makefileをいい感じにする
