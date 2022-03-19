#include "NonTool.hpp"

NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, type, quantity) {

}

bool NonTool::isTool() {
    return false;
}