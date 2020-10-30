#include "tdnf.h"

tdnf::tdnf() {}

void tdnf::set_tdnf(std::string element) {

    this->variables.push_back(element);

}

std::vector<std::string>tdnf::get_tdnf() {

    return this->variables;

}

void tdnf::print_tdnf_string() {

    for (size_t i = 0; i < this->variables.size(); i++)
        std::cout << variables.at(i);

    std::cout << "\n";

}


void tdnf::print_tdnf_column() {

    for (size_t i = 0; i < this->variables.size(); i++)
        std::cout << variables.at(i);

    std::cout << "  ";

}

void tdnf::clear_value() {

    this->variables.clear();

}
