#ifndef TDNF_H
#define TDNF_H


class tdnf {

private:

    std::vector<std::string> variables;


public:

    tdnf();

    void set_tdnf(std::string element);

    std::vector<std::string> get_tdnf();

    void print_tdnf_string();
    void print_tdnf_column();
    void clear_value();



};

#endif // TDNF_H
