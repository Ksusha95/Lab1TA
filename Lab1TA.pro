TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    reading_of_file.cpp \
    check_numb_charact_in_file.cpp \
    dec_2_bin.cpp \
    number_of_units.cpp \
    implicant.cpp \
    construction_of_tdnf.cpp \
    array_of_symbol_variables.cpp \
    dynamic_table_line.cpp \
    filling_the_mdnf_table.cpp \
    tdnf.cpp \

HEADERS += \
    implicant.h \
    tdnf.h \
