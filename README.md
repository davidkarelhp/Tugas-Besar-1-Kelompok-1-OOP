# Doraemonangis Crafting Gadget
> Tugas Besar 1 IF2210 Pemrograman Berorientasi Objek 2022

## General Information
A command-line interface (CLI) game where the player can craft new item from a list of item. Items in this game are divided into two categories, tool and non-tool. Player is allowed to add, discard, move, and give the items from and to the inventory. Lastly, player can also export all the items listed in the inventory to a file. 

## Struktur Repository
    .
    │   .gitignore
    │   check.cpp
    │   main.cpp
    │   Makefile
    │   README.md
    │
    ├───.vscode
    │       settings.json
    │
    ├───config
    │   │   item.txt
    │   │
    │   └───recipe
    │           BIRCH_PLANK.txt
    │           BUCKET.txt
    │           DIAMOND_AXE.txt
    │           DIAMOND_HOE.txt
    │           DIAMOND_PICKAXE.txt
    │           DIAMOND_SHOVEL.txt
    │           DIAMOND_SWORD.txt
    │           GOLDEN_AXE.txt
    │           GOLDEN_HOE.txt
    │           GOLDEN_PICKAXE.txt
    │           GOLDEN_SHOVEL.txt
    │           GOLDEN_SWORD.txt
    │           GOLD_INGOT.txt
    │           GOLD_NUGGET.txt
    │           IRON_AXE.txt
    │           IRON_HOE.txt
    │           IRON_INGOT.txt
    │           IRON_NUGGET.txt
    │           IRON_PICKAXE.txt
    │           IRON_SHOVEL.txt
    │           IRON_SWORD.txt
    │           OAK_PLANK.txt
    │           SHEAR.txt
    │           SPRUCE_PLANK.txt
    │           STICK.txt
    │           STONE_AXE.txt
    │           STONE_HOE.txt
    │           STONE_PICKAXE.txt
    │           STONE_SHOVEL.txt
    │           STONE_SWORD.txt
    │           WOODEN_AXE.txt
    │           WOODEN_HOE.txt
    │           WOODEN_PICKAXE.txt
    │           WOODEN_SHOVEL.txt
    │           WOODEN_SWORD.txt
    │
    ├───Crafting
    │       Crafting.cpp
    │       Crafting.hpp
    │       RecipeTrie.cpp
    │       RecipeTrie.hpp
    │       TrieNode.cpp
    │       TrieNode.hpp
    │
    ├───Exception
    │       BaseException.hpp
    │       DifferentItemException.hpp
    │       ItemNotExistException.hpp
    │       NonStackableToolException.hpp
    │       NonToolUnusableException.hpp
    │       NotEnoughItemException.hpp
    │       NotIntegerException.hpp
    │       NotValidItemNameException.hpp
    │       NotValidSlotIdException.hpp
    │
    ├───Inventory
    │       Inventory.cpp
    │       Inventory.hpp
    │
    ├───IO
    │   │   .txt
    │   │
    │   ├───inputItem
    │   │       InputItem.cpp
    │   │       InputItem.hpp
    │   │
    │   ├───inputRecipe
    │   │       InputRecipe.cpp
    │   │       InputRecipe.hpp
    │   │
    │   └───outputFile
    │           OutputFile.cpp
    │           OutputFile.hpp
    │
    ├───Item
    │       driver_item.cpp
    │       Item.cpp
    │       Item.hpp
    │       NonTool.cpp
    │       NonTool.hpp
    │       Tool.cpp
    │       Tool.hpp
    │       Triplet.cpp
    │       Triplet.hpp
    │
    ├───Player
    │       Player.cpp
    │       Player.hpp
    │
    └───tests
            1.ans
            1.in
            1.out
            2.ans
            2.in
            2.out

## Setup
- Use Linux or WSL (Windows)
- Install g++ compiler

## Usage
1. Clone this repository.
2. Run `make compile` on terminal.
3. Run `./main` on terminal or run `main.exe`

## Contributors
- [Fayza Nadia | 13520001 | K01](https://github.com/fayzanadia)
- [Nadia Mareta Putri Leiden | 13520007 | K01](https://github.com/KorbanFidas2A)
- [Taufan Fajarama Putrawansyah R | 13520031 | K01](https://github.com/roastland)
- [Raden Haryosatyo Wisjnunandono | 13520070 | K01](https://github.com/nandono206)
- [Averrous Saloom | 13520100 | K01](https://github.com/averrous-s)
- [David Karel Halomoan | 13520154 | K01](https://github.com/davidkarelhp)
